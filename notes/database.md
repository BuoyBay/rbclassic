# Classic database adapter

## Integration

The entry module should `Public Import ClassicDatabase`. There are no exported global functions requiring selective imports. Exported classes are `ClassicSQLiteDatabase`, `ClassicDatabaseRecord`, `DatabaseField`, `RecordSet`, `ClassicSQLitePreparedStatement`, and `ClassicEditableRecord`. The module imports only `Xojo`, avoiding entry-module cycles. Internal row bridges are not exported.

Rewrite legacy SQLiteDatabase and DatabaseRecord constructions/declarations to ClassicSQLiteDatabase and ClassicDatabaseRecord; the foundation already owns the original names. Rewrite SQLitePreparedStatement declarations/constants to ClassicSQLitePreparedStatement. PreparedSQLStatement interface substitution is not implemented. Foundation DatabaseRow, DatabaseColumn, Variant and FolderItem remain usable.

Private explicit SQLite FFI uses the existing Xojo SQLite payload. No new native library or shim is needed. Stage sealed Xojo, Variant, sqlite3, postgres, crypto, regex, xml and zip archives in an isolated `packages/` directory when building outside the repository. Native runtime/linking must still be tested separately on each platform.

## Connection and execution contracts

- Boolean Connect opens DatabaseFile read/write and requires an existing disk file. Nil DatabaseFile opens memory. CreateDatabase creates/opens a disk database, or memory for Nil. Connect(filename) is an extension.
- Error, ErrorCode and ErrorMessage are read-only API1 state. Connect/CreateDatabase, SQLSelect/SQLExecute, InsertRecord and Close clear earlier errors. Prepare and prepared Bind/BindType/BindBlob/BindTextBytes/Reset/execution also use the owner's state. Native failures preserve SQLite return codes and messages. Adapter failures use their exception code or -1. Select/Prepare/OpenEditableRecord return Nil on error; execution returns normally with Error set. Snapshot field access and staging errors throw.
- SQL calls accept explicit Variant values; Variant.Empty means NULL. SQLSelectBound/SQLExecuteBound accept an array. Distinct array names avoid the compiler's ParamArray/Array overload collision. Every parameter count, bind status and step result is checked. Oversized UInt64 and unsupported object values fail explicitly.
- One SQL statement per call. Trailing whitespace is accepted; a second statement or a trailing comment after a terminated statement fails before execution. SQLSelect accepts only read-only statements with result columns; DML RETURNING is rejected. SQLExecute can consume returned rows.
- Explicit BEGIN/COMMIT/ROLLBACK work with real SQLite semantics. Close is idempotent. With live prepared statements it preserves SQLite BUSY (5) and keeps the connection open; close the statements and retry. A statement retains its database owner, and destruction finalizes its native handle. A successful close/reopen invalidates existing editable sessions.
- IsConnected, LastRowID and Changes do not reset errors. LastRowID/Changes throw when disconnected. ClearError, SaveError and ConnectionRevision are public plumbing needed by the companion classes in this module; applications should use the operation APIs.

## Buffered records and values

SQLSelect buffers the complete result, including native field bytes, and returns no partial result if a later step fails. Results start at the first row; empty results have BOF/EOF true and preserve FieldCount. MoveNext/Previous/First/Last and RecordCount are supported. IdxField is one-based; named lookup ignores case. Invalid row/index/name access throws. Duplicate result names ignoring case fail and require SQL aliases. Close is idempotent; closed navigation and boundary access throw.

Fields are independent read-only snapshots that survive navigation, statement reuse/finalization and connection closure. Name, Value, StringValue/GetString, IntegerValue, Int64Value, DoubleValue and BooleanValue remain available for scalar data. NULL uses a real empty Variant and converts to empty/zero/false; Boolean text recognizes True/False ignoring case and 1/0. Other conversions retain DatabaseColumn rules, including numeric parse fallback to zero and Double truncation.

New explicit metadata/accessors:

- SQLiteStorageType is SQLite's actual per-row type: INTEGER=1, FLOAT=2, TEXT=3, BLOB=4, NULL=5. These are not legacy DatabaseField.Type codes.
- DeclaredType comes directly from sqlite3_column_decltype; expression fields may have an empty declaration. It is not an inferred affinity or legacy field type.
- IsNull distinguishes NULL from empty TEXT/BLOB without forcing a Variant conversion.
- NativeBytes returns a copied Bytes buffer for TEXT or BLOB. BlobBytes requires BLOB. Binary output and text containing NUL are preserved by explicit Ptr FFI and byte lengths. Scalar access to BLOB throws TypeMismatchException; scalar access to NUL-containing TEXT throws UnsupportedOperationException. Neither silently becomes NULL or a truncated string. Numeric/NULL NativeBytes access throws.

