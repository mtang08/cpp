#include <cstddef>
#include <iostream>

int* make_scores(std::size_t count) {
    if (count < 5) {
        return nullptr;
    }

    int* scores = new int[count]{};

    for (std::size_t i = 0; i < count; ++i) {
        scores[i] = static_cast<int>(i * 10);
    }

    return scores;
}

int main() {
    int* scores = make_scores(6);

    if (scores == nullptr) {
        std::cout << "not enough scores\n";
        return 0;
    }

    std::cout << scores[0] << "\n";
    delete[] scores;
    scores = nullptr;
    delete[] scores;
    return 0;
}
