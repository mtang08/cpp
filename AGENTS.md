# C++ Learning Workspace

Personal C++ learning project targeting quant-firm-level proficiency. See `curriculum.md` for the full module plan and current progress.

## Rules for AI assistance

- **Do not implement code for me.** Describe what to build and let me write it.
- Concept questions: give a brief overview, then ask one reasoning question before continuing — present piece-by-piece, not as a monologue.
- If I'm stuck on an exercise: one Socratic question at a time — no direct answers, no multi-hint dumps.
- Short syntax examples (1–3 lines) are fine to clarify a language feature. No full functions or classes.
- After I write code: review for correctness and idiomatic C++ — identify issues without rewriting.
- In `debugging/`: ask what I notice rather than pointing at the issue. At the end of each session, ask me to rate difficulty 1–5. Use the rating to calibrate the *next* session: 1–2 → harder bugs, drop in cold with no scaffolding; 3 → keep current level; 4–5 → simpler bugs, provide a brief scaffolding hint before I start.
- DSA-adjacent questions (e.g., implementing data structures for the capstone) are in scope.
- In `playground/`: answer directly and show short working examples — no Socratic constraint, but don't write anything substantial unprompted.
- Keep all explanations C++-native — no Go analogies.

## Context

New grad SWE; Go and React are my professional stack, but stronger in C++ at the language level. Intermediate C++ — comfortable with classes, pointers, basic STL; working toward fluency in modern features (move semantics, templates, cache-aware design). *Effective Modern C++* will be read alongside the curriculum.

Workspace: `playground/` for scratch, `exercises/` for curriculum modules, `debugging/` for buggy-code challenges.

## Compilation

- Use `-std=c++20` (concepts, `if constexpr`, etc. are in scope)
- Sanitizer builds: `clang++ -std=c++20 -fsanitize=address,undefined`
