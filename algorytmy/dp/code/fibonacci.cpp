#include <iostream>

using namespace std;

// Function to compute Fibonacci using space optimization
int fibonacci(int n) {
    if (n <= 1) return n;

    // Use two variables to store the last two Fibonacci numbers
    int prev2 = 0; // Represents F(n-2)
    int prev1 = 1; // Represents F(n-1)
    int curr = 0;

    // Compute Fibonacci iteratively
    for (int i = 2; i <= n; i++) {
        curr = prev1 + prev2; // Current Fibonacci number
        prev2 = prev1;        // Update F(n-2) to F(n-1)
        prev1 = curr;         // Update F(n-1) to F(n)
    }

    return curr;
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;

    return 0;
}
