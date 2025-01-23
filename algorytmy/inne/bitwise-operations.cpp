#include <iostream>
using namespace std;

int main() {
    int a = 5;  // Binary: 0101
    int b = 3;  // Binary: 0011

    // Logic Gates:

    // AND (a ∧ b) using bitwise AND (&)
    int and_result = a & b;  // Bitwise AND operation
    cout << "a AND b = " << and_result << " (Bitwise AND: " << a << " & " << b << ")" << endl;

    // OR (a ∨ b) using bitwise OR (|)
    int or_result = a | b;   // Bitwise OR operation
    cout << "a OR b = " << or_result << " (Bitwise OR: " << a << " | " << b << ")" << endl;

    // XOR (a ⊕ b) using bitwise XOR (^)
    int xor_result = a ^ b;  // Bitwise XOR operation
    cout << "a XOR b = " << xor_result << " (Bitwise XOR: " << a << " ^ " << b << ")" << endl;

    // NOT (¬a) using bitwise NOT (~)
    int not_result = ~a;     // Bitwise NOT operation
    cout << "NOT a = " << not_result << " (Bitwise NOT: ~" << a << ")" << endl;

    // NAND (¬(a ∧ b)) => !(a & b)
    int nand_result = ~(a & b); // NAND = NOT(AND), which is ~(a & b)
    cout << "a NAND b = " << nand_result << " (Bitwise NAND: ~(" << a << " & " << b << "))" << endl;

    // NOR (¬(a ∨ b)) => !(a | b)
    int nor_result = ~(a | b);  // NOR = NOT(OR), which is ~(a | b)
    cout << "a NOR b = " << nor_result << " (Bitwise NOR: ~(" << a << " | " << b << "))" << endl;

    // XNOR (¬(a ⊕ b)) => !(a ^ b)
    int xnor_result = ~(a ^ b); // XNOR = NOT(XOR), which is ~(a ^ b)
    cout << "a XNOR b = " << xnor_result << " (Bitwise XNOR: ~(" << a << " ^ " << b << "))" << endl;

    // Now for binary shifts:

    // Left Shift (a << 1)
    int left_shift_result = a << 1;  // Binary: 1010, which is 10
    cout << "a << 1 = " << left_shift_result << " (Left Shift: " << a << " << 1)" << endl;

    // Right Shift (a >> 1)
    int right_shift_result = a >> 1; // Binary: 0010, which is 2
    cout << "a >> 1 = " << right_shift_result << " (Right Shift: " << a << " >> 1)" << endl;

    return 0;
}
