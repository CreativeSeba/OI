#include <iostream>
#include <cstdarg>  // For variadic functions

// C-style variadic function to calculate the sum of numbers
int sum(int count, ...) {
    int total = 0;

    va_list args;
    va_start(args, count);  // Initialize args to retrieve additional arguments

    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);  // Retrieve the next argument as an int
    }

    va_end(args);  // Clean up

    return total;
}
// Variadic template function to calculate the sum of numbers
template <typename... Args>
int sum2(Args... args) {
    return (args + ...);  // Fold expression (C++17 feature) to sum all arguments
}

int main() {
    std::cout << "Sum of 3 numbers: " << sum(3, 1, 2, 3) << std::endl;
    std::cout << "Sum of 5 numbers: " << sum2(5, 1, 2, 3, 4, 5) << std::endl;

    return 0;
}
