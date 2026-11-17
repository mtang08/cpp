# C++ Systems Engineering Curriculum

## For you

Build C++ foundations, then an order-book replay application that can grow into trading infrastructure. Work one module at a time. Each module starts with **For you**; the collapsed teacher section can be skipped.

### Module steps

1. **Build and check:** implement the module and run its checks.
2. **Review:** say “review.” The teacher checks correctness first, then C++ practices once requirements are met. Fix required findings and ask for re-review.
3. **Debug:** investigate the supplied challenge independently, then request review and rate its difficulty. Module 11 combines implementation/debugging; the capstone uses its own project debugging.
4. **Quick quiz:** five short questions, one at a time. Say “skip” if you want to move on; no retake is required.
5. **Continue or pause:** the teacher records progress. Say “continue” for the next step, or “wrap up” to stop.

You never need to type a skill name. An interim “review just this part” stays scoped to that checkpoint.

### Questions while coding

Optionally jot questions in `questions.md` beside the challenge README under **Open**. Add your guess or a code location if useful. The teacher reads them at review, discusses them one at a time, and saves takeaways under **Addressed**. Say “let’s address Q2” for earlier help; unanswered questions can carry forward without blocking progress.

Or send **`/qa your question`** (or “save this question”): the teacher files it in the current challenge and briefly confirms. At review/wrap-up, the teacher also records meaningful stumbles and what helped in that file's **Stumbles** section. You do not need to maintain a separate obstacle log.

### Build rules

Use C++20, `-Wall -Wextra -Wpedantic`, and normal plus ASan/UBSan checks. From Module 7, add `-Wconversion -Wshadow` and separate library code from tests. Keep test checks active with `NDEBUG`. Use optimized, unsanitized builds for benchmarks.

### Modules

| Module | Build / practice |
|---|---|
| [Module 1 — Types, References, and const Correctness](exercises/module-01-types-references-const/README.md) | Practice types, references and const-correct function interfaces. |
| [Module 2 — Ownership and Resource Management (RAII)](exercises/module-02-ownership-raii/README.md) | Practice ownership and deterministic cleanup in a resource-managing class. |
| [Module 3 — The Rule of Five and Value Semantics](exercises/module-03-rule-of-five-value-semantics/README.md) | Implement an owning dynamic array of int to practice value semantics and the five special members. |
| [Module 4 — Move Semantics Deep Dive](exercises/module-04-move-semantics/README.md) | Move-only buffer handoff across APIs. |
| [Module 5 — Templates and Type Deduction](exercises/module-05-templates-type-deduction/README.md) | Constrained diagnostic formatting. |
| [Module 6 — Containers, Storage, and Element Lifetime](exercises/module-06-stl-containers-iterators/README.md) | A bounded `vector<T>` implementation. |
| [Module 7 — STL Algorithms, Lambdas, and Views](exercises/module-07-stl-algorithms-lambdas/README.md) | Deterministic event analytics. |
| [Module 8 — Memory Layout and Performance Measurement](exercises/module-08-memory-layout-cache-performance/README.md) | Profile and compare event layouts. |
| [Module 9 — Compile-Time Computation](exercises/module-09-compile-time-computation/README.md) | Validated event metadata. |
| [Module 10 — Polymorphism and Dispatch Choices](exercises/module-10-polymorphism-virtual-static/README.md) | Compare event-handler boundaries. |
| [Module 11 — Undefined Behavior and Debugging](exercises/module-11-undefined-behavior-debugging/README.md) | Repair an unfamiliar processing component. |
| [Module 12 — Error Handling and Parsing](exercises/module-12-error-handling/README.md) | Parse replay events with useful diagnostics. |
| [Module 13 — Ownership and API Design](exercises/module-13-smart-pointer-api-design/README.md) | A replay session with explicit dependencies. |
| [Module 14 — Testable and Maintainable C++](exercises/module-14-testable-maintainable-cpp/README.md) | Package a replay skeleton. |
| [Module 15 — Order-Book Replay Application](exercises/module-15-order-book-replay/README.md) | Single-instrument order-book replay, queries and measured performance. |

After the initial modules, read *Effective Modern C++* a couple of hours weekly and apply useful lessons to the project. Reading is not a prerequisite for moving through exercises. Python is outside this plan.

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

## For the teacher

<details>
<summary>Workflow, scope, and continuity</summary>

Follow [the teaching workflow](context/teaching-workflow.md) for automatic skill routing and phase transitions. Load skills at the relevant step; do not ask the learner to invoke them. Module contracts live in their learner sections, and module-specific teaching notes live below them. Keep status in progress.md.

- `context/README.md`: goals and preferences. `curriculum.md`: sequence and scope. Exercise READMEs: behavior and acceptance contracts. `progress.md`: current task and demonstrated learning. `AGENTS.md`: teaching rules. The July critique is historical.
- Work one module at a time; progress.md is authoritative for the current phase. Future specifications describe scope, not concurrent assignments.
- Read the full roadmap, current progress and adjacent module specs before preparing/reviewing work. Preserve completed work; identify each module's new contribution instead of repeating prior drills.
- Modules 1–14 have one bounded implementation exercise and a focused debugging session. Module 11 combines them; Module 15 uses its own project debugging and regression work. Generate buggy code only when its session starts, calibrated to the latest rating; give the full challenge and let the learner investigate independently.
- The learner writes core code and meaningful tests. The assistant may supply build support, fixtures and independent checks. Reviews identify problems without rewriting solutions unless asked.
- Specs define behavior, errors, invariants and acceptance evidence. Increasingly leave API, container and internal layout choices to the learner. Any missing material contract should be resolved before implementation, not introduced as a surprise at review.
- Stop expanding a module when its checks pass and findings are addressed. Do not demand every possible abstraction, a fixed speedup, textbook completion or extra drills before moving on.

### Engineering practice

Use C++20 and `-Wall -Wextra -Wpedantic`. Run normal and ASan/UBSan builds for runnable exercises. Introduce `-Wconversion -Wshadow` from Module 7 and resolve or explain diagnostics. Tests must remain effective with NDEBUG. Keep sanitized and optimized benchmark builds separate.

From Module 7, separate reusable code from tests and introduce headers/sources naturally; templates can remain in headers. Build support may be supplied until Module 14 makes build ownership explicit. Formatting and static analysis support implementation rather than becoming separate projects.

Completion means the behavior and edge cases work, ownership/invariants can be explained, meaningful tests pass, and review issues are resolved. Record whether a skill was demonstrated independently or corrected after feedback. Sanitizers complement reasoning; they do not prove correctness. Use subsequent module requirements to revisit weaknesses naturally.

Performance work follows: correct baseline, defined workload, profiling, one relevant change, correctness recheck and a short report. Document compiler, machine, input and variability. Throughput and latency are different metrics; batch runtime divided by event count is not a measured latency distribution. Linux tooling comes with later systems work; use tools available on the development machine now.

Preserve explicit accepted checkpoints and deferred evidence; a formatting change is not permission to reopen them. The module READMEs retain the full requirements even where this index summarizes them.

</details>
