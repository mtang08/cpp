#include <iostream>
#include <string>
#include <vector>
#include <memory> // std::unique_ptr

// large, read-only string
void f(const std::string& s) {
    for (char c : s) {
        std::cout << c;
    }
    std::cout << "\n";
}

// mutates a caller-provided vector
void g(std::vector<int>& v) {
    for (int& i : v) {
        i = 8;
    }
}

// ownership transfer; unique_ptrs must be passed via std::move
void h(std::unique_ptr<int> p) {
    if (p) {
        *p = 67;
    }
}

void observe(const int* p) {
    if (p) {
        std::cout << *p << "\n";
    } else {
        std::cout << "NO OBJECT PRESENT" << "\n";
    }
}


int main() {
    std::vector<int> v(10);
    g(v);

    std::string s = "Hello, world!";
    f(s);

    int not_six_seven = 14;
    std::unique_ptr<int> p = std::make_unique<int>(not_six_seven);
    // h takes ownership of the unique_ptr
    h(std::move(p));
    // p is empty after ownership was moved
    std::cout << p << "\n"; 

    int ten = 10;
    const int* ptr = &ten;
    observe(ptr);

    observe(nullptr);
    return 0;
}
