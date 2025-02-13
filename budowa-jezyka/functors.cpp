#include <iostream>
#include <vector>
#include <algorithm>

//Functors are objects that can be treated as functions or function pointers.
// A simple functor that adds a given value to the member variable 'value'
class Adder {
public:
    Adder(int val) : value(val) {}
    int operator()(int num) const {
        return num + value;
    }

private:
    int value;
};

// A functor that checks if a number is even
class IsEven {
public:
    bool operator()(int num) const {
        return num % 2 == 0;
    }
};

// A functor that multiplies a number by a fixed factor
class Multiplier {
public:
    Multiplier(int factor) : factor(factor) {}
    int operator()(int num) const {
        return num * factor;
    }

private:
    int factor;
};

int main() {
    // Create instances of functors
    Adder add5(5);
    IsEven isEven;
    Multiplier multiply3(3);

    // Using the 'Adder' functor
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Adding 5 to each number: ";
    for (int num : nums) {
        std::cout << add5(num) << " "; // Calls operator() of Adder
    }
    std::cout << std::endl;

    // Using 'IsEven' functor with algorithm
    std::cout << "Even numbers: ";
    for (int num : nums) {
        if (isEven(num)) { // Calls operator() of IsEven
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;

    // Using 'Multiplier' functor
    std::cout << "Multiplying each number by 3: ";
    for (int num : nums) {
        std::cout << multiply3(num) << " "; // Calls operator() of Multiplier
    }
    std::cout << std::endl;

    return 0;
}
