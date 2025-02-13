#include <iostream>

// 1. Simple constant definition
#define PI 3.14159

// 2. Macro for calculating the area of a circle
#define AREA_OF_CIRCLE(radius) (PI * (radius) * (radius))

// 3. Macro to print a message
#define PRINT(msg) std::cout << msg << std::endl;

// 4. Conditional compilation: Debug mode
// It doesn perform any operation, it isnt programmed here to do anything
#define DEBUG_MODE

int main() {
    // 1. Simple constant usage
    std::cout << "Value of PI: " << PI << std::endl;

    // 2. Using a function-like macro
    double radius = 5.0;
    double area = AREA_OF_CIRCLE(radius);
    std::cout << "Area of circle with radius " << radius << ": " << area << std::endl;

    // 3. Using the print macro
    PRINT("Hello from macro!")

    // 4. Conditional compilation (debug mode)
    // Check if the DEBUG_MODE macro is defined
    #ifdef DEBUG_MODE
        std::cout << "Debug mode is ON!" << std::endl;
#else
    std::cout << "Debug mode is OFF!" << std::endl;
#endif

    return 0;
}
