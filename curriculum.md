# C++ Systems Engineering Curriculum

Revised 2026-10-03. Finish C++ foundations, build an order-book replay application, then grow it toward exchange connectivity and reliable trading infrastructure. See [learning context](context/README.md) for goals, background and reading plans. Python is outside this curriculum.

## Workflow and document ownership

- `context/README.md`: goals and preferences. `curriculum.md`: sequence and scope. Exercise READMEs: behavior and acceptance contracts. `progress.md`: current task and demonstrated learning. `AGENTS.md`: teaching rules. The July critique is historical.
- Work one module at a time. Modules 1–3 remain complete; Module 4 is active. Future specifications are prepared now to give agents the whole progression, not to start parallel assignments.
- Read the full roadmap, current progress and adjacent module specs before preparing/reviewing work. Preserve completed work; identify each module's new contribution instead of repeating prior drills.
- Each module has one bounded implementation exercise and a focused debugging session. Module 11 combines them. Generate buggy code only when its session starts, calibrated to the latest rating; give the full challenge and let the learner investigate independently.
- The learner writes core code and meaningful tests. The assistant may supply build support, fixtures and independent checks. Reviews identify problems without rewriting solutions unless asked.
- Specs define behavior, errors, invariants and acceptance evidence. Increasingly leave API, container and internal layout choices to the learner. Any missing material contract should be resolved before implementation, not introduced as a surprise at review.
- Stop expanding a module when its checks pass and findings are addressed. Do not demand every possible abstraction, a fixed speedup, textbook completion or extra drills before moving on.

## Engineering practice

Use C++20 and `-Wall -Wextra -Wpedantic`. Run normal and ASan/UBSan builds for runnable exercises. Introduce `-Wconversion -Wshadow` from Module 7 and resolve or explain diagnostics. Tests must remain effective with NDEBUG. Keep sanitized and optimized benchmark builds separate.

From Module 7, separate reusable code from tests and introduce headers/sources naturally; templates can remain in headers. Build support may be supplied until Module 14 makes build ownership explicit. Formatting and static analysis support implementation rather than becoming separate projects.

Completion means the behavior and edge cases work, ownership/invariants can be explained, meaningful tests pass, and review issues are resolved. Record whether a skill was demonstrated independently or corrected after feedback. Sanitizers complement reasoning; they do not prove correctness. Use subsequent module requirements to revisit weaknesses naturally.

Performance work follows: correct baseline, defined workload, profiling, one relevant change, correctness recheck and a short report. Document compiler, machine, input and variability. Throughput and latency are different metrics; batch runtime divided by event count is not a measured latency distribution. Linux tooling comes with later systems work; use tools available on the development machine now.

## Roadmap

| Modules | New responsibility | Ready to move on when |
|---|---|---|
| 1–4 | Types, ownership, values and API handoff | Transfers and lifetimes are correct and explainable |
| 5–7 | Generic code, object lifetime and data processing | Choose containers/algorithms and test independent components |
| 8–11 | Measurement, dispatch and debugging | Justify tradeoffs and investigate unfamiliar failures |
| 12–14 | Parsing, dependency ownership and packaging | Deliver a tested multi-file application |
| 15 | Integrated order-book replay | Demonstrate deterministic correctness and measured behavior |
| After 15 | Connectivity, concurrency and recovery | Evolve one working system milestone at a time |

Finish foundations first. After the initial modules, read Effective Modern C++ a couple of hours weekly and apply relevant lessons during project work. OSTEP virtualization/concurrency reading is complete; review of the first five chapters of Top-Down Approach networking is planned. Reading is not a gate on module progress. Interview algorithms and role-specific preparation remain separate from this sequence.

## Completed modules — retain existing work

### Module 1 — Types, References, and const Correctness

Value types and deduction, const, pointers/references and lifetime; compilation/linking and basic execution. Exercise: function interfaces. Completed; retain original artifacts and logs.

### Module 2 — Ownership and RAII

Resource ownership, allocation and deterministic cleanup. Exercise: resource-managing class; debugging ownership failures. Completed. Module 13 applies ownership to component boundaries rather than repeating raw resource management.

### Module 3 — Rule of Five and Value Semantics

Completed int-only DynamicArray with deep copies, moves, growth and valid moved-from states. Module 4 adds API handoff; Module 6 adds generic object lifetime. Do not reassign Module 3.

## Active module

### Module 4 — Move Semantics and Ownership Handoff

