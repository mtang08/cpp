# Module 4 — Move Semantics Deep Dive

## For you

### Goal

The delivery component builds, but callers report unexpected copies, changed input and unreliable inspection results. Investigate and fix it independently, then request review.

### Steps

Investigate independently, then say **“review”**. The teacher handles review, the difficulty rating, the module quiz (or skip), and saving your place.

### Build

- `Payload` is supplied test support. Its copies duplicate storage; its moves transfer storage and leave the source empty. Keep this class and its copy counter unchanged.
- `Inbox::accept` borrows and copies an lvalue payload, leaving that caller's contents unchanged. It takes ownership when passed an rvalue. The inbox always holds the latest accepted contents.
- `deliver` must preserve those same rules when forwarding to an inbox. Both named payloads and temporaries must work.
- `archive` takes ownership of its by-value argument. Calling it with a temporary or with `std::move` on a named payload must not copy payload storage.
- `Inspector` observes the current payload object returned by an inbox's `peek()`. It must report the current first value, including after later submissions to that inbox. The inbox outlives its inspector. Empty payloads are outside this inspector's contract.

Preserve the harness, public function names, `Inbox::accept` overloads, and these caller-visible rules. You may correct parameter types in delivery functions and change the inspector's internals. Do not remove copying support, change the counter, weaken tests, or add unrelated features.

### Check

```sh
make run
make run-sanitized
```

The harness runs each case separately so one crash does not hide the others. For a single case, build with `make build` or `make build-sanitized`, then run `./challenge delivery`, `./challenge archive`, or `./challenge inspection` (use `./challenge-sanitized` for the sanitizer build).

Done means all three cases pass in both builds. Keep a short explanation of each cause and fix for the final review. Add a regression check only if it covers a behavior the supplied checks miss; no extra test checklist is required.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Ongoing challenge; preserve supplied support, constraints and learner changes. Calibration and phase are in progress.md. Do not regenerate it, expose defect locations or insert conversational checkpoints.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
