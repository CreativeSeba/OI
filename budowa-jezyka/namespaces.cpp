#include <iostream>

// Regular Namespace
namespace MyNamespace {
    int value = 42;

    void display() {
        std::cout << "Value from MyNamespace: " << value << std::endl;
    }
}

// Anonymous Namespace (file-scoped)
namespace {
    int secretValue = 100;

    void displaySecret() {
        std::cout << "Secret Value (Anonymous Namespace): " << secretValue << std::endl;
    }
}

// Nested Namespaces
namespace Outer {
    namespace Inner {
        void display() {
            std::cout << "Inside the Inner namespace" << std::endl;
        }
    }
}

// Namespace Alias
namespace LongNamespaceName = MyNamespace;

int main() {
    // Regular namespace usage
    MyNamespace::display();  // Output: Value from MyNamespace: 42

    // Anonymous namespace usage (restricted to this file)
    displaySecret();  // Output: Secret Value (Anonymous Namespace): 100

    // Nested namespaces usage
    Outer::Inner::display();  // Output: Inside the Inner namespace

    // Using the namespace alias
    LongNamespaceName::display();  // Output: Value from MyNamespace: 42

    return 0;
}
