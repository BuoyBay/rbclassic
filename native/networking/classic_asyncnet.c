/* RBClassic async client transport. POSIX; no Buoy runtime internals.
 * DNS alone runs on a detached worker. All socket/queue access stays on the
 * calling main thread. The DNS result is published under lock. Two references
 * let Close return immediately while an outstanding resolver finishes safely.
 */
#define _POSIX_C_SOURCE 200809L
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define LIMIT (16 * 1024 * 1024)

typedef struct {
    pthread_mutex_t lock;
    int refs, resolved, dns_error;
    char *host;
    char service[8];
    struct addrinfo *addresses, *next;
    int fd, state, error, eof;
    unsigned char *rx, *tx;
    size_t nr, nt, offset;
    int64_t sent;
    char local[1025], remote[1025];
    int localport;
} cx;

static void release(cx *s) {
    pthread_mutex_lock(&s->lock);
    int last = !--s->refs;
    pthread_mutex_unlock(&s->lock);
    if (last) {
        if (s->addresses) freeaddrinfo(s->addresses);
        free(s->host);
        free(s->rx);
        free(s->tx);
        pthread_mutex_destroy(&s->lock);
        free(s);
    }
}

static void *resolve(void *arg) {
    cx *s = arg;
    struct addrinfo hints = {0}, *addresses = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    int error = getaddrinfo(s->host, s->service, &hints, &addresses);
    pthread_mutex_lock(&s->lock);
    s->addresses = addresses;
    s->next = addresses;
    s->dns_error = error;
    s->resolved = 1;
    pthread_mutex_unlock(&s->lock);
    release(s);
    return NULL;
}

void *cx_start(const char *host, int port) {
    cx *s = calloc(1, sizeof(*s));
    if (!s) return NULL;
    if (pthread_mutex_init(&s->lock, NULL)) {
        free(s);
        return NULL;
    }
    s->refs = 2;
    s->fd = -1;
    s->state = 1;
    s->host = strdup(host);
    snprintf(s->service, sizeof(s->service), "%d", port);
    if (!s->host) {
        s->refs = 1;
        release(s);
        return NULL;
    }
    pthread_t thread;
    int error = pthread_create(&thread, NULL, resolve, s);
    if (error) {
        s->refs = 1;
        release(s);
        return NULL;
    }
    pthread_detach(thread);
    return s;
}

static void shut(cx *s) {
    if (s->fd >= 0) {
        close(s->fd);
        s->fd = -1;
    }
}

void cx_close(void *p) {
    if (!p) return;
    cx *s = p;
    shut(s);
    release(s);
}

static int fail(cx *s, int error) {
    s->error = error;
    s->state = 5;
    shut(s);
    return 16;
}

static void metadata(cx *s) {
    struct sockaddr_storage address;
    socklen_t count = sizeof(address);
    char port[16];
    if (!getsockname(s->fd, (void *)&address, &count)) {
        if (!getnameinfo((void *)&address, count, s->local, sizeof(s->local),
                         port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV)) {
            s->localport = atoi(port);
        }
    }
    count = sizeof(address);
    if (!getpeername(s->fd, (void *)&address, &count)) {
        getnameinfo((void *)&address, count, s->remote, sizeof(s->remote),
                    NULL, 0, NI_NUMERICHOST);
    }
}

/* Transitions: Connected=1, Data=2, Progress=4, EOF=8, Error=16.
 * Never waits. Max one 64 KiB send/receive per call. Connection transition
 * returns before IO so Connected callbacks observe an actual connected state.
 */
