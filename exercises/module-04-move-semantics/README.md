# Module 4 — Move Semantics Deep Dive

## For you

### Goal

Build a move-only byte buffer, processing slot, forwarding relay and return-by-value factory. Practice ownership handoff across APIs.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

#### `UniqueBuffer`

Provide this public API:

```cpp
explicit UniqueBuffer(std::size_t size = 0);
~UniqueBuffer();
UniqueBuffer(const UniqueBuffer&) = delete;
UniqueBuffer& operator=(const UniqueBuffer&) = delete;
UniqueBuffer(UniqueBuffer&&) noexcept;
UniqueBuffer& operator=(UniqueBuffer&&) noexcept;
std::size_t size() const noexcept;
bool empty() const noexcept;
std::byte* data() noexcept;
const std::byte* data() const noexcept;
std::byte& at(std::size_t index);
const std::byte& at(std::size_t index) const;
```

- Own a raw `new[]` allocation of `std::byte`; release it with `delete[]`. Do not use a container or smart pointer for the storage.
- Construction creates exactly `size` zero-initialized bytes. Zero size means a null pointer.
- `at()` throws `std::out_of_range` when `index >= size()`.
- Moving transfers the existing allocation without allocating or copying bytes. The source becomes empty with a null pointer.
- Move assignment releases the destination's previous allocation. Self-move preserves its existing contents and pointer.
- Every public operation preserves exclusive ownership and the invariant `size() == 0` if and only if `data() == nullptr`.

#### `BufferSlot`

Own one `UniqueBuffer` and provide:

```cpp
void submit(UniqueBuffer buffer);
const UniqueBuffer& peek() const noexcept;
UniqueBuffer take() noexcept;
```

- `submit` replaces the stored buffer by transferring ownership of its parameter. An empty buffer is allowed.
- A default-constructed slot is empty. `submit` performs no allocation or byte copying after its parameter has been constructed.
- `peek` provides read-only observation without a transfer.
- The reference returned by `peek` observes the slot's current buffer object and must not outlive the slot. A saved byte pointer has a separate lifetime governed by the allocation's owner; do not dereference it after that allocation is released.
- `take` returns the stored buffer by value, leaving the slot empty. It transfers the allocation without copying or allocating.
- A buffer passed from a named caller variable must be explicitly surrendered by the caller; temporaries must work directly.

#### Forwarding and return values

- Write a function template `relay(BufferSlot& slot, T&& buffer)` that forwards its argument to `submit`, preserving its value category. Do not unconditionally treat every argument as movable.
- Write a factory `make_buffer(std::size_t size)` that creates a named local buffer, fills its bytes with `std::byte{0x2a}`, and returns it by value.
- At the factory return, let the language perform return-value optimization or implicit movement.

### Check

Write checks in `main.cpp` that fail visibly when the expected result is wrong. Merely calling a function does not test its result. Keep checks active even if `NDEBUG` is defined (plain `assert` is disabled in that build).

A source is the object you move from; a destination is the object receiving its storage. A moved-from object is still alive, but this exercise requires it to be empty.

| What to test | What to do and check |
|---|---|
| Empty construction | Construct with no size, and with size zero. Check size zero, `empty()` true, and `data()` null. |
| Nonempty construction | Construct a small buffer. Check its requested size, a non-null pointer, and that every byte is zero. |
| Reading and writing | Change a byte through `at()`, then check its new value. Also read through a const reference to the buffer. |
| Bad index | Call `at(size())` and `at(0)` on an empty buffer. Check that `std::out_of_range` is thrown. Exercise both const and non-const access. |
| Move construction | Put recognizable bytes in a source and save its `data()` pointer. Construct a new destination by moving the source. Check the destination has that exact pointer, size, and bytes. Check the source is empty with a null pointer. |
| Move assignment | Start with two nonempty buffers. Move one into the other using assignment. Check the same pointer, size, contents, and empty-source results as above. Run sanitizers to help catch incorrect memory handling. |
| Self-move | Move a buffer into itself using assignment. Check that its pointer, size, and bytes are unchanged. |
| Move from empty | Move an empty source into a nonempty destination. Check both objects end empty with null pointers. |
| Reuse after moving | After moving out of a buffer, assign another buffer into it. Check it now owns the new storage and can be accessed normally. |
| Empty slot | Construct a slot and check `peek()` reports an empty buffer. |
| Submit | Submit a freshly constructed temporary buffer. Separately submit a named buffer using `std::move`. Check the slot's size and bytes, and that the named source became empty. |
| Replace slot contents | Submit a second buffer into a populated slot. Check it now holds the second buffer's pointer, size, and bytes. Also submit an empty buffer and check the slot becomes empty. |
| Take | Take from a populated slot. Check the result owns the former pointer and contents, and the slot is empty. Taking from an empty slot should return an empty buffer. |
| Relay | Repeat submission through `relay`: once with a temporary, once with a named buffer passed using `std::move`. Check the same transfer results. |
| Factory | Check `make_buffer(0)` is empty. For a nonzero size, check the size and that every byte equals `std::byte{0x2a}`. Run these checks with both normal and no-elide builds. |

Saving a pointer before a transfer and comparing it afterward checks that the existing allocation was handed over. Do not dereference saved pointers after their storage has been released. Review the transfer code as well to confirm it makes no allocation or byte copy.

Use `<type_traits>` and compile-time checks (`static_assert`) to confirm these four facts: `UniqueBuffer` cannot be copy constructed, cannot be copy assigned, can be move constructed without throwing, and can be move assigned without throwing. The corresponding traits are `std::is_copy_constructible_v`, `std::is_copy_assignable_v`, `std::is_nothrow_move_constructible_v`, and `std::is_nothrow_move_assignable_v`.

Finally, try these calls separately, one at a time. Each must fail to compile; record a brief explanation, then remove it from the runnable tests:

- Pass a named buffer directly to `submit`, without `std::move`.
- Pass a const buffer to `submit` using `std::move`.
- Pass a named buffer directly to `relay`, without `std::move`.

These failures are part of the intended API. Do not change the class to allow copying. You do not need to count factory moves: the compiler can omit some moves, so different valid builds may have different counts.

Run `make run`, `make run-sanitized`, and `make run-no-elide`. Compile with C++20 and `-Wall -Wextra -Wpedantic -g`; `make clean` removes build outputs. Briefly explain the rejected calls and why the factory works without optional elision.

### Scope

No growth/capacity API, copying, iterators or generic storage. The no-elide build disables optional NRVO, not mandatory C++17 prvalue elision.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–3. New learning is value categories, const interaction, forwarding and return-value behavior; do not repeat the Rule-of-Five drill. Module 5 covers broader template constraints; Module 6 covers generic element lifetime.

The accepted implementation checkpoint and deferred M04-006 evidence are recorded in progress.md. Preserve that exception and consult progress.md for the packet-delivery phase. Do not restart implementation, silently resolve evidence gaps, or assign repetitive test drills during this formatting/workflow change. An accepted checkpoint is not a claim that all requirements are verified.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>
