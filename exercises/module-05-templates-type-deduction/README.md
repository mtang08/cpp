# Module 5 — Templates and Type Deduction

## For you

### Goal

Constrained diagnostic formatting.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Implement a diagnostic formatting utility returning std::string. Support integral types except character types, bool, std::string, std::string_view, and std::vector<T>/std::array<T,N> whose elements are supported scalars. Support one container level only. Unsupported types must be rejected at compile time. Treat strings as scalar values, not ranges.

Integers use decimal notation, booleans use true/false, strings are double-quoted and escape backslash, double quote, newline, carriage return and tab. Containers use [a, b, c]; empty containers use []. Input strings are text; other control characters and floating-point formatting are outside the contract. Choose your template interfaces and organize type support so adding a supported type does not require duplicating the whole formatter.

### Check

Exact-output tests for each category, empty inputs, escapes, negative integers, numeric limits and both container types. Compile-time checks must distinguish supported and unsupported types. Explain why overload/constraint selection treats strings correctly.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: Full serialization, nested ranges, wire protocols, advanced metaprogramming. Module 4 already owns forwarding practice.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–4.

Teaching focus: Function and class templates; deduction, auto/decltype, concepts/requires and if constexpr. Recognize SFINAE in existing code without making enable_if the default.

Project connection: Type-safe utilities and readable diagnostics.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
