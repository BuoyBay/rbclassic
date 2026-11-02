# REALbasic adapters — ClassicCanvas, View containers

RBClassic helps port legacy RB desktop code. It adds
classic member names and checked behavior over ClassicCanvas, View-based ClassicContainerControl, existing native controls, and ProcessKit. It is a supported subset with
explicit source rewrites, rather than a drop-in implementation of the entire
historical framework.

## Install

From a Buoy consumer project with BPM installed:

```sh
bpm add rbclassic --git https://github.com/BuoyBay/rbclassic.git --rev refs/heads/main
```

BPM records the resolved commit in its lockfile. Keep that lockfile with the
consumer project for reproducible installs.
BPM also resolves `processkit`.

## API entrypoints

- `Import rbclassic`
- `BUOY`
- `Len`
- `Mid`
- `InStr`

## Build from source

With the native `build-packages` driver from [devtools](https://github.com/BuoyBay/devtools)
on your `PATH`, run from this checkout:

```sh
build-packages --root "$PWD" --compile-consumer rbclassic
```

The driver checks source targets and compiles an import consumer. See the
[API guide](docs/API.md) for behavior, limits and any host prerequisites.

## Local Buoy setup

On your own machine, install Buoy and run:

```sh
buoy ai init --both
```

## Contributing

[Contributing](CONTRIBUTING.md) · [License](LICENSE)
