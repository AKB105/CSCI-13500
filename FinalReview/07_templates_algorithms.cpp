/*
    Week 8 Review: Templates and Algorithms

    Good cheat-sheet ideas:
    - Templates let one function/class work with different types.
    - Template definitions usually stay in header files in real multi-file projects.
    - Generic helpers can reduce repeated code for search, min/max, and validation.
*/

#include <iostream>
#include <string>

template <typename T, typename U, typename V>
T AddThreeNumbers(T a, U b, V c) {
    return a + b + c;
}

template <typename T>
bool ContainsValue(const T values[], int size, const T& target) {
    for (int i = 0; i < size; i++) {
        if (values[i] == target) {
            return true;
        }
    }
    return false;
}

template <typename T>
class Box {
public:
    Box(const T& starting_value) {
        value_ = starting_value;
    }

    T GetValue() const {
        return value_;
    }

    void SetValue(const T& new_value) {
        value_ = new_value;
    }

private:
    T value_;
};

int main() {
    std::cout << AddThreeNumbers(6.32, 9, 7.5f) << "\n";

    const int numbers[5] = {3, 6, 9, 12, 15};
    const std::string moves[3] = {"rock", "paper", "scissors"};

    std::cout << std::boolalpha;
    std::cout << ContainsValue(numbers, 5, 9) << "\n";
    std::cout << ContainsValue(moves, 3, std::string("paper")) << "\n";

    Box<std::string> saved_file("puzzle01.txt");
    saved_file.SetValue("puzzle02.txt");
    std::cout << saved_file.GetValue() << "\n";

    return 0;
}
