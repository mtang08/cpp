# Module 13 — Ownership and API Design

## For you

### Goal

A replay session with explicit dependencies.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Design a session that pulls text lines from a source, parses them using Module 12 and sends accepted typed records to a sink. Inject source/sink dependencies so tests can use in-memory substitutes. Use a trivial collecting/counting sink, not a book. Decide and document which objects the session owns and which it borrows.

Support run-to-end and explicit reset/replacement between runs. Invalid lines are reported and skipped. Source/sink failures stop processing and produce a failure result; already delivered records remain delivered. Destruction must release owned resources. Define whether retry requires a new source; do not silently deliver a record twice. Explain when shared ownership would be justified, without forcing it into this design.

### Check

Test empty sources, invalid lines, source/sink failures, replacement, teardown and observer lifetimes. Explain construction/destruction order and any copy/move restrictions.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: Custom smart pointers, manufactured cycles, required pimpl, concurrency and full book implementation.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–12.

Teaching focus: Rule of Zero, unique ownership, observing references/pointers, shared_ptr costs, weak_ptr, factories and sink parameters.

Project connection: Clear ownership for later connections and sessions.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
