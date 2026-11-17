#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

// Supplied support: leave Payload unchanged.
class Payload {
    std::vector<int> values_;
public:
    inline static int copies = 0;
    Payload() = default;
    Payload(std::initializer_list<int> values) : values_(values) {}
    Payload(const Payload& other) : values_(other.values_) { ++copies; }
    Payload& operator=(const Payload& other) {
        if (this != &other) { values_ = other.values_; ++copies; }
        return *this;
    }
    Payload(Payload&& other) noexcept
        : values_(std::exchange(other.values_, std::vector<int>{})) {}
    Payload& operator=(Payload&& other) noexcept {
        if (this != &other) values_ = std::exchange(other.values_, std::vector<int>{});
        return *this;
    }
    std::size_t size() const { return values_.size(); }
    const int* data() const { return values_.data(); }
    int at(std::size_t i) const { return values_.at(i); }
};

class Inbox {
    Payload current_;
public:
    void accept(const Payload& payload) { current_ = payload; }
    void accept(Payload&& payload) { current_ = std::move(payload); }
    const Payload& peek() const { return current_; }
};

template<class T>
void deliver(Inbox& inbox, T&& payload) {
    // bug: always passes as rvalue when it should borrow
    // -> use std::forward instead
    inbox.accept(std::forward<T>(payload));
}

// bug: passing const Payload instead of Payload -> no move constructor accepts const Payload&&
// so it'd route to the copy constructor and create a copy
Payload archive(Payload payload) {
    return std::move(payload);
}

class Inspector {
    const Inbox& inbox_;
public:
    // bug: should store reference to inbox instead of underlying payload
    explicit Inspector(const Inbox& inbox) : inbox_(inbox) {}
    int first() const { return inbox_.peek().at(0); }
};

// Harness: keep existing checks intact.
void check(bool ok, const char* description) {
    std::cout << (ok ? "PASS: " : "FAIL: ") << description << std::endl;
    if (!ok) throw std::runtime_error(description);
}

void test_delivery() {
    Inbox inbox;
    Payload source{11, 12};
    deliver(inbox, source);
    check(inbox.peek().size() == 2 && inbox.peek().at(0) == 11,
          "delivery stores the submitted contents");
    check(source.size() == 2 && source.at(1) == 12,
          "delivery preserves a named input passed without std::move");
    const Payload readonly{21};
    deliver(inbox, readonly);
    check(readonly.at(0) == 21 && inbox.peek().at(0) == 21,
          "delivery accepts const input without changing it");
    Payload outgoing{31, 32};
    const int* address = outgoing.data();
    Payload::copies = 0;
    deliver(inbox, std::move(outgoing));
    check(outgoing.size() == 0 && inbox.peek().data() == address && Payload::copies == 0,
          "explicit transfer retains storage without copying");
    deliver(inbox, Payload{41});
    check(inbox.peek().at(0) == 41, "delivery accepts a temporary");
}

void test_archive() {
    Payload source{51, 52};
    const int* address = source.data();
    Payload::copies = 0;
    Payload saved = archive(std::move(source));
    check(saved.size() == 2 && saved.at(1) == 52 && source.size() == 0,
          "archive preserves contents and consumes explicit input");
    check(Payload::copies == 0 && saved.data() == address,
          "archive transfers existing storage without copying");
    Payload::copies = 0;
    Payload temporary = archive(Payload{61});
    check(temporary.at(0) == 61 && Payload::copies == 0,
          "archive accepts a temporary without copying");
}

void test_inspection() {
    Inbox inbox;
    inbox.accept(Payload{71, 72});
    Inspector inspector(inbox);
    check(inspector.first() == 71, "inspection reads current contents");
    inbox.accept(Payload{81, 82, 83});
    // bug: inspector only sets its first ptr when constructor is called
    // -> should automatically update whenever inbox is updated
    check(inspector.first() == 81, "inspection follows replacement contents");
}

int main(int argc, char** argv) {
    if (argc != 2) { std::cerr << "Choose delivery, archive, or inspection\n"; return 2; }
    try {
        const std::string_view name = argv[1];
        if (name == "delivery") test_delivery();
        else if (name == "archive") test_archive();
        else if (name == "inspection") test_inspection();
        else throw std::invalid_argument("unknown case");
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
