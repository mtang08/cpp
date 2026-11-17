# Questions and learning notes

## Open

## Addressed

- Q1 — 2026-11-08: why does an const rvalue route to the copy constructor, when the copy constructor takes a const reference
  Answer discussed 2026-11-08: a const lvalue reference can bind to rvalues. `std::move` preserves constness, so the move constructor's non-const rvalue reference cannot bind, while the copy constructor's const reference can. See session-2026-11-08.md for the original explanation.
- Q2 — 2026-11-08: for some reason i didn't think you could/should store references to objects as a class member variable. is this belief unfounded?
  Answer discussed 2026-11-08: reference members are valid non-owning observations when the referred object outlives the observer. They must be initialized and cannot be rebound. The learner identified `&` and applied a reference member successfully.

## Stumbles

- S1 — 2026-11-08: Learner observed archive copying but described successive moves as an rvalue of an rvalue. Guided discussion traced preserved constness and constructor binding (Q1). Resolved after guidance: reviewed archive transfers without copies in both builds.
- S2 — 2026-11-08: Learner identified inspection's stale data but attempted to borrow an inbox using a by-value member. Guided question distinguished value storage from reference storage (Q2). Resolved after guidance: final inspector uses an inbox reference and passes replacement checks under ASan/UBSan.
