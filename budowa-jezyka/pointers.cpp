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

// Function to demonstrate pointers to pointers (dynamic 2D array)
void demoPointerToPointer() {
    // Creating a dynamic 2D array using pointers to pointers
    int rows = 3, cols = 3;

    // Dynamically allocating memory for rows (array of pointers)
    int** arr = new int*[rows];

    // Dynamically allocating memory for columns in each row
    for (int i = 0; i < rows; i++) {
        //dereferencing arr[i] to allocate memory for column for each pointer in the array
        arr[i] = new int[cols];
    }

    // Initializing the 2D array with values
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = value++;
        }
    }

    // Printing the 2D array
    cout << "\n2D Array (3x3) using Pointer to Pointer:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocating the memory
    for (int i = 0; i < rows; i++) {
        delete[] arr[i]; // Deallocate each row
    }
    delete[] arr; // Deallocate the array of pointers
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
    // Adress of the function is the same thing as varaible adress
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

    // 6. Demonstrating Pointer to Pointer (Dynamic 2D Array)
    demoPointerToPointer();

    return 0;
}
