# Module 14 — Testable and Maintainable C++

## For you

### Goal

Package a replay skeleton.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Integrate the parser and session into a library, CLI executable and test target. The CLI reads one input file and reports accepted/rejected counts using a simple sink. Keep parsing and processing testable without subprocesses; add a small CLI integration test. Refactor boundaries when testing reveals coupling.

Provide CMake debug, sanitizer and release build instructions with out-of-tree builds and CTest. Understand the build targets yourself; the assistant may help with setup. Exit zero for successful processing of valid input, nonzero for rejected input or operational failure; diagnostics go to stderr. Document the exit codes. Ensure test checks remain active in release builds.

### Check

Clean build and test instructions work; tests cover valid/invalid input, unavailable files and injected sink failure. Explain public headers, dependency direction, linking and test isolation.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: A framework, a build-system survey, mandatory external test packages or implementing the book early.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–13.

Teaching focus: Dependency boundaries, multi-translation-unit builds, CMake/CTest, deterministic tests, CLI contracts and failure propagation.

Project connection: A maintained application foundation for the capstone.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