int cx_poll(void *p) {
    cx *s = p;
    int bits = 0;
    s->sent = 0;
    if (s->state == 1) {
        pthread_mutex_lock(&s->lock);
        int ready = s->resolved, error = s->dns_error;
        pthread_mutex_unlock(&s->lock);
        if (!ready) return 0;
        if (error) return fail(s, 1001); /* Adapter DNS category, not errno. */
        s->state = 2;
    }
    if (s->state == 2) {
        if (s->fd >= 0) {
            struct pollfd descriptor = {s->fd, POLLOUT, 0};
            int ready = poll(&descriptor, 1, 0);
            if (ready < 0) {
                if (errno == EINTR) return 0;
                return fail(s, errno);
            }
            if (!ready) return 0;
            int error = 0;
            socklen_t count = sizeof(error);
            if (getsockopt(s->fd, SOL_SOCKET, SO_ERROR, &error, &count)) error = errno;
            if (!error) {
                s->state = 3;
                metadata(s);
                bits |= 1;
            } else {
                s->error = error;
                shut(s);
            }
        }
        /* Try every resolver answer, e.g. localhost IPv6 followed by IPv4. */
        while (s->state == 2 && s->fd < 0 && s->next) {
            struct addrinfo *address = s->next;
            s->next = address->ai_next;
            s->fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (s->fd < 0) {
                s->error = errno;
                continue;
            }
            if (fcntl(s->fd, F_SETFL, O_NONBLOCK) < 0 ||
                fcntl(s->fd, F_SETFD, FD_CLOEXEC) < 0) {
                s->error = errno;
                shut(s);
                continue;
            }
#ifdef SO_NOSIGPIPE
            int one = 1;
            if (setsockopt(s->fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one))) {
                s->error = errno;
                shut(s);
                continue;
            }
#endif
            int connected = connect(s->fd, address->ai_addr, address->ai_addrlen);
            if (!connected) {
                s->state = 3;
                metadata(s);
                bits |= 1;
            } else if (errno != EINPROGRESS) {
                s->error = errno;
                shut(s);
            } else {
                return 0;
            }
        }
        if (s->state == 2 && s->fd < 0) {
            return fail(s, s->error ? s->error : ECONNREFUSED);
        }
    }
    if (s->state != 3 || (bits & 1)) return bits;
    if (s->nt > s->offset) {
        size_t count = s->nt - s->offset;
        if (count > 65536) count = 65536;
#ifdef MSG_NOSIGNAL
        ssize_t written = send(s->fd, s->tx + s->offset, count, MSG_NOSIGNAL);
#else
        ssize_t written = send(s->fd, s->tx + s->offset, count, 0);
#endif
        if (written > 0) {
            s->offset += written;
            s->sent = written;
            bits |= 4;
            if (s->offset == s->nt) s->nt = s->offset = 0;
        } else if (written < 0 && errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
            return bits | fail(s, errno);
        }
    }
    unsigned char buffer[65536];
    if (s->nr < LIMIT) {
        size_t count = LIMIT - s->nr;
        if (count > sizeof(buffer)) count = sizeof(buffer);
        ssize_t received = recv(s->fd, buffer, count, 0);
        if (received > 0) {
            void *grown = realloc(s->rx, s->nr + received);
            if (!grown) return bits | fail(s, ENOMEM);
            s->rx = grown;
            memcpy(s->rx + s->nr, buffer, received);
            s->nr += received;
            bits |= 2;
        } else if (!received) {
            s->eof = 1;
            s->state = 4;
            shut(s);
            bits |= 8;
        } else if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
            return bits | fail(s, errno);
        }
    }
    return bits;
}

int cx_write(void *p, const char *bytes, int64_t count) {
    cx *s = p;
    if (count < 0 || count > LIMIT || s->nt - s->offset > LIMIT - (size_t)count) return 0;
    size_t left = s->nt - s->offset;
    unsigned char *grown = malloc(left + count);
    if (!grown && left + count) return 0;
    if (left) memcpy(grown, s->tx + s->offset, left);
    if (count) memcpy(grown + left, bytes, count);
    free(s->tx);
    s->tx = grown;
    s->nt = left + count;
    s->offset = 0;
    return 1;
}

void cx_purge(void *p) {
    cx *s = p;
    s->nt = s->offset = 0;
}

int64_t cx_value(void *p, int key) {
    cx *s = p;
    switch (key) {
        case 0: return s->state;
        case 1: return s->error;
        case 2: return s->nr;
        case 3: return s->nt - s->offset;
        case 4: return s->sent;
        case 5: return s->eof;
        case 6: return s->localport;
        case 7: return s->fd;
        default: return 0;
    }
}

void *cx_data(void *p) {
    return ((cx *)p)->rx;
}

void cx_consume(void *p, int64_t count) {
    cx *s = p;
    if (count <= 0 || (uint64_t)count > s->nr) return;
    memmove(s->rx, s->rx + count, s->nr - count);
    s->nr -= count;
}

const char *cx_address(void *p, int remote) {
    cx *s = p;
    return remote ? s->remote : s->local;
}