[Complete spec](exercises/module-04-move-semantics/README.md). Build UniqueBuffer, BufferSlot, a forwarding relay and a return-by-value factory. New learning: value categories, const interaction, forwarding, implicit moves and elision across APIs. Keep the existing API and raw storage exercise; no extra container features. Complete normal, sanitized and optional-elision-disabled checks and explain rejected calls. Broader template constraints belong to Module 5.

## Remaining foundations

### Module 5 — Templates and Type Deduction

- **New focus:** Function and class templates; deduction, auto/decltype, concepts/requires and if constexpr. Recognize SFINAE in existing code without making enable_if the default.
- **Build:** [Constrained diagnostic formatting](exercises/module-05-templates-type-deduction/README.md).
- **Completion:** Exact-output tests for each category, empty inputs, escapes, negative integers, numeric limits and both container types. Compile-time checks must distinguish supported and unsupported types. Explain why overload/constraint selection treats strings correctly.
- **Boundary:** Full serialization, nested ranges, wire protocols, advanced metaprogramming. Module 4 already owns forwarding practice.
- **Project connection:** Type-safe utilities and readable diagnostics.

### Module 6 — Containers, Storage, and Element Lifetime

- **New focus:** Separate raw storage from live objects; allocator_traits, construction/destruction, relocation, exception guarantees and invalidation. Compare standard container complexity and locality.
- **Build:** [A bounded vector<T> implementation](exercises/module-06-stl-containers-iterators/README.md).
- **Completion:** Use lifetime-counting, non-default-constructible, move-only and copy-throwing test types. Test relocation failure, destruction counts, empty states, bounds and reuse after move. Explain vector/map/unordered_map/deque choices for ID lookup and ordered price queries; implement only this container.
- **Boundary:** Full std::vector compatibility, allocator propagation, custom allocators, copyable container semantics and throwing move-only relocation. This adds object lifetime to Module 3, not another integer array.
- **Project connection:** Understand standard containers before choosing book indexes.

### Module 7 — STL Algorithms, Lambdas, and Views

- **New focus:** Algorithm contracts and complexity, strict weak ordering, captures, callable types, span/string_view and borrowed lifetimes.
- **Build:** [Deterministic event analytics](exercises/module-07-stl-algorithms-lambdas/README.md).
- **Completion:** Hand-computed cases for empty input, boundaries, ties, mixed instruments, overflow and input preservation. Explain complexity, comparator correctness and capture/view lifetimes.
- **Boundary:** Parsing, order-book state transitions, custom sorting algorithms and a mandatory ranges framework.
- **Project connection:** Deterministic batch processing and queries.

### Module 8 — Memory Layout and Performance Measurement

- **New focus:** Alignment/padding, locality, working sets, AoS/SoA, optimized builds, profiling and benchmark validity.
- **Build:** [Profile and compare event layouts](exercises/module-08-memory-layout-cache-performance/README.md).
- **Completion:** Report compiler/options, machine, workload sizes/seeds, repetitions, variability, memory/storage cost and output equivalence. Explain a speedup, slowdown or inconclusive result. A small results table and concise explanation are sufficient.
- **Boundary:** An arbitrary speedup target, SIMD, hardware tuning, custom pools and false-sharing experiments before concurrency.
- **Project connection:** Reproducible evidence for later optimization.

### Module 9 — Compile-Time Computation

- **New focus:** constexpr, consteval, static_assert, simple traits and the distinction between constant evaluation and runtime execution.
- **Build:** [Validated event metadata](exercises/module-09-compile-time-computation/README.md).
- **Completion:** Compile-time success/failure examples for metadata invariants and runtime checks for each kind and unknown codes. Explain constexpr versus consteval and why runtime input still needs validation.
- **Boundary:** A general metaprogramming library, parser implementation, forced compile-time optimization of all logic.
- **Project connection:** Consistent protocol metadata.

### Module 10 — Polymorphism and Dispatch Choices

- **New focus:** Virtual interfaces, variant/visit, template dispatch, open versus closed type sets; recognize CRTP and devirtualization.
- **Build:** [Compare event-handler boundaries](exercises/module-10-polymorphism-virtual-static/README.md).
- **Completion:** Equivalent behavioral tests, empty input and destruction/lifetime checks. Justify a preferred boundary for this workload. Virtual dispatch does not imply a fixed penalty or guaranteed branch misprediction.
- **Boundary:** A plugin system, mandatory CRTP refactor or a required benchmark win.
- **Project connection:** Choose abstractions according to extension and ownership needs.

### Module 11 — Undefined Behavior and Debugging

