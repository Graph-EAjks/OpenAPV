# OpenAPV Shared Library Versioning Guidelines

This document outlines the versioning rules for the shared library in the OpenAPV project, following the Semantic Versioning (SemVer) convention.

## Versioning Scheme

The version of the library is defined by three numbers:

- `LIBVERSION_MAJOR`
- `LIBVERSION_MINOR`
- `LIBVERSION_PATCH`

### LIBVERSION_MAJOR

Increment this number when:
- You introduce changes that are not backward-compatible (breaking changes). This means that changes to the API or the library's behavior may cause existing code that relies on this library to stop working.

**Examples:**
- Removing functions
- Changing function signatures
- Altering the behavior of functions in a way that affects users

### LIBVERSION_MINOR

Increment this number when:
- You introduce new features that are backward-compatible. This means that the new version of the library adds new functions or fixes but does not affect existing code.

**Examples:**
- Adding new functions
- Adding new methods that do not conflict with the existing API

### LIBVERSION_PATCH

Increment this number when:
- You make bug fixes or minor changes that are backward-compatible. This means that these changes do not introduce new features or alter the existing API.

**Examples:**
- Fixing bugs
- Improving performance
- Correcting documentation

## Version Storage

The library version is stored in the file `version_library.txt` in the following format:
```
v[VERSION_MAJOR].[VERSION_MINOR].[VERSION_PATCH]
```

The string must match the following regular expression pattern:
```
^([vV])([0-9]+)([.])([0-9]+)([.])([0-9]+)$
```

## Example

If the current version is `1.2.3`:
- Changing to `1.3.0` indicates the addition of new features (minor).
- Changing to `2.0.0` indicates the introduction of backward-incompatible changes (major).
- Changing to `1.2.4` indicates a bug fix (patch).

These rules will help maintain consistency and clarity in version management for the library, which is crucial for users and developers working with the OpenAPV project.

## Additional Resources

- [Semantic Versioning](https://semver.org/)
- [Software Versioning - Wikipedia](https://en.wikipedia.org/wiki/Software_versioning)

# OpenAPV Project Versioning Guidelines

This document outlines the versioning rules for the OpenAPV project, following the Semantic Versioning (SemVer) convention.

## Versioning Scheme

The version of the project is defined by three numbers:

- `VERSION_MAJOR`
- `VERSION_MINOR`
- `VERSION_PATCH`

### VERSION_MAJOR

- The major version will be incremented for major releases. This indicates significant changes that may include breaking changes or substantial new features.

### VERSION_MINOR

- The minor version will be incremented for development releases, specifically when a new release is issued.

### VERSION_PATCH

- The patch version will be incremented for fixing and patching releases. This indicates backward-compatible bug fixes or minor improvements to the existing release.

## Version Storage

The project version is stored in the file `version.txt` in the following format:

 in the following format:
```
v[VERSION_MAJOR].[VERSION_MINOR].[VERSION_PATCH]
```

The string must match the following regular expression pattern:
```
^([vV])([0-9]+)([.])([0-9]+)([.])([0-9]+)$
```