# Module 3 — The Rule of Five and Value Semantics

## For you

### Goal

Implement an owning dynamic array of int to practice value semantics and the five special members.

### Steps

Archived exercise; no new work is assigned here.

### Build

Create `main.cpp` and a `Makefile` in this directory.

The class should be named `DynamicArray`.

#### Core API

- Constructor: `DynamicArray(std::size_t initial_capacity)`
- Destructor
- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator
- `std::size_t size() const`
- `std::size_t capacity() const`
- `bool empty() const`
- `void push_back(int value)`
- `int& operator[](std::size_t index)`
- `const int& operator[](std::size_t index) const`
- `int& at(std::size_t index)`
- `const int& at(std::size_t index) const`

#### Behavior

- The array owns a heap allocation for `int` elements.
- `size()` is the number of constructed/logically present elements.
- `capacity()` is the number of elements the allocation can currently hold.
- `push_back` appends a value.
- If `push_back` would exceed capacity, allocate a larger buffer, copy existing values, release the old buffer, and then append.
- `operator[]` may assume the index is valid.
- `at()` must check bounds and throw `std::out_of_range` on invalid index.
- A copied `DynamicArray` must own its own allocation. Mutating the copy must not mutate the original.
- A moved-from `DynamicArray` must remain destructible and valid to query with `size()`, `capacity()`, and `empty()`.

#### Invariants

Maintain these after every public operation:

- If `capacity_ == 0`, the data pointer may be `nullptr`.
- If `capacity_ > 0`, the data pointer should own an allocation of `capacity_` integers.
- `size_ <= capacity_`.
- Destruction releases exactly the allocation owned by that object.
- No two live `DynamicArray` objects should believe they exclusively own the same allocation.

### Check

Write tests or checks that demonstrate:

- Constructing an empty or small array.
- Appending within capacity.
- Appending past capacity triggers growth.
- `operator[]` and `at()` work for valid indices.
- `at()` throws for an invalid index.
- Copy construction performs a deep copy.
- Copy assignment performs a deep copy.
- Move construction transfers ownership and leaves the source valid.
- Move assignment transfers ownership and leaves the source valid.
- Self-copy-assignment does not corrupt the object.
- Self-move-assignment does not corrupt the object.

Build targets: `make run`, `make run-sanitized`, `make clean`.

### Scope

- Use raw `new[]` and `delete[]` internally for this exercise.
- Do not use `std::vector`, `std::unique_ptr`, or `std::shared_ptr` inside `DynamicArray`.
- Keep the class non-template for now: `int` only.
- Prefer clear invariants and correctness over cleverness.
- Compile with `-std=c++20 -Wall -Wextra -Wpedantic -g`.
- Run with AddressSanitizer/UBSan before review.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Historical completed module. Preserve its original contract and work; no new review, quiz or debugging requirement is added retroactively.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
