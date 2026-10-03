# Module 5 — Templates and Type Deduction

Status: specified, not started. Prerequisites: Modules 1–4; proceed in sequence.

## New learning

Function and class templates; deduction, auto/decltype, concepts/requires and if constexpr. Recognize SFINAE in existing code without making enable_if the default.

## Exercise: Constrained diagnostic formatting

Implement a diagnostic formatting utility returning std::string. Support integral types except character types, bool, std::string, std::string_view, and std::vector<T>/std::array<T,N> whose elements are supported scalars. Support one container level only. Unsupported types must be rejected at compile time. Treat strings as scalar values, not ranges.

Integers use decimal notation, booleans use true/false, strings are double-quoted and escape backslash, double quote, newline, carriage return and tab. Containers use [a, b, c]; empty containers use []. Input strings are text; other control characters and floating-point formatting are outside the contract. Choose your template interfaces and organize type support so adding a supported type does not require duplicating the whole formatter.

## Verification and review

Exact-output tests for each category, empty inputs, escapes, negative integers, numeric limits and both container types. Compile-time checks must distinguish supported and unsupported types. Explain why overload/constraint selection treats strings correctly.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: Full serialization, nested ranges, wire protocols, advanced metaprogramming. Module 4 already owns forwarding practice.

Capstone connection: Type-safe utilities and readable diagnostics.
