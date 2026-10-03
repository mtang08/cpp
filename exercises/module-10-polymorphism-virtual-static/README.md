# Module 10 — Polymorphism and Dispatch Choices

Status: specified, not started. Prerequisites: Modules 1–9; proceed in sequence.

## New learning

Virtual interfaces, variant/visit, template dispatch, open versus closed type sets; recognize CRTP and devirtualization.

## Exercise: Compare event-handler boundaries

Implement a small handler for already typed ADD, CANCEL and EXECUTE records in two forms: an interface with virtual dispatch and a variant-based representation with visitation. Each produces counts and total quantities by event kind, with the same overflow/error behavior. It does not maintain an order book.

Choose ownership and APIs, run equivalent inputs through both, and explain the changes needed to introduce a fourth event kind. Read or inspect a short static-dispatch/CRTP example to compare constraints; a third framework is not required. If making runtime speed claims, use Module 8 measurement discipline.

## Verification and review

Equivalent behavioral tests, empty input and destruction/lifetime checks. Justify a preferred boundary for this workload. Virtual dispatch does not imply a fixed penalty or guaranteed branch misprediction.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: A plugin system, mandatory CRTP refactor or a required benchmark win.

Capstone connection: Choose abstractions according to extension and ownership needs.
