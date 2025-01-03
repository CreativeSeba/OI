#include <bits/stdc++.h>

using namespace std;

class BigInt {
private:
    vector<uint32_t> digits; // Each element stores a part of the number, it is 32 bit, because we are adding 32 bit numbers, and we cant add 64 bit numbers, because it would exceed the limit
    static const uint64_t BASE = 1000000000; // Base 10^9, used for arithmetic operations
    static const int BASE_DIGITS = 9; // Number of digits in the base, used for string formatting

    // Helper function to remove leading zeros
    void trim() {
        while (!digits.empty() && digits.back() == 0)
            digits.pop_back();
    }

public:
    // Constructors
    BigInt() : digits(1, 0) {} //Initialize digits vector with zero
    BigInt(uint64_t value) { *this = value; } //Dereference 'this' pointer and assign value using overloaded operator for uint64_t
    BigInt(const string &str) { *this = str; } //Dereference 'this' pointer and assign value using overloaded operator for string

    // Assignment operators
    BigInt &operator=(uint64_t value) {//BigInt & returns a reference to the object, not a copy
        /*BigInt num1("12345678901234567890"); // Initialize with a large number
        num1 = 42;                          // Assign a new value*/
        // When we override the same BigInt, we need to clear the digits vector, to not have multiple BigInt's in the vector
        digits.clear();
        /*value = 1234567890134567890
        value % BASE = 134567890 → Extract the least significant 9 digits.
        digits.push_back(34567890).
        value /= BASE = 1234567890 → Remove the extracted digits.*/
        do {//do-while loop is used to execute at least once
            digits.push_back(value % BASE);
            value /= BASE;
        } while (value > 0);
        return *this;
    }

    BigInt &operator=(const string &str) { //Passed by reference, because strings are large and const, because we don't want to change the value of the string
        digits.clear();
        int len = str.length();
        for (int i = len; i > 0; i -= BASE_DIGITS) {
            int end = i;
            int start = max(0, i - BASE_DIGITS); //max is used to avoid negative values
            digits.push_back(stoul(str.substr(start, end - start))); //stoul converts string to unsigned long and pushes the substring to the digits vector
        }
        trim();//Remove leading zeros

        return *this;
    }

    //We dont return by refrence in the following functions, because we are returning a new BigInt object

    // Addition operator
    BigInt operator+(const BigInt &other) const {
        BigInt result;
        result.digits.clear(); // here it isnt necessary to clear the vector, because we are creating a new BigInt object, but it is good practice
        uint64_t carry = 0;
        size_t maxSize = max(digits.size(), other.digits.size()); //Get the maximum size of the two BigInts, to iterate through all the digits
        //maxSize isnt a size of a variable, it is number of 32 bit chunks
        for (size_t i = 0; i < maxSize || carry; ++i) { //it checks if i exceeds maxSize, or if carry is bigger than 0
            //Jak dodawanie pod kreska, tylko 'pojedynacza cyfra' to 32 bitowa liczba, a reszta to 64 bitowa, ale dziala to tak samo, tylko nie na pojedynczych cyfrach
            uint64_t sum = carry;
            //these if statements are used to check if we are not exceeding the size of the vector
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits.push_back(sum % BASE); //32 bitowa czesc liczby bez reszty z dodawania
            carry = sum / BASE; // reszta z dodawania
        }
        return result;
    }

    // Subtraction operator
    BigInt operator-(const BigInt &other) const {
        if (*this < other) throw underflow_error("Negative result in unsigned BigInt subtraction");
        BigInt result;
        result.digits.clear();
        int64_t carry = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int64_t diff = digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0);
            carry = (diff < 0);
            if (carry) diff += BASE;
            result.digits.push_back(diff);
        }
        result.trim();
        return result;
    }

    // Multiplication operator
    BigInt operator*(const BigInt &other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size());
        for (size_t i = 0; i < digits.size(); ++i) {
            uint64_t carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                uint64_t prod = result.digits[i + j] + digits[i] * 1ULL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = prod % BASE;
                carry = prod / BASE;
            }
        }
        result.trim();
        return result;
    }

    // Division operator (integer division)
    BigInt operator/(const BigInt &other) const {
        if (other == 0) throw overflow_error("Division by zero");
        BigInt result, current;
        result.digits.resize(digits.size());
        for (int i = digits.size() - 1; i >= 0; --i) {
            current = current * BASE + digits[i];
            uint64_t x = 0, left = 0, right = BASE;
            while (left <= right) {
                uint64_t mid = (left + right) / 2;
                if (other * mid <= current) {
                    x = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            result.digits[i] = x;
            current = current - other * x;
        }
        result.trim();
        return result;
    }

    // Comparison operators
    bool operator<(const BigInt &other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator<=(const BigInt &other) const {
        return (*this < other) || (*this == other);
    }

    bool operator==(const BigInt &other) const {
        return digits == other.digits;
    }

    // Stream output operator
    friend ostream &operator<<(ostream &out, const BigInt &value) {
        if (value.digits.empty()) {
            out << 0;
            return out;
        }
        out << value.digits.back();
        for (int i = value.digits.size() - 2; i >= 0; --i) {
            out << setw(BASE_DIGITS) << setfill('0') << value.digits[i];
        }
        return out;
    }
};

int main() {
    BigInt num1("190000000000000000000000");
    BigInt num2("190000000000000000000000");

    BigInt sum = num1 + num2;
    BigInt diff = num1 - num2;
    BigInt prod = num1 * num2;
    BigInt quot = num1 / num2;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    return 0;
}
/*
Time Complexity Analysis for BigInt Class:

1. Addition (operator+):
   Time Complexity: O(n)
   - Iterates through the digits of both numbers, adding corresponding blocks with carry propagation.

2. Subtraction (operator-):
   Time Complexity: O(n)
   - Iterates through the digits of the two numbers, subtracting corresponding blocks with borrow propagation.

3. Multiplication (operator*):
   Time Complexity: O(n^2)
   - Implements long multiplication, iterating through each block of the first number and multiplying it with all blocks of the second.

4. Division (operator/):
   Time Complexity: O(n^2)
   - Performs repeated subtraction (scaled by binary search for the quotient), which involves O(n) operations for each of the n blocks.

5. Comparison (operator<, operator<=, operator==):
   Time Complexity: O(n)
   - Compares the numbers by iterating through their blocks from the most significant to the least significant.

6. Input/Output:
   Time Complexity: O(n)
   - Reading from or writing to a string involves processing each block/digit exactly once.

Overall Notes:
- Here, `n` represents the number of blocks (or digits in base 10^9) in the larger of the two numbers being operated upon.
- Multiplication and division are the most computationally expensive operations, with O(n^2) complexity in the current implementation.
- Optimized algorithms like FFT multiplication (O(n log n)) or Newton-Raphson division (O(n log^2 n)) can significantly reduce complexity for large inputs.
*/
