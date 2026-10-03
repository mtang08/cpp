# Module 12 — Error Handling and Parsing

Status: specified, not started. Prerequisites: Modules 1–11; proceed in sequence.

## New learning

Structured results, optional versus diagnostic errors, exceptions/noexcept, from_chars, numeric bounds and string_view lifetimes.

## Exercise: Parse replay events with useful diagnostics

Implement a parser for the text event grammar in the capstone README. Parse one line into an owning typed record or a structured error with line number, field position when applicable, and reason. Reject invalid syntax and numeric ranges without modifying caller-owned book state. State-dependent validation belongs to the future book.

Use a C++20 result representation of your choice; std::expected is not available in the required language version. Choose boundaries for recoverable invalid input versus resource/I/O failures. Compare an exception-based interface in a short design explanation, not a second full parser. Do not mark operations noexcept if they can propagate allocation failures.

## Verification and review

Valid records and missing/extra fields, numeric limits/overflow, signs, trailing junk, invalid tags and blank lines. Results survive destruction of the input string. Diagnostics identify the failing location.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: FIX, binary parsing, book implementation, a custom general-purpose expected library or blanket exception bans.

Capstone connection: A reusable input contract for replay.

The event grammar is specified in [the capstone contract](../module-15-order-book-replay/README.md#input-contract).
