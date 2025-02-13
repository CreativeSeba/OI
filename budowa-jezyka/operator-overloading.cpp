#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r, double i) : real(r), imag(i) {}

    // Overloading the + operator
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Method to display the complex number
    void display() const {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

class Point {
private:
    int x, y;

public:
    // Constructor
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Overloading the << operator for output
    //We have to use friend, becuase operator functions are non-member functions, so they dont have access to the private members of the class
    friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
        os << "(" << pt.x << ", " << pt.y << ")";
        return os;
    }
};

class MyArray {
private:
    int arr[5];

public:
    // Constructor to initialize the array
    MyArray() {
        for (int i = 0; i < 5; i++) {
            arr[i] = i * 10;  // Initialize with multiples of 10
        }
    }

    // Overloading the [] operator
    int& operator[](int index) {
        return arr[index];
    }
};

class Rectangle {
private:
    int width, height;

public:
    // Constructor
    Rectangle(int w, int h) : width(w), height(h) {}

    // Overloading the == operator to compare two Rectangle objects
    bool operator==(const Rectangle& other) {
        return (width == other.width && height == other.height);
    }
};

// User-defined literal for kg
long double operator"" _kg(long double x) {
    return x * 1000;  // Convert kg to grams
}

int main() {
    //Complex
    Complex num1(3.0, 4.0);
    Complex num2(1.0, 2.0);
    Complex result = num1 + num2;  // Using overloaded + operator

    result.display();  // Output: 4.0 + 6.0i

    //Point
    Point p(3, 4);
    std::cout << p << std::endl;  // Output: (3, 4)

    //MyArray
    MyArray arr;
    std::cout << "Element at index 2: " << arr[2] << std::endl;  // Output: 20

    arr[2] = 100;  // Modify element at index 2
    std::cout << "Modified element at index 2: " << arr[2] << std::endl;  // Output: 100

    //Rectangle
    Rectangle r1(10, 5);
    Rectangle r2(10, 5);
    Rectangle r3(20, 15);

    std::cout << "r1 == r2: " << (r1 == r2 ? "True" : "False") << std::endl;  // Output: True
    std::cout << "r1 == r3: " << (r1 == r3 ? "True" : "False") << std::endl;  // Output: False

    //User-defined literal
    auto weight = 5.0_kg;  // 5 kg becomes 5000 grams
    std::cout << "Weight in grams: " << weight << std::endl;
    return 0;
}
