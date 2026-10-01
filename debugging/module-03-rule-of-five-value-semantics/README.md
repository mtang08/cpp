# Module 3 — The Rule of Five and Value Semantics

`Packet` owns integers. Its values look correct, but ownership transfers do unexpected work.

Run `make run`, investigate, and explain the behavior before fixing the class. Keep the harness and counters; retain raw owning storage for this challenge.

Requirements:
- Copies own independent storage and preserve the source.
- Transfers into new or existing objects allocate nothing and copy no elements.
- Transferred-from objects have size zero and remain safe to destroy, copy, or assign to.
- Self-copy preserves contents; self-move leaves a valid object.
- Vector growth preserves contents without copying packet storage.
- Pass normal and sanitizer checks; add missing edge-case checks.
