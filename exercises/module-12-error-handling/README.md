# Module 12 — Error Handling and Parsing

## For you

### Goal

Parse replay events with useful diagnostics.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Implement a parser for the text event grammar in the capstone README. Parse one line into an owning typed record or a structured error with line number, field position when applicable, and reason. Reject invalid syntax and numeric ranges without modifying caller-owned book state. State-dependent validation belongs to the future book.

Use a C++20 result representation of your choice; std::expected is not available in the required language version. Choose boundaries for recoverable invalid input versus resource/I/O failures. Compare an exception-based interface in a short design explanation, not a second full parser. Do not mark operations noexcept if they can propagate allocation failures.

The event grammar is specified in [the capstone contract](../module-15-order-book-replay/README.md#input-contract).

### Check

Valid records and missing/extra fields, numeric limits/overflow, signs, trailing junk, invalid tags and blank lines. Results survive destruction of the input string. Diagnostics identify the failing location.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: FIX, binary parsing, book implementation, a custom general-purpose expected library or blanket exception bans.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–11.

Teaching focus: Structured results, optional versus diagnostic errors, exceptions/noexcept, from_chars, numeric bounds and string_view lifetimes.

Project connection: A reusable input contract for replay.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