- **New focus:** Lifetime/bounds, signed overflow, aliasing/alignment, optimizer assumptions, debugger use and sanitizer limitations.
- **Build:** [Repair an unfamiliar processing component](exercises/module-11-undefined-behavior-debugging/README.md).
- **Completion:** Reproducible failures, justified fixes and regression tests covering each issue. Explain what clean sanitizer results do and do not establish.
- **Boundary:** A second duplicate debug assignment, exhaustive UB puzzles or mandatory MSan on unsupported platforms.
- **Project connection:** Investigate integration failures independently.

### Module 12 — Error Handling and Parsing

- **New focus:** Structured results, optional versus diagnostic errors, exceptions/noexcept, from_chars, numeric bounds and string_view lifetimes.
- **Build:** [Parse replay events with useful diagnostics](exercises/module-12-error-handling/README.md).
- **Completion:** Valid records and missing/extra fields, numeric limits/overflow, signs, trailing junk, invalid tags and blank lines. Results survive destruction of the input string. Diagnostics identify the failing location.
- **Boundary:** FIX, binary parsing, book implementation, a custom general-purpose expected library or blanket exception bans.
- **Project connection:** A reusable input contract for replay.

### Module 13 — Ownership and API Design

- **New focus:** Rule of Zero, unique ownership, observing references/pointers, shared_ptr costs, weak_ptr, factories and sink parameters.
- **Build:** [A replay session with explicit dependencies](exercises/module-13-smart-pointer-api-design/README.md).
- **Completion:** Test empty sources, invalid lines, source/sink failures, replacement, teardown and observer lifetimes. Explain construction/destruction order and any copy/move restrictions.
- **Boundary:** Custom smart pointers, manufactured cycles, required pimpl, concurrency and full book implementation.
- **Project connection:** Clear ownership for later connections and sessions.

### Module 14 — Testable and Maintainable C++

- **New focus:** Dependency boundaries, multi-translation-unit builds, CMake/CTest, deterministic tests, CLI contracts and failure propagation.
- **Build:** [Package a replay skeleton](exercises/module-14-testable-maintainable-cpp/README.md).
- **Completion:** Clean build and test instructions work; tests cover valid/invalid input, unavailable files and injected sink failure. Explain public headers, dependency direction, linking and test isolation.
- **Boundary:** A framework, a build-system survey, mandatory external test packages or implementing the book early.
- **Project connection:** A maintained application foundation for the capstone.

## Module 15 — Order-Book Replay Application

[Complete capstone contract](exercises/module-15-order-book-replay/README.md). Integrate the foundations into a single-instrument, single-threaded replay program. The learner chooses containers and interfaces and records a short design rationale. Use standard components unless a measured requirement justifies otherwise; exercise implementations need not become project dependencies.

Deliver typed input handling, book state transitions and queries, a CLI, independent reference tests, generated event sequences, build instructions and a measured baseline with one investigated improvement. Executions come from input; matching is a separate extension. The capstone is complete without sockets, threads or a live exchange.

## Project expansion after the capstone

These are roadmap milestones, not additional requirements for Modules 4–15. Specify one fully when it starts and keep a working system at every step. Revisit OS/networking concepts to explain concrete behavior rather than repeating entire courses.

| Milestone | Build and learn | Completion evidence |
|---|---|---|
| 1 — Feed simulator and connectivity | A local C++ feed simulator and connected consumer; framing, partial reads/writes, bounded input, sequence tracking and explicit disconnect behavior | Deterministic tests for fragmented/coalesced messages, gaps, duplicates, disconnects and reconnect policy; Linux build and basic profiling |
| 2 — Order-entry lifecycle | A simulated venue accepting requests and emitting acknowledgments, rejections and fills; track pending/accepted/partial/terminal states | State-machine tests, correlation IDs, cancel/fill races and explicit handling of uncertain outcomes; no real trading required |
| 3 — Concurrency and load | Introduce bounded queues and separate work only where useful; threads/jthread, mutexes, condition variables, cancellation and happens-before | Ordering, overload and shutdown tests; measured throughput/latency under a stated load; TSan where supported, separately from ASan |
| 4 — Recovery and operations | Durable logs/checkpoints, restart/reconciliation, metrics and failure injection | Reproducible recovery without silent loss/duplication; documented consistency, resource limits and operational failure behavior |

Add multiple instruments or richer binary protocols when an explicit milestone needs them. Begin concurrency with ordinary synchronization; atomics and lock-free designs are later choices, not prerequisites. Investigate allocation strategies/PMR, CPU-specific optimization or hardware interfaces only when measurements and interest justify them. Python remains outside the plan.

The target is reliable C++ systems engineering with a path toward live-trading platform work. The same foundation supports trading-facing execution work later. There is no assumed nanosecond target or guarantee of hiring readiness; independent debugging, design judgment and clear explanations matter alongside completed code.
