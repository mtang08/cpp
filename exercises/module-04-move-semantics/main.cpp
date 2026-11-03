#include <cstddef>
#include <stdexcept>
#include <utility>

class UniqueBuffer {
  std::size_t size_;
  std::byte *data_;

public:
  explicit UniqueBuffer(std::size_t size = 0);
  ~UniqueBuffer();
  UniqueBuffer(const UniqueBuffer &) = delete;
  UniqueBuffer &operator=(const UniqueBuffer &) = delete;
  UniqueBuffer(UniqueBuffer &&) noexcept;
  UniqueBuffer &operator=(UniqueBuffer &&) noexcept;
  std::size_t size() const noexcept;
  bool empty() const noexcept;
  std::byte *data() noexcept;
  const std::byte *data() const noexcept;
  std::byte &at(std::size_t index);
  const std::byte &at(std::size_t index) const;
};

UniqueBuffer::UniqueBuffer(std::size_t size) : size_{size} {
  if (!size) {
    data_ = nullptr;
    return;
  }

  // 2026-10-10 codex: [M04-001] [resolved] [bug] Construction left bytes uninitialized; the spec
  // requires every byte to start at zero. Verified 2026-10-10: explicit initialization reviewed and
  // all bytes checked in an independent probe.
  data_ = new std::byte[size];
  for (std::size_t i = 0; i < size; ++i) {
    data_[i] = std::byte{0};
  }
}

UniqueBuffer::~UniqueBuffer() {
  // 2026-10-10 codex: [M04-002] [resolved] [bug] Scalar deletion mismatched the array allocation,
  // causing undefined behavior. Verified 2026-10-10: array deletion reviewed and nonempty
  // destruction exercised under ASan/UBSan.
  delete[] data_;
  data_ = nullptr;
}

UniqueBuffer::UniqueBuffer(UniqueBuffer &&other) noexcept {
  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
}

UniqueBuffer &UniqueBuffer::operator=(UniqueBuffer &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  // 2026-10-10 codex: [M04-003] [resolved] [bug] Assignment overwrote the destination's owning
  // pointer without releasing its allocation. Verified 2026-10-10: release before transfer
  // reviewed; assignment into nonempty storage and assignment from empty exercised under
  // ASan/UBSan.
  if (data_)
    delete[] data_;

  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
  return *this;
}

std::size_t UniqueBuffer::size() const noexcept { return size_; }
bool UniqueBuffer::empty() const noexcept { return size_ == 0; }

std::byte *UniqueBuffer::data() noexcept { return data_; }

const std::byte *UniqueBuffer::data() const noexcept { return data_; }

std::byte &UniqueBuffer::at(std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("index out of range");
  }
  return data_[index];
}

const std::byte &UniqueBuffer::at(std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("index out of range");
  }
  return data_[index];
}

class BufferSlot {
  UniqueBuffer b;

public:
  // 2026-10-10 codex: [M04-004] [resolved] [bug] A default slot owned one byte instead of being empty. Verified 2026-10-10: zero-sized construction reviewed and empty-slot check passes in all three builds.
  BufferSlot() : b(0) {}
  void submit(UniqueBuffer buffer);
  const UniqueBuffer &peek() const noexcept;
  UniqueBuffer take() noexcept;
};

void BufferSlot::submit(UniqueBuffer buffer) { b = std::move(buffer); }

const UniqueBuffer &BufferSlot::peek() const noexcept { return b; }

UniqueBuffer BufferSlot::take() noexcept { return std::move(b); }

template <typename T> void relay(BufferSlot &slot, T &&buffer) {
  // 2026-10-10 codex: [M04-005] [resolved] [bug] Relay lost the caller's value category. Verified 2026-10-10: temporary and explicit-move calls pass all three builds; an independent lvalue call fails through the deleted copy constructor as required.
  slot.submit(std::forward<T>(buffer));
}

UniqueBuffer make_buffer(std::size_t size) {
  UniqueBuffer b(size);
  std::byte *data = b.data();
  for (std::size_t i = 0; i < size; ++i) {
    data[i] = std::byte{0x2a};
  }
  return b;
}

