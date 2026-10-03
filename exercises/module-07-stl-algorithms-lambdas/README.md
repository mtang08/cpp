# Module 7 — STL Algorithms, Lambdas, and Views

Status: specified, not started. Prerequisites: Modules 1–6; proceed in sequence.

## New learning

Algorithm contracts and complexity, strict weak ordering, captures, callable types, span/string_view and borrowed lifetimes.

## Exercise: Deterministic event analytics

Process already validated in-memory records containing instrument name, timestamp, unique sequence number, event kind and quantity. Provide filtering by instrument and a half-open timestamp interval, chronological ordering with sequence-number tie breaking, and per-instrument summaries of event count and quantity sum. Summaries are ordered lexicographically by instrument. Input order is arbitrary; an empty selection produces empty output. Detect aggregate overflow.

Choose your API and standard containers. Use standard algorithms where they fit. The input must remain unchanged and returned results must remain valid after input destruction. Borrow views only within explicitly documented lifetimes. Split public declarations, implementation and a separate test executable; the assistant may provide build support.

## Verification and review

Hand-computed cases for empty input, boundaries, ties, mixed instruments, overflow and input preservation. Explain complexity, comparator correctness and capture/view lifetimes.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: Parsing, order-book state transitions, custom sorting algorithms and a mandatory ranges framework.

Capstone connection: Deterministic batch processing and queries.
