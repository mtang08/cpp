# Module 14 — Testable and Maintainable C++

Status: specified, not started. Prerequisites: Modules 1–13; proceed in sequence.

## New learning

Dependency boundaries, multi-translation-unit builds, CMake/CTest, deterministic tests, CLI contracts and failure propagation.

## Exercise: Package a replay skeleton

Integrate the parser and session into a library, CLI executable and test target. The CLI reads one input file and reports accepted/rejected counts using a simple sink. Keep parsing and processing testable without subprocesses; add a small CLI integration test. Refactor boundaries when testing reveals coupling.

Provide CMake debug, sanitizer and release build instructions with out-of-tree builds and CTest. Understand the build targets yourself; the assistant may help with setup. Exit zero for successful processing of valid input, nonzero for rejected input or operational failure; diagnostics go to stderr. Document the exit codes. Ensure test checks remain active in release builds.

## Verification and review

Clean build and test instructions work; tests cover valid/invalid input, unavailable files and injected sink failure. Explain public headers, dependency direction, linking and test isolation.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: A framework, a build-system survey, mandatory external test packages or implementing the book early.

Capstone connection: A maintained application foundation for the capstone.