int main() {
  // 2026-10-10 codex: [M04-006] [open] [test-gap] Harness now exercises most behavior, but required checks remain: const-buffer access and bounds, nonempty at(size()), move-assignment source state, reused-buffer pointer identity, temporary submission before replacement, replacement pointer identity, take from empty, relay source state and contents, factory size/null state, type traits, and explanations of rejected calls and no-elide return behavior.
  auto check = [](bool ok) {
    if (!ok)
      throw std::runtime_error("test failed");
  };

  // empty construction
  UniqueBuffer no_size;
  check(no_size.size() == 0);
  check(no_size.empty() && no_size.data() == nullptr);
  UniqueBuffer size_zero(0);
  check(size_zero.size() == 0);
  check(size_zero.empty() && size_zero.data() == nullptr);

  // nonempty construction
  UniqueBuffer small(3);
  check(small.size() == 3 && small.data() != nullptr);
  for (std::size_t i = 0; i < 3; ++i) {
    check(small.at(i) == std::byte(0));
  }

  // reading and writing
  small.at(0) = std::byte(8);
  check(small.at(0) == std::byte(8));
  const std::byte &val = small.at(1);
  check(val == std::byte(0));

  // bad index
  UniqueBuffer empty;
  bool threw_size = false;
  bool threw_first = false;
  try {
    empty.at(0);
  } catch (const std::out_of_range &) {
    threw_first = true;
  }
  try {
    empty.at(empty.size());
  } catch (const std::out_of_range &) {
    threw_size = true;
  }
  check(threw_size && threw_first);

  // move construction
  UniqueBuffer source(3);
  for (std::size_t i = 0; i < 3; ++i) {
    source.at(i) = std::byte((i + 1) * 8);
  }
  auto data = source.data();
  UniqueBuffer dst(std::move(source));
  check(dst.data() == data);
  check(dst.size() == 3);
  for (std::size_t i = 0; i < 3; ++i) {
    check(dst.at(i) == std::byte((i + 1) * 8));
  }
  check(source.empty() && source.data() == nullptr);

  // move assignment
  UniqueBuffer one(1);
  UniqueBuffer two(2);
  one.at(0) = std::byte(67);
  auto ptr = one.data();
  two = std::move(one);
  check(two.data() == ptr && two.size() == 1 && two.at(0) == std::byte(67));

  // self-move
  UniqueBuffer self(3);
  for (std::size_t i = 0; i < 3; ++i) {
    self.at(i) = std::byte(i + 1);
  }
  auto before = self.data();
  self = std::move(self);
  check(self.data() == before && self.size() == 3);
  for (std::size_t i = 0; i < 3; ++i) {
    check(self.at(i) == std::byte(i + 1));
  }

  // move from empty
  UniqueBuffer empty_src;
  UniqueBuffer nonempty_dst(10);
  nonempty_dst = std::move(empty_src);
  check(nonempty_dst.data() == nullptr && empty_src.data() == nullptr);
  check(nonempty_dst.empty() && empty_src.empty());

  // reuse after moving
  UniqueBuffer checkee(3);
  UniqueBuffer tmp(std::move(checkee));
  UniqueBuffer sac(5);
  checkee = std::move(sac);
  check(checkee.size() == 5);
  for (std::size_t i = 0; i < 5; ++i) {
    bool threw = false;
    try {
      checkee.at(i);
    } catch (std::out_of_range &) {
      threw = true;
    }
    check(!threw);
  }

  // empty slot
  BufferSlot bs;
  check(bs.peek().empty());

  // submit
  bs.submit(UniqueBuffer(1));
  UniqueBuffer named(2);
  bs.submit(std::move(named));
  check(bs.peek().size() == 2 && bs.peek().at(0) == std::byte(0) &&
        bs.peek().at(1) == std::byte(0));
  check(named.data() == nullptr && named.empty());

  // replace slot contents
  UniqueBuffer second(3);
  for (std::size_t i = 0; i < 3; ++i) {
    second.at(i) = std::byte(0xfa);
  }
  bs.submit(std::move(second));
  check(bs.peek().size() == 3);
  for (std::size_t i = 0; i < 3; ++i) {
    check(bs.peek().at(i) == std::byte(0xfa));
  }
  UniqueBuffer empty1;
  bs.submit(std::move(empty1));
  check(bs.peek().empty());

  // take
  UniqueBuffer takee(3);
  for (std::size_t i = 0; i < 3; ++i) {
    takee.at(i) = std::byte(0xfa);
  }
  bs.submit(std::move(takee));
  auto ptr1 = bs.peek().data();
  auto taken = bs.take();
  check(ptr1 == taken.data());
  check(taken.size() == 3);
  for (std::size_t i = 0; i < 3; ++i) {
    check(taken.at(i) == std::byte(0xfa));
  }
  check(bs.peek().empty());

  // relay
  UniqueBuffer named_buffy(3);
  BufferSlot buffy_slot;
  relay(buffy_slot, UniqueBuffer(2));
  check(buffy_slot.peek().size() == 2 && buffy_slot.peek().at(0) == std::byte(0) && buffy_slot.peek().at(1) == std::byte(0));
  relay(buffy_slot, std::move(named_buffy));
  check(buffy_slot.peek().size() == 3);

  // factory
  auto b = make_buffer(0);
  check(b.empty());

  auto c = make_buffer(67);
  for (std::size_t i = 0; i < 67; ++i) {
    check(c.at(i) == std::byte(0x2a));
  }

  // final checks
//   buffy_slot.submit(named_buffy); // does not compile
  const UniqueBuffer const_buff(2);
//   buffy_slot.submit(const_buff); // does not compile
//   relay(buffy_slot, const_buff); // does not compile

  return 0;
}
