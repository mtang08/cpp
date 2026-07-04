# C++ Mastery Curriculum

Goal: quant-firm-level C++ proficiency. Concurrency deferred to a later study phase.

## Phase Roadmap

| Phase | Timeline | Focus |
|-------|----------|-------|
| 1 | Now → early August 2026 | Finish OSTEP, C++ exercises Modules 1–3, start 4 |
| 2 | August → December 2026 | EMCPP + Modules 4–14, systems depth (networks, perf comp arch, light DDIA), capstone |

**EMCPP** will be read alongside the curriculum.
Capstone deadline is soft; slide to early 2027 if Modules 8–11 (the harder ones) run long.

---

## Folder Structure

```
cpp/
├── curriculum.md          ← this file
├── progress.md            ← current module/session progress
├── playground/            ← conceptual sessions: textbook reading, tiny snippet experiments
│   └── main.cpp
├── exercises/             ← implementation sessions, organized by module
│   └── module-01-types-references-const/
│       ├── main.cpp
│       └── Makefile
└── debugging/             ← debugging sessions, organized by module
    └── module-01-types-references-const/
        ├── main.cpp
        ├── Makefile
        └── session-YYYY-MM-DD.md
```

- `playground/`: scratch space for exploration, syntax experiments, and concept verification
- `exercises/module-XX-*`: curriculum exercises — I give a prompt, you implement, I review
- `debugging/module-XX-*`: generated buggy code plus session notes recording prompts, responses, mistakes, and takeaways. `make run-sanitized` available for ASan/UBSan

Progress rule: modules advance one by one. Do not expand scope, insert extra topics, or jump ahead unless explicitly requested.

---

## Phase 1: Foundations Refresher

### - [x] Module 1 — Types, References, and const Correctness
- What happens when you compile and run a program: source → compiler → object → linker → executable → OS loads it → stack frame for `main`
- Stack frames, where local variables live, what a function call does at the machine level
- Value types, narrowing, `auto` deduction rules
- References vs pointers — when and why
- `const T&`, `T const&`, `const T* const` — reading declarations right-to-left
- **Exercise:** implement a function family with correct const/reference signatures
- **Debug:** find subtle const-correctness bugs

### - [ ] Module 2 — Ownership and Resource Management (RAII)
- Stack vs heap allocation — what actually happens at each
- RAII: constructors, destructors, deterministic cleanup
- `new`/`delete` and why you almost never use them directly
- `std::unique_ptr`, `std::shared_ptr` — ownership semantics
- **Exercise:** build a resource-managing class (file wrapper or buffer)
- **Debug:** fix a resource leak and a double-free

### - [ ] Module 3 — The Rule of Five and Value Semantics
- Copy constructor, copy assignment, destructor, move constructor, move assignment
- When the compiler generates them, when it doesn't, and why
- `= default`, `= delete`
- **Exercise:** implement a `DynamicArray` class with all five special members
- **Debug:** fix a class with a missing move constructor causing unnecessary copies

---

## Phase 2: Modern C++ Mechanics

### - [ ] Module 4 — Move Semantics Deep Dive
- lvalues vs rvalues vs xvalues — what the compiler sees
- `std::move` is just a cast — what it does and doesn't do
- Reference collapsing and perfect forwarding (`std::forward`)
- RVO / NRVO — when moves are elided entirely
- **Exercise:** implement a `UniqueBuffer` that transfers ownership correctly
- **Debug:** fix misused `std::move` (moving from const, use-after-move)

### - [ ] Module 5 — Templates and Type Deduction
- Function templates, class templates, template argument deduction
- `auto` and `decltype` — deduction rules and pitfalls
- SFINAE basics and `std::enable_if`
- C++17 `if constexpr`, `constexpr` functions
- **Exercise:** write a generic `serialize()` dispatching by type (arithmetic vs string vs container)
- **Debug:** decipher and fix template error messages

### - [ ] Module 6 — STL Containers and Iterators Under the Hood
- `vector` memory layout: size, capacity, reallocation, iterator invalidation
- `map` vs `unordered_map` — red-black tree vs hash table, cache implications
- `deque`, `list`, `array` — when and why
- Iterator categories and why they matter for algorithm complexity
- **Exercise:** implement a simplified `vector<T>` with push_back, reserve, move-aware reallocation
- **Debug:** fix iterator invalidation bugs

### - [ ] Module 7 — STL Algorithms and Lambdas
- Algorithm complexity guarantees and iterator requirements
- Lambdas: capture by value/reference, mutable, generic lambdas
- `std::function` and its overhead vs templates
- **Exercise:** solve a data-processing pipeline using STL algorithms and lambdas
- **Debug:** fix capture-by-reference lifetime bugs

---

## Phase 3: Performance and Low-Level Reasoning

### - [ ] Module 8 — Memory Layout and Cache Performance
- Struct layout, padding, alignment (`alignof`, `alignas`)
- Array-of-structs vs struct-of-arrays
- Cache lines, spatial/temporal locality, false sharing (conceptual)
- **Exercise:** optimize a hot loop by improving data layout; measure with timing

### - [ ] Module 9 — Compile-Time Computation
- `constexpr` vs `const` vs `consteval`
- `constexpr` functions, `constexpr if`
- Template metaprogramming basics: type traits, `std::integral_constant`
- Practical uses: compile-time lookup tables, static dispatch
- **Exercise:** implement a compile-time lookup table and type-trait-based dispatch

### - [ ] Module 10 — Polymorphism: Virtual vs Static
- Virtual dispatch: vtable layout, pointer indirection cost
- CRTP (Curiously Recurring Template Pattern) for static polymorphism
- `std::variant` + `std::visit` as an alternative to inheritance
- Quant perspective: virtual = branch mispredictions in hot paths
- **Exercise:** refactor virtual dispatch into CRTP; implement a variant-based message handler

### - [ ] Module 11 — Undefined Behavior, Compiler Optimizations, and Debugging
- Common UB: signed overflow, null deref, use-after-free, strict aliasing
- How UB enables compiler optimizations (and bites you)
- Reading compiler output with Compiler Explorer
- Sanitizers: ASan, UBSan, MSan
- **Exercise:** find and fix UB in a series of short programs

---

## Phase 4: Design and Idioms

### - [ ] Module 12 — Error Handling Strategies
- Exceptions: cost model (zero-cost happy path, expensive throw)
- `std::optional`, `std::expected` (C++23 pattern)
- Error codes, `noexcept` — when and why
- Quant perspective: many firms ban exceptions in hot paths
- **Exercise:** implement a parser using `std::optional`; compare exception vs error-code approaches

### - [ ] Module 13 — Smart Pointer Patterns and API Design
- `unique_ptr` for ownership, raw pointers/references for observation
- `shared_ptr` costs: reference counting, control block, atomic overhead
- `weak_ptr` for breaking cycles
- Designing APIs: sink parameters, factory functions, pimpl idiom
- **Exercise:** design and implement a component system with clear ownership semantics

### - [ ] Module 14 — Writing Testable, Maintainable C++
- Header/source organization and compilation model
- Dependency injection without frameworks
- Building small projects with multiple translation units
- **Exercise:** split a monolithic program into headers/sources, add a simple test harness

---

## Phase 5: Capstone

### - [ ] Module 15 — Order Book or Message Parser
- Build a simplified limit order book or FIX message parser
- Applies: move semantics, templates, cache-aware data structures, RAII, no-exception hot paths
- Iterative: start simple, profile, optimize, explain tradeoffs
