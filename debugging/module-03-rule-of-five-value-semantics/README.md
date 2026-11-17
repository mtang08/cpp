# Module 3 — The Rule of Five and Value Semantics

## For you

### Goal

Investigate unexpected work during Packet ownership transfers.

### Steps

Archived challenge; no new work is assigned here.

### Build

- Copies own independent storage and preserve the source.
- Transfers into new or existing objects allocate nothing and copy no elements.
- Transferred-from objects have size zero and remain safe to destroy, copy, or assign to.
- Self-copy preserves contents; self-move leaves a valid object.
- Vector growth preserves contents without copying packet storage.
- Pass normal and sanitizer checks; add missing edge-case checks.

### Check

Run `make run` and `make run-sanitized`. Preserve the harness, counters and raw owning storage; explain the behavior before fixing it.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Completed challenge. Preserve the original artifacts and session record; do not restart it.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
