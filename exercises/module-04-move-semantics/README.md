# Module 4 — Move Semantics Deep Dive

## Challenge: move-only buffer handoff

Build a move-only byte buffer and a single-buffer processing slot. The goal is to make ownership transfers explicit and understand when expressions permit or prevent moving. Write the implementation and tests yourself; no conversational checkpoints are required.

Status: active. Prerequisites: Modules 1–3. The new learning is ownership handoff across APIs, forwarding, and return values. The buffer reinforces earlier ownership work; do not add capacity/growth, copying, iterators, or generic storage. Module 5 covers broader template constraints and Module 6 covers generic element lifetime. This exercise prepares you to distinguish owned input from borrowed observation in the replay project.

### `UniqueBuffer`

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

### `BufferSlot`

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

### Forwarding and return values

- Write a function template `relay(BufferSlot& slot, T&& buffer)` that forwards its argument to `submit`, preserving its value category. Do not unconditionally treat every argument as movable.
- Write a factory `make_buffer(std::size_t size)` that creates a named local buffer, fills its bytes with `std::byte{0x2a}`, and returns it by value.
- At the factory return, let the language perform return-value optimization or implicit movement.

### Verification

Use meaningful checks in `main.cpp` covering:

- Empty and nonempty construction, zero initialization, mutable and const access, and out-of-range access.
- Move construction and move assignment into a nonempty destination. Record the original pointer and verify destination pointer identity, contents, and empty source state.
- Self-move and moving an empty buffer into a nonempty buffer.
- Reuse of a moved-from object through assignment.
- Submission of a temporary and an explicitly surrendered named buffer; replacement of an existing slot value; taking from populated and empty slots.
- Forwarding a temporary and an explicitly surrendered named buffer through `relay`.
- A factory result that survives normal builds and builds with `-fno-elide-constructors`.
- `make_buffer(0)` returns an empty buffer; nonempty results contain only `std::byte{0x2a}`. Do not require a specific move-constructor count when optional elision is enabled.
- Type traits confirming the buffer is noncopyable and nothrow move constructible/assignable.

Also try these intentionally invalid calls separately from the runnable harness: submit a named buffer without surrendering it; submit a const buffer through `std::move`; relay a named buffer as an lvalue. Record briefly why each fails, then keep the normal build valid. Do not change the API to make those calls succeed.

### Build and review

Use C++20 with `-Wall -Wextra -Wpedantic -g`. The supplied Makefile supports `make run`, `make run-sanitized`, `make run-no-elide`, and `make clean`.

Work through implementation, compilation, and debugging independently. When ready for review, include your explanation of the rejected calls and why the factory works even when optional elision is disabled.

The no-elide flag disables optional elision such as NRVO; it does not disable mandatory C++17 prvalue elision. Keep the explanation brief. Passing the stated checks and addressing review findings completes the implementation exercise; no extra move-semantics drills are required. A separate focused debugging session will be generated using your latest difficulty rating.
