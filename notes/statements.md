# Reusable SQLite statements

The implementation is included in ClassicDatabase.bui. Parent integration needs only `Public Import ClassicDatabase`, exporting ClassicSQLitePreparedStatement and ClassicEditableRecord alongside existing database classes. No global selective imports, separate statement module, new native dependency or entry-module import is needed. See database.md for staging and connection contracts.

## Supported surface

`db.Prepare(sql)` returns ClassicSQLitePreparedStatement or Nil with the database Error state. Preparation happens once with sqlite3_prepare_v2, not once per execution. Bind(index, Variant) uses zero-based indexes. ParameterCount is SQLite's parameter count, so repeated named parameters share one index and numbered parameter holes retain SQLite's own counting rules. BindType accepts symbolic class constants SQLITE_INTEGER, SQLITE_INT64, SQLITE_DOUBLE, SQLITE_BOOLEAN, SQLITE_TEXT, SQLITE_NULL and SQLITE_BLOB. Type selection affects the actual native binder and invalidates a previous binding until rebound. Scalar conversion uses DatabaseColumn rules. NULL values remain NULL for any selected type.

These constants are adapter-local compile-time values, not a promise of Xojo plug-in numeric ABI compatibility. Rewrite symbolic qualifiers to ClassicSQLitePreparedStatement. INTEGER=1, DOUBLE=2, TEXT=3, BLOB=4, NULL=5, INT64=6 and BOOLEAN=7. No stored-only type flag is exposed. Unknown constants fail; BLOB rejects scalar binding. Direct scalar Variant types are inferred when BindType is absent.

BindBlob(index, Bytes) and BindTextBytes(index, Bytes) are explicit extensions. They pass DataPtr plus checked byte lengths and SQLITE_TRANSIENT copying lifetime. Empty BLOB uses sqlite3_bind_zeroblob(0), preserving its distinction from NULL. Empty TEXT remains TEXT. Nil Bytes fails; use Bind(index, Variant.Empty()) for SQL NULL. BindTextBytes validates via the UTF8 Bytes decoder and passes original bytes, including NUL, rather than decoding and re-encoding through String FFI. BLOB values may contain any bytes. Mutating the caller buffer after Bind cannot alter the bound value. Read with DatabaseField.BlobBytes/NativeBytes; do not route through Variant/DbValue.

SQLSelect(ParamArray Variant) returns a buffered RecordSet; SQLExecute consumes all rows and sets database Error state. No-argument calls reuse existing bindings. Nonempty convenience arguments replace the scalar bindings and must exactly match ParameterCount; selected BindType conversions remain in effect. All parameter slots must have been bound, including explicit NULL. A failed bind invalidates that slot, preventing accidental reuse of its prior value. Read-only selection and one-statement restrictions match the database APIs.

Execution captures SQLite's exact step error before resetting the native statement. Reset after each run preserves bindings for reuse, including after a constraint failure. Reset() explicitly resets while retaining bindings; Reset(True) clears bindings and requires all slots to be rebound. Close is idempotent and finalizes the handle; destruction does the same. Closed execution reports SQLITE_MISUSE (21). ParameterCount on a closed statement throws. Close itself does not clear the owner's previous error. Live statements retain their database owner and make database Close return BUSY until finalized.

Legacy SelectSQL/ExecuteSQL RowSet aliases, the PreparedSQLStatement interface, arbitrary numeric plug-in constants, multi-command prepared statements, implicit binary Strings, and mutable DatabaseField properties are not provided. API1 SQLSelect/SQLExecute shapes are the tested surface.

## Roadmap work completed in this scope

- Reusable native preparation with checked Bind/BindType and API1 execution methods.
- Exact step/bind/prepare errors, statement reset/recovery/finalization, and safe connection lifetime.
- Real SQLite table/primary-key and field storage/declaration metadata via explicit extensions.
- Binary and NUL-safe TEXT data bindings and buffered snapshots using Bytes and Ptr FFI.
- Explicit single-column-primary-key editing with schema revalidation, identifier quoting, one-row checks, savepoint rollback, and connection identity guards.

Arbitrary SELECT editing, composite/binary identities, legacy field-type codes and full schema-result parity remain open; these are not foundation/core changes hidden behind stored flags. Parent owns final roadmap reconciliation, entry exports, packaging and integrated tests.

## Behavior tests and evidence

`tests/classic_statements_test.bui` has independent assertions against literal fixtures, SQLite typeof results, exact errors and subsequent SQL reads. It covers:

- Disconnected/invalid/multiple-statement preparation; missing/excess/negative binds; convenience counts and native repeated named markers.
- Actual native TEXT/REAL/INTEGER/NULL/BLOB type changes, 64-bit and Boolean bindings, invalid type selections, invalid UTF8 rejection, Bytes/type mismatches and stale-bind prevention.
- BLOB fixture `00ff610062c3a9`, UTF8/NUL TEXT fixture `61c3a90062`, empty TEXT/BLOB versus NULL, independent output copies and copied input buffers.
- Repeated execution, constraint recovery and exact `UNIQUE constraint failed: payloads.label`, later-step integer-overflow errors, clear/retained bindings, snapshot survival across reuse and all native lifetimes, double Close, and destructor finalization.
- Real table_info primary-key/type results, safe schema-name binding, table enumeration and empty-result field counts.
- Parameterized updates, failed update atomicity, explicit transaction rollback, SQLSelect mutation rejection and BUSY-safe connection closure.
- Explicit editable sessions: rejected wrong/composite keys, NULL/missing identities and views; main-schema isolation under temporary-table shadowing; rejected unknown/key edits; exact constraint error and atomic multi-column changes; retry inside outer transactions; quoted table/key/value identifiers; update/delete persistence; single-use success; removed rows, changed schema without mass mutation, and close/reopen identity protection.

Compiler command/results and isolated package/build instructions are in database.md. Fresh final checks cover the module and both tests across all six target triples; native Linux builds/runs pass. Cross-target semantic checks do not certify foreign SQLite ABI execution. No new candidate upstream issue was necessary, and no external issue was published.
