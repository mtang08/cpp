# Module 7 — STL Algorithms, Lambdas, and Views

## For you

### Goal

Deterministic event analytics.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Process already validated in-memory records containing instrument name, timestamp, unique sequence number, event kind and quantity. Provide filtering by instrument and a half-open timestamp interval, chronological ordering with sequence-number tie breaking, and per-instrument summaries of event count and quantity sum. Summaries are ordered lexicographically by instrument. Input order is arbitrary; an empty selection produces empty output. Detect aggregate overflow.

Choose your API and standard containers. Use standard algorithms where they fit. The input must remain unchanged and returned results must remain valid after input destruction. Borrow views only within explicitly documented lifetimes. Split public declarations, implementation and a separate test executable; the assistant may provide build support.

### Check

Hand-computed cases for empty input, boundaries, ties, mixed instruments, overflow and input preservation. Explain complexity, comparator correctness and capture/view lifetimes.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: Parsing, order-book state transitions, custom sorting algorithms and a mandatory ranges framework.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–6.

Teaching focus: Algorithm contracts and complexity, strict weak ordering, captures, callable types, span/string_view and borrowed lifetimes.

Project connection: Deterministic batch processing and queries.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
