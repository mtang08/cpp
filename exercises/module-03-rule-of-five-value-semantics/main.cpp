#include <cstddef>
#include <stdexcept>
#include <iostream>

class DynamicArray {
private:
    std::size_t capacity_;
    std::size_t size_;
    int* data_;
public:
    DynamicArray(std::size_t initial_capacity);
    ~DynamicArray();
    DynamicArray(const DynamicArray& da);
    DynamicArray& operator=(const DynamicArray& da);
    DynamicArray(DynamicArray&& da) noexcept;
    DynamicArray& operator=(DynamicArray&& da) noexcept;
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
    void push_back(int value);
    int& operator[](std::size_t index);
    const int& operator[](std::size_t index) const;
    int& at(std::size_t index);
    const int& at(std::size_t index) const;
};

DynamicArray::DynamicArray(std::size_t initial_capacity) : capacity_{initial_capacity}, size_{0} {
    if (!initial_capacity) {
        data_ = nullptr;
        return;
    }
    data_ = new int[initial_capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data_;
    data_ = nullptr;
}

DynamicArray::DynamicArray(const DynamicArray& da) {
    capacity_ = da.capacity_;
    size_ = da.size_;
    data_ = nullptr;
    if (da.capacity_) {
        data_ = new int[capacity_];
    }
    // I think there may be an optimization using memcpy possible here
    for (std::size_t i = 0; i < size_; ++i) {
        // mistake: accessed da[i] instead of da.data_[i]; functionally the same, but better to access private directly in this case
        data_[i] = da.data_[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& da) {
    // should I be comparing data_ to da.data_ or this to &da?
    // ANSWER: compare this to &da
    if (this == &da) {
        return *this;
    }
    int* new_data = nullptr;
    if (da.capacity_) {
        new_data = new int[da.capacity_];
    }
    // need to check if we are overwriting existing dynamic array
    // mistake: we'd delete if argument is same as *this
    // mistake: the func continues on after not deleting, leak mem when the arg is equal to this
    delete[] data_;
    // mistake: used to directly assign data_ = new int[]; if allocation throws, left with dangling pointer
    // same issue with assigning capacity and size early
    // mistake: now that I moved the size assignment later, cannot use it as index var here
    for (std::size_t i = 0; i < da.size_; ++i) {
        // mistake: accessed da[i] instead of da.data_[i]
        new_data[i] = da.data_[i];
    }
    data_ = new_data;
    size_ = da.size_;
    capacity_ = da.capacity_;
    return *this;
}

DynamicArray::DynamicArray(DynamicArray&& da) noexcept {
    capacity_ = da.capacity_;
    da.capacity_ = 0;
    size_ = da.size_;
    da.size_ = 0;
    data_ = da.data_;
    da.data_ = nullptr;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& da) noexcept {
    if (this == &da) {
        return *this;
    }
    // deleting nullptr is no-op so might not be needed--what's best practice here?
    // do not need the if check
    delete[] data_;
    capacity_ = da.capacity_;
    da.capacity_ = 0;
    size_ = da.size_;
    da.size_ = 0;
    data_ = da.data_;
    da.data_ = nullptr;

    return *this;
}

std::size_t DynamicArray::size() const {
    return size_;
}

std::size_t DynamicArray::capacity() const {
    return capacity_;
}

bool DynamicArray::empty() const {
    return size_ == 0;
}

void DynamicArray::push_back(int value) {
    // mistake: array with capacity 0 could not grow
    if (capacity_ == 0) {
        ++capacity_;
        data_ = new int[capacity_];
    } else if (size_ == capacity_) {
        // could we use move constructor here?
        std::size_t new_capacity = capacity_ * 2;
        int* new_data = new int[new_capacity];
        // mistake: copied capacity elements when only size elements should be copied
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        capacity_ = new_capacity;
        data_ = new_data;
    }

    data_[size_++] = value;
}

int& DynamicArray::operator[](std::size_t index) {
    return data_[index];
}

// why do we need the above in addition to this one? this is read-only, above enables write?
const int& DynamicArray::operator[](std::size_t index) const {
    return data_[index];
}

int& DynamicArray::at(std::size_t index) {
    // mistake: std::size_t is unsigned so cannot be negative
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }

    return data_[index];
}
const int& DynamicArray::at(std::size_t index) const {
   if (index >= size_) {
        throw std::out_of_range("invalid index");
    }

    return data_[index]; 
}

int main() {
    std::cout << "Testing empty creation and push\n";
    DynamicArray initially_empty(0);
    initially_empty.push_back(67);
    std::cout << initially_empty.at(0) << "\n";


    std::cout << "\nTesting small array creation, expansion, subscript, and at\n";
    DynamicArray small_array(1); // construct small array
    small_array.push_back(1); // append within capacity
    small_array.push_back(2); // append past capacity
    std::cout << small_array.capacity() << "\n";
    int valid_subscript = small_array[0];
    std::cout << valid_subscript << "\n";
    int valid_at = small_array.at(1);
    std::cout << valid_at << "\n";

    std::cout << "\nTesting throw std::out_of_range\n";
    try {
        int invalid = small_array.at(10);
        std::cout << invalid << "\n";
        // convention: catch std::out_of_range by const reference to avoid copying exception object
    } catch(const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "\nTesting copy constructor and assignment operator\n";
    DynamicArray copy_small(small_array);
    copy_small[0] = 8;
    if (copy_small[0] != small_array[0]) {
        std::cout << copy_small[0] << " " << small_array[0] << "\n";
    }

    // DynamicArray copy_ass = small_array; -> this is still copy constructor technically
    DynamicArray copy_ass(0);
    copy_ass = small_array;
    copy_ass[1] = 10;
    std::cout << copy_ass.size() << "\n";
    std::cout << copy_ass[0] << " " << copy_ass[1] << "\n";
    if (copy_ass[1] != small_array[1]) {
        std::cout << copy_ass[1] << " " << small_array[1] << "\n";
    }

    DynamicArray source_empty(0);
    DynamicArray target_nonempty(2);
    target_nonempty.push_back(1);
    target_nonempty = source_empty;
    target_nonempty.push_back(99);
    std::cout << target_nonempty.at(0) << "\n";

    std::cout << "\nTesting move\n";
    DynamicArray move_small(std::move(small_array));
    std::cout << small_array.size() << "\n";
    std::cout << small_array.capacity() << "\n";
    std::cout << small_array.empty() << "\n";


    // DynamicArray move_ass = std::move(copy_small); -> this is still move constructor technically because move_ass does not exist before this line
    DynamicArray move_ass(0);
    move_ass = std::move(copy_small);
    std::cout << copy_small.size() << "\n";
    std::cout << copy_small.capacity() << "\n";
    std::cout << copy_small.empty() << "\n";

    std::cout << "\nTesting self-copy and self-move\n";
    DynamicArray copy_self(10);
    // copy_self[5] = 5; -> technically invalid because size_ = 0
    copy_self.push_back(5);
    copy_self = copy_self;
    std::cout << copy_self.at(0) << "\n";

    DynamicArray move_self(8);
    // move_self[6] = 7; -> technically invalid because size_ = 0
    move_self.push_back(7);
    move_self = std::move(move_self);
    std::cout << move_self.at(0) << "\n";

    return 0;
}