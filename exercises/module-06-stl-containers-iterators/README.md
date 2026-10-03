# Module 6 — Containers, Storage, and Element Lifetime

Status: specified, not started. Prerequisites: Modules 1–5; proceed in sequence.

## New learning

Separate raw storage from live objects; allocator_traits, construction/destruction, relocation, exception guarantees and invalidation. Compare standard container complexity and locality.

## Exercise: A bounded vector<T> implementation

Implement an owning contiguous container with size, capacity, empty, indexed access, checked at, reserve, clear, push_back(const T&) and push_back(T&&), destruction and move operations. Copying the container may be deleted. Use std::allocator<T> and allocator_traits for storage/lifetime operations. Do not use new T[capacity] or an STL container as backing storage.

Support non-default-constructible types and move-only types with nonthrowing moves. Require nonthrowing destruction and either copy construction or nonthrowing move construction. Copy append only participates for copy-constructible types. reserve never shrinks; clear destroys live elements but retains storage. Moves leave the source empty with zero capacity; self-move leaves it valid. Only [0,size) contains live elements.

For supported types, failed reserve or append must leave the container's prior size, capacity and element values intact. An external rvalue argument may be modified by its own throwing constructor. Append arguments must not refer to an element inside this container; document that explicit precondition. Detect capacity/size overflow before allocation. Choose a growth policy and document invalidation. No custom iterator implementation is required.

## Verification and review

Use lifetime-counting, non-default-constructible, move-only and copy-throwing test types. Test relocation failure, destruction counts, empty states, bounds and reuse after move. Explain vector/map/unordered_map/deque choices for ID lookup and ordered price queries; implement only this container.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: Full std::vector compatibility, allocator propagation, custom allocators, copyable container semantics and throwing move-only relocation. This adds object lifetime to Module 3, not another integer array.

Capstone connection: Understand standard containers before choosing book indexes.
