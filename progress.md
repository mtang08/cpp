# Progress

## Current Module

- Module 4 implementation — Move Semantics Deep Dive.

## 2026-10-01

- Prepared the Module 4 `UniqueBuffer` handoff exercise with complete requirements and build support. Independent implementation first; review on request.
- Completed Module 3 debugging; see `debugging/module-03-rule-of-five-value-semantics/session-2026-10-01.md`.
- Mistakes:
  - Assumed `std::move` guarantees move construction regardless of available constructors.
  - Initially used an inequality instead of verifying the source's exact preserved value.
- Conventions learned:
  - Rvalues can bind to a copy constructor's `const T&` parameter.
  - Ownership transfer leaves a valid source; this challenge specifically requires an empty source.
  - `noexcept` move construction enables vector relocation without packet copies.
  - Copy assignment can restore a moved-from object; test independent storage afterward.
- Verification: normal and ASan/UBSan checks passed, including moved-from destination reuse.
- Debugging difficulty rating: 1; next challenge should be harder with no scaffolding.
- Debugging flow: give the full challenge up front, then allow independent work. Discuss at review or when help is explicitly requested; avoid conversational checkpoints.

## 2026-07-10

- Next session: run the Module 3 debugging challenge.
- Calibration: previous debugging difficulty rating was 1, so start colder and harder with minimal scaffolding.

## 2026-07-04

- Completed Modules 1 and 2.
- Mistakes:
  - Mixed up const object type versus const reference type.
  - Initially treated a dangling reference as if the reference extended local object lifetime.
  - Confused pointer variable lifetime with pointee lifetime.
  - Needed sharper distinction between owning pointers and non-owning observation.
- Conventions learned:
  - Use `const T&` for read-only non-owning parameters.
  - Return locally created objects by value, not by reference.
  - Use RAII to make cleanup automatic instead of manually pairing raw `new[]`/`delete[]`.
  - After `delete`, a raw pointer still holds the old address unless reassigned.
  - Debugging difficulty rating: 1; next debugging session should be harder with less scaffolding.

## 2026-07-07

- Started Module 3.
- Added the implementation-first `DynamicArray` exercise spec in `exercises/module-03-rule-of-five-value-semantics/README.md`.
- Wrote the initial `DynamicArray` implementation.
- Mistakes:
  - Left `data_` uninitialized for zero-capacity construction.
  - Did not handle growth from zero capacity.
  - Copied allocated capacity instead of logical size.
  - Used capacity-valid indices in tests when only size-valid indices are valid.
- Conventions learned:
  - `size_` is logical element count; `capacity_` is allocated storage.
  - Valid element access requires `index < size_`.
  - Class methods can access private fields of any object of the same class.
  - Copy/move internals should usually access private fields directly.

## 2026-07-09

- Addressed review comments and completed Module 3.
- Ran `make run` and `make run-sanitized` successfully for `exercises/module-03-rule-of-five-value-semantics`.
- Mistakes:
  - Initially tested construction when assignment was intended.
  - Copy assignment committed state too early for exception safety.
  - Copying from an empty array needed explicit zero-capacity handling.
  - Moved-from objects need query-validity checks, not just destination checks.
- Conventions learned:
  - Compare object identity with `this == &other`.
  - `delete[] nullptr` is a no-op.
  - Catch standard exceptions by `const&`.
  - Prefer `value > 0` for numeric clarity; pointer truthiness is idiomatic for pointers.
  - Members are initialized in declaration order, not member-initializer-list order; compilers warn when the written order differs.

## Session Rules

- Work through modules one by one.
- Avoid expanding scope beyond the current module unless explicitly requested.
- From Module 3 onward, make sessions more implementation-heavy: brief concept checkpoints, then substantial build/review/debug cycles.
- Treat exercises like engineering work: define invariants, compile often, run sanitizers, test edge cases, and review API/ownership/design tradeoffs.
- Prefer full module exercise specs up front for implementation work, with phased review checkpoints rather than step-by-step scaffolding.
