#include <iostream>
using namespace std;

// Generic class template
template <typename T>
class Container {
public:
    T value;
    Container(T v) : value(v) {}

    void print() {
        cout << "Generic Container: " << value << endl;
    }
};

// Template specialization for int type
template <>
class Container<int> {
public:
    int value;
    Container(int v) : value(v) {}

    void print() {
        cout << "Specialized Container for int: " << value << endl;
    }
};

// Function template that works with the Container class
template <typename T>
void displayContainer(Container<T>& container) {
    container.print();
}

// Template specialization for the Container<int> type
template <>
void displayContainer<int>(Container<int>& container) {
    cout << "Displaying an int-specific container: ";
    container.print();
}

int main() {
    // Using the generic class template
    Container<double> doubleContainer(3.14);
    displayContainer(doubleContainer);  // Calls the generic function

    // Using the specialized class template for int
    Container<int> intContainer(42);
    displayContainer(intContainer);  // Calls the specialized function

    return 0;
}
