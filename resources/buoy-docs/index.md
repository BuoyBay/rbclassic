---
title: "rbclassic Overview"
summary: "Explicit REALbasic and Xojo API 1 adapters over Buoy and the bundled Xojo shim"
category: "Guide"
symbols: ["ClassicDate", "ClassicSQLiteRows", "DatabaseField", "RecordSet", "ClassicDatabaseRecord", "ClassicSQLiteDatabase", "ClassicPicture", "ClassicRGBSurface", "ClassicGraphics", "ClassicCanvas", "ClassicTimer", "ClassicUDPSocket", "ClassicShell"]
related: ["getting-started.md", "api.md", "typed-api.md"]
---

# rbclassic

Explicit REALbasic and Xojo API 1 adapters over Buoy and the bundled Xojo shim

[Getting started](getting-started.md) · [API contracts](api.md) · [Typed API](typed-api.md)


[Explicit dynamic-value transport](dynamic-values.md) describes lossless extended-value boxing and optional scalar conversion.

## Compatibility mapping

- [Every maintained adapter API](legacy-api-map.md)
- [Installed foundation APIs](foundation-api-map.md)
- Complete JSON mapping resource: `legacy-api-map.json`

Use `Import rbclassic`. Readable `Lowercase(text)` and `Uppercase(text)` forward directly to native Buoy casing. The installed vendor package retains its external name; only RBFoundation imports it.
