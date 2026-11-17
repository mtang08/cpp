# Module 15 — Order-Book Replay Application

## For you

### Goal

Build a single-threaded, single-instrument program that replays recorded events, maintains active orders and answers book queries. Executions are supplied by input: this is not a matching engine. Prices are positive integer ticks and quantities are positive integer units; there is no floating-point money arithmetic.

Before implementing, write a short design note covering public operations, storage/index choices, ownership, invariants, expected complexity and errors. Choose interfaces and containers yourself. Standard containers are encouraged; do not use educational containers merely to demonstrate every prior module. Earlier parser/session code may be reused when its contract fits.

### Steps

1. Design, implement and verify the application below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Answer the short quiz (or skip), then wrap up the project milestone.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

#### Input contract

Each nonblank input line is one of these case-sensitive records:

- `ADD <id> <side> <price> <quantity>`
- `CANCEL <id>`
- `EXECUTE <id> <quantity>`

Fields are separated by one or more ASCII spaces or tabs; leading/trailing spaces or tabs are allowed. Accept LF and CRLF line endings. Whitespace-only lines are ignored. No comments or extra fields are accepted. Side is exactly `B` or `S`. All numeric tokens are unsigned decimal digits, with no sign or suffix; leading zeros are accepted. Values must be in `[1, UINT64_MAX]`. A final line without a newline is valid. Module 12's single-line parser may receive a trailing carriage return from line reading; accept it only at the end as part of CRLF handling. A blank line produces an explicit ignored-line result, not a fake event.

Line numbers are one-based. Syntax/range failures report the line and field/reason. Parsed records own their values and do not borrow input storage. Blank lines are excluded from accepted/rejected event counts.

#### State transitions

- Start with an empty book.
- ADD creates an order with its side, price and remaining quantity. An ID already active is invalid. An ID may be reused after its previous order has been fully removed.
- CANCEL removes the entire remaining order. An unknown ID is invalid.
- EXECUTE decreases the specified order's remaining quantity. An unknown ID or a quantity larger than the remaining amount is invalid. Remove the order if remaining quantity reaches zero.
- There is no amend operation. A cancel followed by add is two independent events.
- Track aggregate remaining quantity by side and price. Reject an ADD that would overflow the quantity total at its price level. Remove empty levels.
- Accepted events preserve consistency between individual orders and all query results. Invalid events leave book state unchanged and produce a diagnostic.
- Locked/crossed books are allowed: replay does not infer or generate trades. There is no price-time matching requirement.

Recoverable input errors are reported and skipped; continue processing later lines in file order. Allocation and I/O failures may terminate processing with a nonzero exit code. Document the exception guarantee for resource failures; strong recovery from allocation failure is not required, but leaks/double destruction are never acceptable. Do not claim successful replay after an operational failure.

#### Queries

Provide testable library operations for:

- Active order count and lookup by ID, including an explicit unknown-ID result.
- Best bid (highest buy price) and best ask (lowest sell price), each with aggregate quantity or an explicit empty-side result.
- Top N price levels on either side, best price first, including aggregate quantity. N=0 returns no levels; N larger than the book returns all available levels.

Choose value versus view returns deliberately and document invalidation if using borrowed results. Do not expose internal storage solely to satisfy tests.

#### CLI and packaging

Provide `replay <input-file>` and print a deterministic final summary: accepted/rejected event counts, active order count, best bid/ask and the top five levels on each side. Define the precise output format in your project documentation before integration tests. Send diagnostics to stderr.

Exit codes: 0 for a fully valid input file (including an empty file), 1 if any event is rejected but the file was otherwise processed, and 2 for usage or operational failure. Operational failure takes precedence over rejected-input status. Write concise build, test and example-run instructions.

Use a library, CLI and separate tests with CMake/CTest, including debug, ASan/UBSan and release instructions. Checks in tests must remain active in release builds. Keep generated binaries/build directories out of source control. Choose the project layout within this module; it may continue growing here after graduation.

### Check

Write tests covering each transition, partial/full execution, duplicate/unknown IDs, reuse after removal, numeric boundaries, aggregate overflow, removal of best/last levels, both sides, queries and invalid-event state preservation. Cover parsing and CLI behavior with small integration fixtures.

Implement a deliberately simple reference model in C++ with independent state/update/query logic (for example, derive aggregates from active orders on demand). It is test support, not the production implementation with a different name. Generate reproducible sequences containing both valid and invalid typed events and compare outcomes and queries after every event. Record failing seeds and event prefixes so failures can be replayed. Parser tests remain separate from typed-state differential tests.

Run normal, sanitized and optimized tests. No external exchange data or paid service is required.

#### Performance and completion

Create reproducible workloads with varied active-order counts and mixes of adds, cancellations and executions. State the workload size, seed, compiler, machine and build options. Measure state processing separately from parsing/I/O, then measure end-to-end replay. Report throughput, memory and variability; do not label average time per event as a latency percentile.

Profile a correct baseline and investigate one change supported by evidence. Recheck equivalence and document whether you kept or rejected it. A speedup is not required. Keep the final design note short: choices, complexity, measured results, limitations and one sensible next extension.

### Scope

No sockets, threads, real exchange protocol, strategy, matching engine or nanosecond target. Finish when behavior and error contracts pass, required findings are addressed, results reproduce and you can explain the implementation. See [later milestones](../../curriculum.md#project-expansion-after-the-capstone).

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–14. This is the first integrated version of an ongoing project. Keep container/interface choices with the learner; educational implementations are not mandatory dependencies. Existing project defects and regression work supply debugging practice; do not invent a second standalone challenge for the capstone.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
