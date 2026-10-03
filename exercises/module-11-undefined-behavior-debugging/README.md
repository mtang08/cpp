# Module 11 — Undefined Behavior and Debugging

Status: specified, not started. Prerequisites: Modules 1–10; proceed in sequence.

## New learning

Lifetime/bounds, signed overflow, aliasing/alignment, optimizer assumptions, debugger use and sanitizer limitations.

## Exercise: Repair an unfamiliar processing component

This module is one combined implementation/debugging challenge. When it starts, the assistant supplies a compact unfamiliar event-processing component, observable behavior requirements and failing inputs, calibrated to the latest difficulty rating. Investigate and repair it independently, add regression tests and explain each violated invariant or language rule.

Use warning/debug and optimized builds plus ASan/UBSan. Use a debugger to inspect relevant state, and compiler output when needed to explain a discrepancy. Generate actual defects just in time, without describing their locations or fixes in advance.

## Verification and review

Reproducible failures, justified fixes and regression tests covering each issue. Explain what clean sanitizer results do and do not establish.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: A second duplicate debug assignment, exhaustive UB puzzles or mandatory MSan on unsupported platforms.

Capstone connection: Investigate integration failures independently.
