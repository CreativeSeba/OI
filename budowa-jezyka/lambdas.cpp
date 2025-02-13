#include <iostream>
#include <vector>
#include <algorithm>

// 1. Simple Lambda
void simple_lambda() {
    auto greet = []() { std::cout << "Hello, World!" << std::endl; };
    greet();  // Calls the lambda function
}

// 2. Lambda with parameters
void lambda_with_parameters() {
    auto add = [](int a, int b) { return a + b; };
    int result = add(3, 5);
    std::cout << "3 + 5 = " << result << std::endl;
}

// 3. Lambda with captured variables
void lambda_with_capture() {
    int x = 5, y = 10;
    auto sum = [x, y]() { return x + y; };  // Captures x and y by value
    std::cout << "Sum of x and y: " << sum() << std::endl;
}

// 4. Lambda with reference capture
void lambda_with_reference_capture() {
    int a = 2, b = 4;
    auto modify = [&a, &b]() { a *= 2; b += 3; };  // Captures a and b by reference
    modify();
    std::cout << "Modified a: " << a << ", Modified b: " << b << std::endl;
}

// 5. Lambda with return type
void lambda_with_return_type() {
    auto multiply = [](int a, int b) -> int { return a * b; };
    int result = multiply(4, 6);
    std::cout << "4 * 6 = " << result << std::endl;
}

// 6. Lambda used with standard algorithms
void lambda_with_algorithms() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto is_even = [](int num) { return num % 2 == 0; };

    std::cout << "Even numbers: ";
    for (int num : nums) {
        if (is_even(num)) {
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
}

// 7. Using a Lambda as a Function Pointer Argument
void process_numbers(const std::vector<int>& nums, int (*func)(int)) {
    for (int num : nums) {
        std::cout << func(num) << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "1. Simple Lambda:" << std::endl;
    simple_lambda();

    std::cout << "\n2. Lambda with Parameters:" << std::endl;
    lambda_with_parameters();

    std::cout << "\n3. Lambda with Captured Variables:" << std::endl;
    lambda_with_capture();

    std::cout << "\n4. Lambda with Reference Capture:" << std::endl;
    lambda_with_reference_capture();

    std::cout << "\n5. Lambda with Return Type:" << std::endl;
    lambda_with_return_type();

    std::cout << "\n6. Lambda with Standard Algorithms:" << std::endl;
    lambda_with_algorithms();

    std::cout << "\n7. Using a Lambda as a Function Pointer Argument:" << std::endl;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    // Passing a lambda as a function pointer to process_numbers
    process_numbers(nums, [](int x) { return x * x; });  // Squares each number

    return 0;
}
