#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

struct Work {
    inline static std::size_t allocations = 0, copies = 0;
    static void reset() { allocations = copies = 0; }
};

class Packet {
    std::size_t size_ = 0;
    int* data_ = nullptr;
    static int* allocate(std::size_t n) {
        if (!n) return nullptr;
        int* p = new int[n];
        ++Work::allocations;
        return p;
    }
public:
    Packet() = default;
    Packet(std::initializer_list<int> values)
        : size_(values.size()), data_(allocate(size_)) {
        if (size_) std::copy(values.begin(), values.end(), data_);
    }
    ~Packet() { delete[] data_; }
    Packet(const Packet& other)
        : size_(other.size_), data_(allocate(size_)) {
        if (size_) std::copy_n(other.data_, size_, data_);
        ++Work::copies;
    }
    Packet& operator=(const Packet& other) {
        if (this == &other) return *this;
        int* replacement = allocate(other.size_);
        if (other.size_) std::copy_n(other.data_, other.size_, replacement);
        delete[] data_;
        data_ = replacement;
        size_ = other.size_;
        ++Work::copies;
        return *this;
    }
    Packet& operator=(Packet&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = std::exchange(other.data_, nullptr);
        size_ = std::exchange(other.size_, 0);
        return *this;
    }
    Packet(Packet&& other) noexcept {
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    std::size_t size() const noexcept { return size_; }
    int& operator[](std::size_t i) { return data_[i]; }
    const int& operator[](std::size_t i) const { return data_[i]; }
};

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* label) {
        std::cout << (ok ? "PASS: " : "FAIL: ") << label << '\n';
        if (!ok) ++failures;
    };
    auto report = [] {
        std::cout << "  allocations=" << Work::allocations << " copies=" << Work::copies << '\n';
    };
    Packet original{10, 20, 30};
    Packet copied(original);
    copied[0] = 99;
    check(original[0] == 10 && copied[0] == 99, "independent copy storage");
    Work::reset();
    Packet received(std::move(original));
    report();
    check(received.size() == 3 && received[2] == 30, "constructed destination contents");
    check(original.size() == 0, "constructed transfer leaves source empty");
    check(Work::allocations == 0 && Work::copies == 0, "constructed transfer does no copying or allocation");
    original = received;
    original[0] = -1;
    check(original[0] == -1 && received[0] == 10, "modified own copy of bytes");
    check(original.size() == received.size(), "copied should be same size");
    Packet assigned{1};
    Work::reset();
    assigned = std::move(received);
    report();
    check(assigned.size() == 3 && assigned[1] == 20 && received.size() == 0, "assigned transfer contents and source state");
    check(Work::allocations == 0 && Work::copies == 0, "assigned transfer does no copying or allocation");
    std::vector<Packet> packets;
    packets.reserve(2);
    packets.emplace_back(std::initializer_list<int>{4, 5});
    packets.emplace_back(std::initializer_list<int>{6, 7});
    Work::reset();
    packets.reserve(packets.capacity() + 1);
    report();
    check(packets[0][0] == 4 && packets[1][1] == 7, "growth preserves contents");
    check(Work::allocations == 0 && Work::copies == 0, "growth transfers existing storage");
    std::cout << failures << " failed checks\n";
    return failures == 0 ? 0 : 1;
}
