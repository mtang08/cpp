#include <cstddef>
#include <iostream>
#include <stdexcept>

class IntBuffer {
public:
    // advantageous to use class member initializer list to construct members directly
    // necessary for class-type members, references, const members
    // new int[sz]{} initializes array elements to zero
    IntBuffer(std::size_t sz) : data_(new int[sz]{}), size_(sz) {}
    // disable use of copy constructor and copy assignment operator
    // to prevent double-free issues
    IntBuffer(const IntBuffer&) = delete;
    IntBuffer& operator=(const IntBuffer&) = delete;
    ~IntBuffer() {
        delete[] data_;
    }
    // method marked const because it does not modify the IntBuffer
    std::size_t size() const {
        return size_;
    }

    int get(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    void set(std::size_t index, int value) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        data_[index] = value;
    }


private:
    int* data_;
    std::size_t size_;
};

int main() {
    std::cout << "Module 2 RAII buffer exercise\n";
    IntBuffer buffer(10);
    buffer.set(3, 5);
    buffer.set(8, 8);
    buffer.set(6, 7);
    for (std::size_t i = 0; i < 10; ++i) {
        std::cout << buffer.get(i) << " ";
    }
    std::cout << "\n";
    return 0;
}
