# Module 9 — Compile-Time Computation

## For you

### Goal

Validated event metadata.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Define metadata for the three replay event kinds ADD, CANCEL and EXECUTE, including a unique code and expected field count. Build a compile-time validated table that rejects duplicate codes or missing kinds. Provide lookup usable in constant expressions and at runtime; unknown runtime codes must produce an explicit no-result value.

Choose the representation. Keep it small enough to explain directly; use compile-time machinery only to enforce a real invariant.

Use the uppercase names as text codes. Field counts include the event tag: ADD has 5 fields, CANCEL 2, and EXECUTE 3, matching [the capstone input contract](../module-15-order-book-replay/README.md#input-contract).

### Check

Compile-time success/failure examples for metadata invariants and runtime checks for each kind and unknown codes. Explain constexpr versus consteval and why runtime input still needs validation.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: A general metaprogramming library, parser implementation, forced compile-time optimization of all logic.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–8.

Teaching focus: constexpr, consteval, static_assert, simple traits and the distinction between constant evaluation and runtime execution.

Project connection: Consistent protocol metadata.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
