# Module 6 — Containers, Storage, and Element Lifetime

## For you

### Goal

A bounded vector<T> implementation.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Implement an owning contiguous container with size, capacity, empty, indexed access, checked at, reserve, clear, push_back(const T&) and push_back(T&&), destruction and move operations. Copying the container may be deleted. Use std::allocator<T> and allocator_traits for storage/lifetime operations. Do not use new T[capacity] or an STL container as backing storage.

Support non-default-constructible types and move-only types with nonthrowing moves. Require nonthrowing destruction and either copy construction or nonthrowing move construction. Copy append only participates for copy-constructible types. reserve never shrinks; clear destroys live elements but retains storage. Moves leave the source empty with zero capacity; self-move leaves it valid. Only [0,size) contains live elements.

For supported types, failed reserve or append must leave the container's prior size, capacity and element values intact. An external rvalue argument may be modified by its own throwing constructor. Append arguments must not refer to an element inside this container; document that explicit precondition. Detect capacity/size overflow before allocation. Choose a growth policy and document invalidation. No custom iterator implementation is required.

### Check

Use lifetime-counting, non-default-constructible, move-only and copy-throwing test types. Test relocation failure, destruction counts, empty states, bounds and reuse after move. Explain vector/map/unordered_map/deque choices for ID lookup and ordered price queries; implement only this container.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: Full std::vector compatibility, allocator propagation, custom allocators, copyable container semantics and throwing move-only relocation. This adds object lifetime to Module 3, not another integer array.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–5.

Teaching focus: Separate raw storage from live objects; allocator_traits, construction/destruction, relocation, exception guarantees and invalidation. Compare standard container complexity and locality.

Project connection: Understand standard containers before choosing book indexes.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
