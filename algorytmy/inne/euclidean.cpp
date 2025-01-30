//GCD - greatest common divisor
//LCM - least common multiple
#include <iostream>

using namespace std;

// Function to find GCD using Euclidean algorithm
int gcd(int a, int b) {
    // Base case: if b becomes 0, return a
    while (b != 0) {
        //gcd(a, b) = gcd(b, a % b)
        int temp = b;
        b = a % b; // Remainder of a divided by b
        a = temp;
    }
    return a;
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int num1, num2;
    cin >> num1 >> num2;
    cout << "The GCD of " << num1 << " and " << num2 << " is " << gcd(num1, num2) << endl;
    cout << "The LCM of " << num1 << " and " << num2 << " is " << lcm(num1, num2) << endl;
    return 0;
}
