# Curriculum Critique

Assessment date: July 2026

Goal: evaluate whether `curriculum.md` is a sufficient starting path for targeting quant SWE roles with 1-2 YOE, using *Effective Modern C++* concurrently and *A Tour of C++* as prior light exposure.

## Summary

The current curriculum is a strong starting plan.

It is well-sequenced for building modern C++ fluency: ownership, value semantics, move semantics, templates, STL internals, memory layout, undefined behavior, API design, and a relevant capstone. This is the right foundation before going deep into concurrency or low-latency systems.

It is not yet a complete quant-SWE preparation plan. It should eventually be extended with more measurement discipline, tooling, concurrency, allocators, networking/protocol work, and larger systems-oriented projects.

For now, proceeding with the curriculum as written is reasonable.

## What The Curriculum Does Well

The early modules have the right priorities.

- RAII before advanced smart-pointer patterns
- Rule of Five before deeper move semantics
- move semantics before STL internals
- containers and iterators before performance tuning
- memory layout before cache-aware design
- undefined behavior before aggressive optimization

This avoids a common failure mode: jumping into low-latency or quant-flavored topics before having reliable ownership, lifetime, and value-semantics intuition.

Modules 2-6 are especially important. If those are done carefully, they will build the core C++ mental model needed for both interviews and production C++ work.

Modules 8-11 are also well chosen. They move from surface-level language fluency into the lower-level reasoning expected in performance-sensitive codebases.

The capstone choice is appropriate. A simplified order book or FIX/message parser is much more aligned with quant SWE than generic OOP projects.

## Fit With Current Resources

*Effective Modern C++* fits the curriculum very well, especially Modules 1-7 and 12-13.

High-value overlaps include:

- `auto` and type deduction
- `decltype`
- smart-pointer ownership
- move semantics
- perfect forwarding
- lambdas
- `std::function` tradeoffs
- `noexcept`
- concurrency later, when that phase begins

*A Tour of C++* is useful as prior orientation, but it should not be treated as a mastery resource. It is broad and helpful for exposure, but too compressed to drive deep proficiency by itself.

Recommended reference material alongside the curriculum:

- cppreference for exact language and library behavior
- C++ Core Guidelines for idioms and design judgment
- Compiler Explorer for codegen inspection
- selected CppCon talks for performance, tooling, and modern C++ practice

## Main Gaps

### 1. Measurement Discipline

The curriculum currently includes timing in Module 8, but performance measurement should become a recurring habit rather than a one-time topic.

For quant SWE, it is important to learn how to measure before optimizing.

Eventually add recurring practice with:

- debug vs release builds
- optimization flags
- microbenchmarking pitfalls
- benchmark noise
- profiling hot paths
- flamegraphs or equivalent profiling views
- cachegrind-like tools where available
- reading generated assembly in Compiler Explorer
- distinguishing algorithmic wins from constant-factor wins

Suggested habit: for performance-oriented exercises, first write the simple correct version, then measure, then optimize, then explain what changed and why.

### 2. Tooling And Project Hygiene

Module 14 covers header/source organization, but tooling should appear earlier.

Quant C++ environments tend to care about build discipline and diagnostics. Eventually add a small tooling module or recurring checklist covering:

- `-Wall -Wextra -Wconversion -Wshadow -pedantic`
- sanitizer builds with ASan/UBSan
- debug vs release builds
- basic CMake
- `clang-format`
- `clang-tidy`
- simple test harnesses
- compile-time and dependency-boundary awareness

Suggested habit: every exercise should compile cleanly with strict warnings and have a sanitizer run when relevant.

### 3. Concurrency Cannot Stay Deferred Forever

Deferring concurrency is the right choice for now. It is better to build single-threaded ownership, lifetime, and performance intuition first.

But for quant SWE, concurrency eventually needs its own major phase.

Important later topics:

- `std::thread`
- mutexes and condition variables
- atomics
- memory ordering
- producer/consumer queues
- ring buffers
- false sharing in practice
- lock-free vs wait-free vocabulary
- latency vs throughput tradeoffs
- safe shutdown and lifetime management across threads

This does not need to be inserted into the current plan immediately, but it should be planned as a follow-up phase.

### 4. Networking, Protocols, And Parsing

The capstone mentions FIX/message parsing, which is good. The curriculum could eventually benefit from more explicit protocol-oriented work.

Relevant topics:

- binary message formats
- endian handling
- framing
- parsing without unnecessary allocation
- `std::span`
- `std::string_view`
- zero-copy parsing tradeoffs
- malformed input handling
- backpressure and buffering concepts

These topics are especially useful for market data, trading infrastructure, and exchange-connectivity roles.

### 5. Allocators And Memory Resources

Allocator awareness is currently missing.

For quant-oriented C++, eventually add:

- allocation cost
- avoiding heap allocation in hot paths
- object pools
- arenas
- allocator-aware containers
- `std::pmr`
- ownership/lifetime boundaries for pooled objects

This would fit naturally after Module 8 or before the capstone.

## Suggested Small Adjustments Later

The curriculum does not need a large rewrite right now.

When ready, consider adding recurring requirements to exercises:

- compile with strict warnings
- run sanitizer builds
- write at least a small test harness
- state ownership and lifetime invariants
- measure before optimizing
- explain performance tradeoffs after changes

Possible future module additions:

- Tooling and build basics after Module 3
- Allocators and memory resources after Module 8
- Protocol parsing before the capstone
- Concurrency as a later Phase 6

## Quant-SWE Readiness Judgment

As a starting curriculum: sufficient.

As a complete quant-SWE preparation plan: not yet.

The current plan should build a strong base in modern C++ and performance-aware reasoning. To become more quant-SWE-specific, the next layer should emphasize systems tooling, performance measurement, concurrency, allocators, protocol parsing, and realistic project work.

The capstone can become a strong bridge if implemented seriously:

- start with a correct simple version
- add tests and malformed-input cases
- profile before optimizing
- reduce hot-path allocations
- reason about data layout
- document tradeoffs
- be able to explain design choices under interview conditions

## Current Recommendation

Proceed with `curriculum.md` as written.

Do not over-expand the plan before building momentum. The current modules are valuable and ordered well. The critique above should be treated as guidance for the next phase, not as a reason to stop and redesign the curriculum now.
