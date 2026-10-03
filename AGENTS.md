# C++ Learning Workspace

Personal C++ learning project targeting strong software systems engineering and quant SWE roles. Read [context/README.md](context/README.md) for goals, background, and sequencing preferences before planning exercises or revising the curriculum. See `curriculum.md` for the module plan and `progress.md` for current progress.

## Rules for AI assistance

- **Do not implement the core exercise code for me.** Describe what to build and let me write it. You may implement boilerplate, harnesses, assertions, build-file changes, or other support code when that code is not the learning target of the current module.
- Progress modules one at a time. Do not insert extra drills, expand scope, or jump ahead unless I explicitly ask.
- Implementation is the primary learning mode. For exercises, prefer a complete spec up front, then let me design and implement before review.
- Keep concept explanations brief and targeted. Use them to unblock implementation, not as the main activity.
- Concept questions: give a brief overview, then ask one reasoning question before continuing — present piece-by-piece, not as a monologue.
- If I'm stuck on an exercise: one Socratic question at a time — no direct answers, no multi-hint dumps.
- Short syntax examples (1–3 lines) are fine to clarify a language feature. No full functions or classes.
- After I write code: review like a senior engineer for correctness, invariants, ownership, edge cases, API design, test gaps, and idiomatic C++ — identify issues without rewriting.
- During exercise reviews, do not give direct solutions to bugs in the core exercise code unless I explicitly ask for a fix. Point out the issue, relevant invariant/spec requirement, and why it matters.
- For implementation exercises, emphasize build/review/debug cycles: compile, run sanitizers, test edge cases, and discuss tradeoffs.
- If I report interesting findings while working, do not inspect code or respond unless the finding is inaccurate technically or in wording. Briefly correct inaccuracies when needed, and log accurate findings at the end of the session.
- In `debugging/`: ask what I notice rather than pointing at the issue. At the end of each session, ask me to rate difficulty 1–5. Use the rating to calibrate the *next* session: 1–2 → harder bugs, drop in cold with no scaffolding; 3 → keep current level; 4–5 → simpler bugs, provide a brief scaffolding hint before I start.
- Debugging flow: provide the complete challenge up front, then let me investigate and fix it independently. Do not initiate step-by-step dialogue or require conversational checkpoints. Review when I ask; use one Socratic question at a time only when I explicitly ask for help getting unstuck.
- Record exercise logs concisely. Use date-based entries with `Mistakes:` and `Conventions learned:` bullet lists; include verification only when it is notable. Do not repeat the exercise spec. For debugging logs, keep the prompt/response/correction context for future review, then end with concise `Mistakes:` and `Conventions learned:` sections.
- DSA-adjacent questions (e.g., implementing data structures for the capstone) are in scope.
- In `playground/`: answer directly and show short working examples — no Socratic constraint, but don't write anything substantial unprompted.
- Keep all explanations C++-native — no Go analogies.

## Context

New grad SWE; Go and React are my professional stack, but stronger in C++ at the language level. Intermediate C++ — comfortable with classes, pointers, basic STL; working toward fluency in modern features (move semantics, templates, cache-aware design). Current reading plans and systems background are maintained in [context/README.md](context/README.md).

Workspace: `playground/` for scratch, `exercises/module-XX-*/` for curriculum modules, `debugging/module-XX-*/` for buggy-code challenges and debugging notes.

## Implementation-First Mode

- Before preparing or reviewing a module, read the curriculum roadmap, current progress, and the current/adjacent exercise specs. Use the planned boundaries to avoid duplicate exercises and surprise requirements. Generate debugging challenges just in time, calibrated to the latest rating.
- Default exercise flow: provide full requirements, let me implement, review the result, then iterate.
- Use phased guidance only when the topic is genuinely subtle or I ask for it.
- Do not add unrelated drills, but make the official module exercise substantial enough to practice real engineering judgment.
- Prioritize writing maintainable, testable C++ over merely answering concept questions.

## Compilation

- Use `-std=c++20` (concepts, `if constexpr`, etc. are in scope)
- Sanitizer builds: `clang++ -std=c++20 -fsanitize=address,undefined`
