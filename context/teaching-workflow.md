# Teacher workflow

This is agent-facing orchestration for the C++ curriculum. The learner-facing steps are in [the curriculum](../curriculum.md#module-steps). The learner requested automatic skill selection on 2026-11-08; do not ask them to remember or type skill names.

## Read and resume

Read AGENTS.md, context/README.md, the curriculum roadmap, progress.md, reviews.md, and the current/adjacent module specs. Read both the learner contract and teacher notes. Current status belongs in progress.md; inline finding IDs remain the canonical review ledger.

Use `cpp-session-handoff` when resuming or wrapping up. Resume with the current phase and one next action. Do not review code merely because the learner reports a finding, or expose defects in an uncompleted debugging challenge.

## Route the module steps

| Step / learner cue | Skill or action | Transition |
|---|---|---|
| `/qa <question>` / “save this question” | Load `cpp-qa` | Record in the current challenge's questions.md and briefly confirm; do not answer or inspect code |
| “Start” / “continue” during implementation | Present the current contract and any needed build support | Let the learner implement independently; no unsolicited review |
| “Review” / “check my changes” / re-review | Load `cpp-correctness-review` | Review the requested scope and update existing finding IDs; return control for required fixes |
| Correctness and required acceptance evidence verified on the current implementation | Load `cpp-idioms-review` automatically as the second part of a full review | Report only useful C++20/API improvements; optional taste does not block progress |
| Implementation review complete; “continue” to debugging | Prepare the module’s planned challenge using its teacher notes and latest difficulty rating | Give the full contract up front, then allow independent investigation |
| Debugging solution ready for review | Load `cpp-correctness-review` in its debugging context; retain the local Socratic/no-spoiler rules | Verify the solution on request, ask for the 1–5 rating, and record it; no duplicate full idioms pass unless changed code warrants it |
| Module implementation/debugging review complete | Load `cpp-module-quiz` automatically for the curriculum quiz step | Ask five questions one at a time; accept “skip” or “stop”; a score never gates completion |
| Phase completed, quiz finished/skipped, “wrap up,” or resume | Load `cpp-session-handoff` | Save concise evidence, open IDs, phase and one next action; avoid duplicate logs already written by a review |
| “Continue” after module wrap-up | Check the existing completion contract and any explicit learner exceptions | Advance one module when supported; never silently mark unresolved evidence verified |

These cues are examples, not commands the learner must memorize. Infer the intended step from ordinary language and the saved phase. Do not chain into a quiz from an interim checkpoint, partial review, unrelated syntax question, or report of a finding. A request to pause or restrict scope takes priority.

## Question scratchpad

Load `cpp-qa` for capture and Q&A bookkeeping during authorized reviews/handoffs. `/qa` is a teacher-interpreted message prefix, not a registered application command; “save this question” or `$cpp-qa` also works. Explicit target or unambiguous conversation context takes precedence over progress.md; otherwise use its current module and phase to distinguish exercises/ from debugging/. Ask only if the target is genuinely ambiguous. Keep the original question, date and stable local Q ID; do not hardcode Module 4 or change phase to match a note.

The learner may keep `questions.md` beside the current exercise or debugging README. Create it only when requested or when there is a real question to record; do not populate every module with empty files. Use `## Open` and `## Addressed`, with local IDs such as Q1. The question alone is enough; a guess and code location are optional:

```markdown
## Open

- Q1: When should this function be noexcept?
  My guess: ...
  Context: ...

## Addressed
```

- **During implementation:** do not watch, inspect or answer the scratchpad merely because it changes. A direct request such as “let’s address Q2” authorizes that question; retain the one-question Socratic approach when the learner is stuck.
- **At requested review:** read the current challenge's questions alongside the implementation. Honor a code-only or partial review request. Distinguish questions the learner demonstrably answered through their work from unresolved uncertainties; working code alone is not proof of understanding.
- **After the review findings:** address unresolved in-scope questions one at a time, with brief explanations and a reasoning question as appropriate. Do not dump answers or expose debugging fixes. Let this discussion precede the scheduled quiz; a pause or skip takes priority.
- **When addressed:** preserve the original question and learner guess, move the entry to Addressed, and append a dated, concise takeaway based on the actual discussion. Do not invent answers or mark a question addressed just because an explanation was offered without resolving the uncertainty.
- **At wrap-up:** keep unanswered items in Open, mark future-module topics deferred with a reason when useful, and link outstanding IDs/file paths from progress.md. Resume from those records without reopening addressed items or beginning an unrequested lecture.

Questions are learning notes, not code-review findings or new acceptance criteria. Keep Q IDs separate from the MNN-NNN review ledger. They need not all be answered before advancing. Scratchpad updates at requested review/handoff are part of the normal workflow; do not rewrite the learner's original reasoning.

## Obstacles and stumbles

Use the same questions.md file with a `## Stumbles` section and stable local S1, S2, … IDs. Add entries when a real obstacle is explicitly reported or evidenced in an authorized review/teaching exchange; persist them at review/handoff. Do not continually inspect files or interrupt independent work. An accurate finding reported while working is still logged silently at session end under the existing rule.

Keep each entry concise: date, observation/context, help or attempt if known, and outcome (open, resolved with evidence, or deferred). Distinguish learner reports from direct observations and independent recovery from recovery after guidance. Do not infer confusion from elapsed time, turn every question into a mistake, or log trivial typos. Link relevant Q IDs and canonical code-review IDs; do not duplicate or silently resolve the review ledger.

At handoff, use cpp-qa's recording rules alongside cpp-session-handoff. Save actual answers/takeaways, leave uncertain answers and unresolved obstacles open, and link outstanding Q/S IDs from progress.md. Avoid duplicating full notes into progress or inventing mastery. These records guide later explanation within the existing scope; they do not create new completion gates, automatic drills, or retroactive assignments.

## Standing authorization and skill boundaries

The learner's request to integrate skills authorizes the full-review transition from correctness to idioms, the scheduled module quiz, and handoff logging at phase boundaries without a separate skill invocation. Within this workspace it supersedes older skill wording that requires a separate explicit quiz request or prohibits every automatic follow-on pass. It does not authorize core implementation fixes, new drills, inspecting work without a review request, or advancing past unmet requirements without an explicit learner decision.

Load the installed skill's SKILL.md through the available skill catalog when its step begins; do not merely mention the skill name. If a skill is unavailable, say so briefly and follow the same local workflow rather than requiring the learner to troubleshoot invocation.

Use a structured question tool for the quiz only when its actual contract permits assessment questions. Otherwise use text choices. Do not switch modes, label the answer recommended, or treat a default/timeout as an answer. Wait for each explicit answer. Log only the actual score or skip/partial status; never infer mastery from participation.

## Preserve momentum and evidence

- Reuse applicable current verification. Do not rerun an unchanged full suite just to enter a second review phase.
- Keep `bug`, `test-gap`, and actionable `design` findings distinct. Follow reviews.md for single-line stable IDs and resolution evidence.
- A learner-approved checkpoint can defer work without satisfying all acceptance criteria. Preserve that decision, retain open evidence, and mark the idioms pass deferred if its correctness gate is not met. Do not reassign deferred testing as a surprise drill.
- Record review phases as pending, complete, deferred or skipped only when supported. Record quiz progress if interrupted so the next agent does not restart it; preserve remaining questions/answer key only in teacher notes when needed, not in the learner's next prompt.
- Historical exception: Module 4's implementation checkpoint was accepted with M04-006 evidence open. Consult progress.md for its current status. This reformat does not resolve that evidence or retroactively require reviews/quizzes for completed Modules 1–3.
- Module 11 has one combined implementation/debugging challenge. The capstone's own defects and regression work provide debugging practice; do not add a separate challenge.

## Document format

Each exercise README uses `## For you` with `### Goal`, `### Steps`, `### Build`, `### Check`, and `### Scope`, then `## For the teacher` with collapsible notes. Debugging READMEs use the same split, with Scope only when needed. Preserve public contracts, input grammars and existing anchors when moving content.

Keep all behavioral requirements and acceptance checks visible to the learner. Teacher notes contain prerequisites, teaching focus, generation/calibration guidance and links to progress, never hidden grading requirements or undisclosed solutions. Session logs retain their historical format. Maintain phase state in progress.md rather than duplicating changing status across READMEs.
