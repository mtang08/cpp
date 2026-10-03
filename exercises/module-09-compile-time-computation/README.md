# Module 9 — Compile-Time Computation

Status: specified, not started. Prerequisites: Modules 1–8; proceed in sequence.

## New learning

constexpr, consteval, static_assert, simple traits and the distinction between constant evaluation and runtime execution.

## Exercise: Validated event metadata

Define metadata for the three replay event kinds ADD, CANCEL and EXECUTE, including a unique code and expected field count. Build a compile-time validated table that rejects duplicate codes or missing kinds. Provide lookup usable in constant expressions and at runtime; unknown runtime codes must produce an explicit no-result value.

Choose the representation. Keep it small enough to explain directly; use compile-time machinery only to enforce a real invariant.

Use the uppercase names as text codes. Field counts include the event tag: ADD has 5 fields, CANCEL 2, and EXECUTE 3, matching [the capstone input contract](../module-15-order-book-replay/README.md#input-contract).

## Verification and review

Compile-time success/failure examples for metadata invariants and runtime checks for each kind and unknown codes. Explain constexpr versus consteval and why runtime input still needs validation.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: A general metaprogramming library, parser implementation, forced compile-time optimization of all logic.

Capstone connection: Consistent protocol metadata.
