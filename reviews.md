# Code review checkpoints

Review the current implementation against its existing module spec. Read the learning context, roadmap, progress, and current/adjacent specs first. A checkpoint can review incomplete work without declaring the module complete. Identify bugs without rewriting core code or providing fixes unless requested.

## Inline finding format

Place each finding immediately above the relevant code, using one comment line:

```cpp
// YYYY-MM-DD codex: [M04-001] [open] [bug] Trigger, violated requirement or invariant, and consequence.
```

- Date: date first identified, retained through later reviews.
- ID: `MNN-NNN`, module number plus a monotonically increasing finding number. Unique across that module's exercise and debugging files; never reuse or renumber it.
- Status: `open`, `resolved`, or `dismissed`.
- Kind: `bug` for incorrect behavior or compilation; `test-gap` for missing verification; `design` for an actionable API/maintainability concern. Do not label unfinished acceptance evidence as a proven runtime bug.
- Description: state the concrete problem and impact, without solution code. Keep distinct causes in separate findings; reference an existing ID rather than duplicating it at each affected call site.

Comments are the canonical finding records. A report can scan source files for this prefix and extract date, ID, status, kind, description, file, and current line number. IDs remain stable when code moves. Do not generate a linter or additional tooling unless requested.

## Review and resolution

Run checks appropriate to the implemented portion. Report what they actually exercise: an empty harness passing sanitizers is not evidence of ownership correctness. Independent temporary probes may substantiate a finding without changing learner code. Do not add new exercise requirements during review.

The learner fixes code and adds meaningful regression checks. On requested re-review, confirm the relevant behavior before changing a finding to `resolved`. Retain its original date and ID; append `Verified YYYY-MM-DD: <evidence>.` to the comment. Move the comment to the corrected code if necessary. Use `dismissed` with a dated reason when a finding is shown to be invalid. Keep retained records factual so future spaced review can distinguish historical issues from active ones.

Log checkpoint state and notable verification concisely in `progress.md`. Record mistakes separately from conventions actually demonstrated or learned. Stop at the requested checkpoint; proceed only when the learner asks.
