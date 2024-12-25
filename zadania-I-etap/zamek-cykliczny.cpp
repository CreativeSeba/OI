//https://szkopul.edu.pl/problemset/problem/mLyF3KRZMSxwdnrKhXMOjUFJ/site/?key=statement
#include <iostream>
#include <string>

using namespace std;

// Funkcja do liczenia ilości zer i dziewiątek w liczbie reprezentowanej jako string
int countZerosAndNines(const string& number) {
    int count = 0;

    for (char digit : number) {
        if (digit == '0' || digit == '9') {
            count++;
        }
    }

    return count;
}

// Funkcja do usuwania wiodących zer z liczby reprezentowanej jako string
string removeLeadingZeros(const string& number) {
    const size_t firstNonZero = number.find_first_not_of('0');
    return (firstNonZero != string::npos) ? number.substr(firstNonZero) : "0";
}

// Funkcja do obracania cyfr liczby reprezentowanej jako string
string rotateDigits(const string& number) {
    if (number.length() <= 1) return number;

    const string rotated = number.substr(1) + number[0];

    return removeLeadingZeros(rotated);
}

// Funkcja do dodawania 1 do liczby reprezentowanej jako string
string incrementByOne(const string& number) {
    string result = number;
    int carry = 1;

    for (int i = result.length() - 1; i >= 0 && carry; --i) {
        if (result[i] == '9') {
            result[i] = '0';
        } else {
            result[i]++;
            carry = 0;
        }
    }

    if (carry) result = '1' + result; // Przeniesienie z lewej strony

    return result;
}

// Funkcja do określenia minimalnej liczby naciśnięć przycisków, aby osiągnąć 1
long long calculateMinButtonPresses(const string& number) {
    string currentNumber = number;
    currentNumber = removeLeadingZeros(number);
    if (number == "1") return 0;

    long long presses = 0;

    while (currentNumber != "1") {
        presses++;

        // Jeśli wszystkie cyfry to 9, dodaj 1, ponieważ nie ma sensu obracać cyfr, a dodanie 1 doprowadzi nas bliżej 1
        bool allNines = true;
        for (const char digit : currentNumber) {
            if (digit != '9') {
                allNines = false;
                break;
            }
        }

        if (allNines) {
            currentNumber = incrementByOne(currentNumber);
            continue;
        }

        // Jeżeli ostatnia cyfra to 9 lub 0, obróć cyfry, ponieważ dążymy do doprowadzenia do sytuacji, w której
        // wszystkie cyfry to 9, by móc dodać 1, obrócić i w ten sposób otrzymać 1.
        // Jeśli ostatnia cyfra nie jest 0 ani 9, dodaj 1, ponieważ dążymy wtedy do otrzymania 9 na końcu.
        const char lastDigit = currentNumber.back();
        if (lastDigit == '9' || lastDigit == '0') {
            currentNumber = rotateDigits(currentNumber);
        } else {
            currentNumber = incrementByOne(currentNumber);
        }
    }

    return presses;
}

int main() {
    string number;
    cin >> number;

    cout << calculateMinButtonPresses(number) << endl;

    return 0;
}
