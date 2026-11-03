# Progress

## Current Module

- Module 4 — implementation checkpoint accepted; focused debugging is next. Remaining test evidence is recorded under M04-006.

## 2026-10-10 — Implementation checkpoint handoff

- Implemented `UniqueBuffer`, `BufferSlot`, forwarding relay, factory, and a populated test harness. Ownership and forwarding bugs were corrected after review guidance.
- Verification: `make run`, `make run-sanitized`, and `make run-no-elide` passed. An independent compile probe confirmed plain-lvalue relay calls fail through the deleted copy constructor. The intentional self-move test produces a compiler warning.
- Review state: M04-001 through M04-005 resolved; M04-006 remains open for incomplete acceptance evidence. Passing builds do not cover every specified check.
- Accepted this implementation checkpoint after the learner requested less repetitive testing and a focus on new concepts. No further testing drills assigned; this does not mark the remaining test evidence verified or the whole module complete.
- Mistakes:
  - Initially omitted the template argument to `std::forward`, then hardcoded `UniqueBuffer` instead of preserving the deduced `T`.
  - Expected a populated result after clearing the slot, then tried to repopulate it using an already moved-from buffer.
- Conventions learned:
  - Applied `std::forward<T>` to preserve the caller's value category; named parameters are lvalue expressions.
  - Distinguished zero-valued bytes from an empty buffer.
  - Used specific exception catches and explicit checks in tests.
  - Explained with prompts that `std::move` preserves constness, preventing binding to the non-const move constructor.
  - Identified NRVO and implicit movement as the two paths supporting the factory's return by value.
  - Explained that slot replacement releases the old allocation and invalidates saved byte pointers; a `peek()` reference still observes the live slot's buffer object.
- Next action: prepare Module 4's focused debugging challenge when requested. Prior difficulty rating: 1; make it harder, provide the full challenge up front, and allow independent investigation.

## 2026-10-10 — Initial implementation checkpoint

- Reviewed Module 4 without modifying implementation behavior. Findings M04-001 through M04-006 are recorded inline; see [review workflow](reviews.md).
- Mistakes:
  - Byte storage is not zero-initialized; destructor mismatches array allocation.
  - Move assignment loses the destination's previous allocation.
  - Default slot is nonempty; relay loses the caller's value category.
- Conventions learned:
  - Review findings now use dated, stable IDs with explicit status and kind for later reporting.
- Verification: normal, sanitized, and no-elide builds pass an empty harness only. An independent compile probe confirms relay rejects a temporary through the deleted copy constructor.
- Paused at the requested checkpoint. Acceptance tests and findings remain outstanding; module is not complete.
- Re-review: M04-001, M04-002, and M04-003 resolved after learner fixes; an independent ASan/UBSan probe checked zero initialization, destruction, and assignment transfers. M04-004, M04-005, and M04-006 remain open.
- Reworded the existing verification requirements as concrete actions and expected results; no scope added.
- Further re-review: M04-004 and M04-005 resolved. Normal, sanitizer, and no-elide targets pass the populated harness. An independent plain-lvalue relay call is rejected as required. M04-006 remains open for missing acceptance evidence; its inline description now reflects the current tests.

## 2026-10-03 — Learning direction

- Recorded goals, role interests, prior systems study, and reading plans in [context/README.md](context/README.md); consult it before curriculum planning.
- Decided on C++ foundations first, followed by an order-book replay capstone that can grow into trading infrastructure. Python is outside the current curriculum.
- Completed the detailed curriculum revision and exercise contracts for Modules 4–15. Module 4 remains active with its existing API and build targets; its spec now clarifies handoff/observer lifetimes and completion boundaries.
- Future debugging READMEs define scope; generate challenges only when reached. Module 11 combines implementation and debugging into one assignment. Networking, order entry, concurrency, and recovery follow the initial capstone.
- Next action: implement and test Module 4, request review, then complete its calibrated debugging session before advancing. Prioritize momentum through the stated requirements; avoid extra drills.

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
