# Module 11 — Undefined Behavior and Debugging

## For you

### Goal

Repair an unfamiliar processing component.

### Steps

1. Investigate the supplied challenge and add focused regression checks.
2. Say **“review”** when ready; the teacher handles correctness and C++ quality checks.
3. Give a difficulty rating, answer the short quiz (or skip), then say **“continue”** when ready.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Investigate and repair the supplied event-processing component independently. Add regression tests and explain each violated invariant or language rule.

Use warning/debug and optimized builds plus ASan/UBSan. Use a debugger to inspect relevant state, and compiler output when needed to explain a discrepancy.

### Check

Reproducible failures, justified fixes and regression tests covering each issue. Explain what clean sanitizer results do and do not establish.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: A second duplicate debug assignment, exhaustive UB puzzles or mandatory MSan on unsupported platforms.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–10.

Teaching focus: Lifetime/bounds, signed overflow, aliasing/alignment, optimizer assumptions, debugger use and sanitizer limitations.

Project connection: Investigate integration failures independently.

Generate the full challenge and failing inputs when reached, calibrated to the latest difficulty rating. This is the combined implementation/debugging assignment; do not create a second challenge or expose defect locations.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
