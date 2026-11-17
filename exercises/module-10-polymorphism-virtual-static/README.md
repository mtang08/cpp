# Module 10 — Polymorphism and Dispatch Choices

## For you

### Goal

Compare event-handler boundaries.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Implement a small handler for already typed ADD, CANCEL and EXECUTE records in two forms: an interface with virtual dispatch and a variant-based representation with visitation. Each produces counts and total quantities by event kind, with the same overflow/error behavior. It does not maintain an order book.

Choose ownership and APIs, run equivalent inputs through both, and explain the changes needed to introduce a fourth event kind. Read or inspect a short static-dispatch/CRTP example to compare constraints; a third framework is not required. If making runtime speed claims, use Module 8 measurement discipline.

### Check

Equivalent behavioral tests, empty input and destruction/lifetime checks. Justify a preferred boundary for this workload. Virtual dispatch does not imply a fixed penalty or guaranteed branch misprediction.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: A plugin system, mandatory CRTP refactor or a required benchmark win.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–9.

Teaching focus: Virtual interfaces, variant/visit, template dispatch, open versus closed type sets; recognize CRTP and devirtualization.

Project connection: Choose abstractions according to extension and ownership needs.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
