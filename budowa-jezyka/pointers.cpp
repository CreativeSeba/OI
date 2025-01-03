// Dangling Pointer: A pointer that refers to memory that has been freed/deallocated. Accessing such memory leads to undefined behavior.
// Memory Leak: Occurs when dynamically allocated memory is not freed, causing a program to consume more memory over time.
// Null Pointer Exception: Attempting to dereference or use a null pointer (nullptr) causes an error or crash since it doesn't point to a valid memory location.

//A refrence '&' doesnt store memory adress, it just makes us use the same memory adress as the variable we are refering to, so that we dont copy the variable
//A pointer '*' stores the memory adress of the variable we are pointing to, so we can change the variable we are pointing to, we can change the memory adress we are pointing to, we can make the pointer point to nothing (nullptr)

#include <iostream>
using namespace std;

// Function to demonstrate pointers to functions
// This function simply prints the value passed to it.
void printValue(int x) {
    cout << "Value: " << x << endl;
}

// Another function to demonstrate the versatility of pointers to functions
// This function prints the square of the value passed to it.
void printSquare(int x) {
    cout << "Square: " << x * x << endl;
}

// Function that takes a pointer to a function as an argument
void executeFunction(void (*func)(int), int value) {
    cout << "Executing function pointer with value: " << value << endl;
    func(value); // Call the function using the pointer
}

int main() {
    // 1. Declaration and initialization of pointers
    int a = 10;            // A simple integer variable
    int* ptr = &a;         // Pointer stores the address of variable 'a'

    // Display the value and address
    cout << "Value of a: " << a << endl;
    cout << "Address of a (&a): " << &a << endl;
    cout << "Value stored in ptr: " << ptr << endl;
    cout << "Value pointed to by ptr (*ptr): " << *ptr << endl;

    // 2. Pointer arithmetic
    int arr[3] = {1, 2, 3};
    int* arrPtr = arr;  // Pointer to the first element of the array

    cout << "\nArray Pointer Arithmetic:" << endl;
    cout << "Value at arrPtr: " << *arrPtr << endl;
    arrPtr++;  // Move pointer to the next element in the array
    cout << "Value at arrPtr after increment: " << *arrPtr << endl;

    // 3. Null pointer
    int* nullPtr = nullptr; // A pointer that doesn't point to any address
    cout << "\nNull pointer example:" << endl;
    if (nullPtr == nullptr) {
        cout << "nullPtr is null." << endl;
    }

    // 4. Pointer to a function
    // Pointers to functions allow dynamic function calls.
    void (*funcPtr)(int) = printValue; // funcPtr points to printValue function

    cout << "\nPointer to Function Example:" << endl;
    funcPtr(42); // Call the function using the pointer

    // Changing the function the pointer refers to
    funcPtr = printSquare;
    funcPtr(7); // Now funcPtr points to printSquare

    // 5. Using function pointers as arguments
    cout << "\nUsing Function Pointer as Argument:" << endl;
    executeFunction(printValue, 15); // Pass printValue as a function pointer
    executeFunction(printSquare, 4); // Pass printSquare as a function pointer

    return 0;
}