TableSchema(tableName) is an extension returning SQLite's real main-schema table_info fields (`cid`, `name`, `type`, `notnull`, `dflt_value`, `pk`). Its name is bound as data, not interpolated SQL. Tables returns main-schema user table names. These are not a claim of exact legacy FieldSchema/TableSchema row-column parity.

ClassicDatabaseRecord retains string Column(name)/one-based Column(index), zero-based FieldName, FieldCount, IntegerColumn/Int64Column/DoubleColumn/BooleanColumn setters/getters and SetValue for NULL/supported Variant values. InsertRecord accepts it or a foundation DatabaseRow, quotes identifiers, binds values and handles DEFAULT VALUES. Binary inserts/updates use the prepared Bytes APIs; DbValue and Variant have not gained a binary kind.

## Explicit editing

Arbitrary RecordSet.Edit/Update/DeleteRecord still throw; SELECT updatability is never guessed. OpenEditableRecord(tableName, primaryKey, key) is an explicit extension for a single row in an ordinary main-schema table. It requires an exact single-column declared primary key and a supported non-NULL scalar key. Views, virtual tables, composite keys, unique-but-not-primary fields, missing rows and ambiguous identities fail. Main-schema qualification prevents temporary-table shadowing.

ClassicEditableRecord.Field returns the original read-only snapshot. SetValue stages named scalar/NULL changes; column lookup is checked and primary-key edits fail. Update and DeleteRecord revalidate the schema/identity inside a savepoint, quote all identifiers, bind values, require exactly one affected row and roll back failed changes while preserving the original error. The savepoint nests inside caller transactions. A successful change closes the session; a failed constraint permits correcting staged values and retrying. Close cancels staging. A closed/reopened connection cannot receive stale session writes.

This is a single-thread, short-lived edit session, not optimistic concurrency control. It does not compare the original non-key values; another writer's scalar changes can be overwritten, and deletion/reinsertion with the same key denotes the current identity. Do not interleave schema changes or connection operations across threads. SQLite trigger effects retain SQLite's own semantics. Binary edits use parameterized prepared SQL rather than SetValue. Full mutable DatabaseField setters, arbitrary SELECT edits, composite identities and automatic edit-buffer refresh remain out of scope.

## Remaining limits

Buffered results consume memory proportional to the full result. Strings/paths/SQL/identifiers must not contain embedded NUL; use Bytes only for data. Legacy BlobValue/NativeValue String properties, legacy Type/FieldType numeric codes, exact legacy schema-result shapes, rich date/picture/currency types, encryption, backups, busy-timeout configuration, server adapters, async execution and cross-thread synchronization remain unsupported. Missing members fail at compile time. Bundled SQLiteRowSet still loses native errors; this adapter therefore retains its own checked execution path without editing the foundation.

## Primary references

- [Archived RecordSet](https://documentation.xojo.com/versions/2022r3/api/deprecated/recordset.html), [DatabaseField](https://documentation.xojo.com/versions/2022r3/api/deprecated/databasefield.html), [DatabaseRecord](https://documentation.xojo.com/versions/2022r3/api/deprecated/databaserecord.html), and [SQLiteDatabase](https://documentation.xojo.com/versions/2022r3/api/databases/sqlitedatabase.html).
- [Archived SQLitePreparedStatement](https://documentation.xojo.com/versions/2022r3/api/databases/sqlitepreparedstatement.html) and [PreparedSQLStatement](https://documentation.xojo.com/versions/2022r3/api/databases/preparedsqlstatement.html), consulted for zero-based Bind and convenience binding precedence.
- SQLite [binding and lifetimes](https://www.sqlite.org/c3ref/bind_blob.html), [column values](https://www.sqlite.org/c3ref/column_blob.html), [declared types](https://www.sqlite.org/c3ref/column_decltype.html), [step errors](https://www.sqlite.org/c3ref/step.html), [savepoints](https://www.sqlite.org/lang_savepoint.html), and [PRAGMA table_info](https://www.sqlite.org/pragma.html#pragma_table_info).
- Local `/usr/share/buoy/docs/documentation/{bytes,database,ffi-declare,exceptions,paramarray,sized-integers}.md`, actual shipped XojoDatabase/SQLite3 modules, and `.claude/skills/buoy-syntax/SKILL.md`.
