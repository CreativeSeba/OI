    #include <bits/stdc++.h>

    using namespace std;

    class BigInt {
    private:
        //we store digits in reverse order, because we dont have to iterate throught the vector from the end
        vector<uint32_t> digits; // Each element stores a part of the number, it is 32 bit, because we are adding 32 bit numbers, and we cant add 64 bit numbers, because it would exceed the limit
        static const uint32_t BASE = 1000000000; // Base 10^9, used for arithmetic operations
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
        BigInt operator+(const BigInt &other) const { //const means that the function does not modify the object
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
            if (*this < other) throw underflow_error("Negative result in unsigned BigInt subtraction"); //An underflow error occurs when an operation produces a result smaller than what can be represented by the data type being used
            BigInt result;
            result.digits.clear();
            //carry is either 0 or 1, because we can borrow only once
            //we try to use the same types in the calculations to avoid overflows and promote the types
            int64_t carry = 0;//Underflow behavior occurs due to how small integer types (like bool or int32_t) are promoted to larger types and how their results are interpreted in the operation, they are promoted to 32bit types and compiler tries to fit them into a 64bit, thus creating an underflow
            //Using int64_t prevents the underflow, because it allows for proper representation of the type of numbers, allows for proper promotion of the types
            for (size_t i = 0; i < digits.size(); ++i) {
                //we use int64 and not uint64, because we can get negative numbers, after subtraction and we need it to check if we need to borrow, and we dont use 32 bit int because we can borrow
                int64_t diff = digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0); //odejmujemy carry, bo to jest to co porzyczylismy, jesli mamy liczbe 123456, to zaluzmy ze w tablicy jest [456, 123], jesli porzyczylismy od 123 to, to zostanie 123-1 , czyli 122
                //(i < other.digits.size() ? other.digits[i] : 0) sprawdza czy mozna odjac, jesli nasza liczba jest wieksza niz liczba od ktorej chcemy odjac, tzn wyszla poza zakres, to odejmujemy zero, bo nie ma co odjac
                carry = (diff < 0);
                if (carry) diff += BASE; // jesli musimy pozyczyc, to dodajemy do obecnej liczby 10^9, czyli 1
                result.digits.push_back(diff); //dodajemy do wyniku
            }
            result.trim(); //musi byc bo jesli w tablicy jest [0, 1] i [200000], to porzyczamy to jeden i zostaje zero z przodu
            return result;
        }

        // Multiplication operator
        BigInt operator*(const BigInt &other) const {
            BigInt result;
            result.digits.resize(digits.size() + other.digits.size()); //Without resizing, result.digits will initially be empty, and trying to access result.digits[i + j] will attempt to write to an invalid memory location. This will cause either a crash or unexpected behavior.
            for (size_t i = 0; i < digits.size(); ++i) {
                uint64_t carry = 0;
                for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                    //result.digits[i + j] to bierze pod uwage poprzednie wyniki mnozenia, ale bez tych ktor byly przed dodaniem 'zera' na koncu, bo jak i sie zwieksza to 'dodajemy' na koncu zero, mnozenie pod kreska
                    //(j < other.digits.size() ? other.digits[j] : 0) to sprawdza czy j juz wyszedl poza zakres, jesli tak to petla patrzy czy carry jest wieksze od zera, jesli jest to wykonywana jest ta operacja i zapomniane carry jest dodane do ostatniego bloku
                    uint64_t prod = result.digits[i + j] + digits[i] * 1ULL * (j < other.digits.size() ? other.digits[j] : 0) + carry; //1ULL(1 as an unsigned long long integer) is used to promote the result to 64 bits, because we are multiplying 32 bit numbers, and we dont want to lose the data
                    result.digits[i + j] = prod % BASE;
                    carry = prod / BASE;
                }
            }
            result.trim();//Przykład: 1234 * 5678 -> wynik to [7006652, 0]. Bez trim() pozostanie zero na końcu, które trzeba usunąć. Zero zostanie bo robimy resize, ktory zawiera mksymalna ilosc blokow, ale nie gwaarantuje ze tyle ich bedzie, dlatego czasami bloki moga byc puste, czyli rowne zero
            return result;
        }

        // Division operator (integer division)
        BigInt operator/(const BigInt &other) const {
            if (other == 0) throw overflow_error("Division by zero");
            BigInt result, current;
            result.digits.resize(digits.size()); // Moze byc tyle blokow ile jest w dzielnej
            for (int i = digits.size() - 1; i >= 0; --i) { // idziemy od tylu, bo digits jest od tylu, a dzielenie pisemne zaczyna sie od najwiekszej czesci liczby,a nie od najmniejszej
                // Dowód dlaczego current < other * BASE zawsze zachodzi:
                //
                // 1. Aktualizacja current:
                //    W każdej iteracji pętli current jest aktualizowane w ten sposób:
                //        current = current * BASE + digits[i];
                //    To oznacza, że dodajemy do current cyfrę digits[i], która zawsze jest mniejsza od BASE
                //    (ponieważ każda cyfra w digits reprezentuje wartość w systemie pozycyjnym opartym na BASE).
                //
                // 2. Zakres x:
                //    Wyszukujemy x spełniające:
                //        other * x <= current
                //    Wyszukiwanie binarne ogranicza x do zakresu:
                //        0 <= x < BASE
                //    Maksymalna możliwa wartość to więc other * (BASE - 1).
                //
                // 3. Maksymalna wartość current:
                //    Przed odjęciem w każdej iteracji maksymalna wartość current wynosi:
                //        current = other * (BASE - 1) + digits[i];
                //    Ponieważ digits[i] < BASE, to:
                //        current < other * BASE
                //
                // 4. Po każdej iteracji:
                //    W każdej iteracji odejmujemy od current wartość other * x, co powoduje,
                //    że current w kolejnych krokach staje się coraz mniejsze.
                //    Dzięki temu current nigdy nie osiągnie wartości większej lub równej other * BASE.
                //
                // Podsumowanie:
                // Warunek current < other * BASE zawsze jest spełniony,
                // co oznacza, że x nigdy nie osiągnie wartości BASE, (x moze byc maksymalnie BASE-1)
                // a wynik dzielenia jest zawsze poprawny.

                current = current* BASE+ digits[i];// Current, to jest ta czesc glownej liczby od ktorej odejmujy, na ktorej wykonujemy obliczenia. Mnozymy przez BASE, bo nawet jesli digits jest 0 to trzeba przeniesc o BASE, zeby byl poprawny wynik, bo digits=0 moze oznaczac 10^9, tak jakby przesuwamy o jedno miejsce w lewo, tak jak w dzieleniu pisemnym, BASE jest jak jedna cyfra
                uint32_t x = 0, left = 0, right = BASE; //x to ta liczba, ktora jest na gorze w dzieleniu pisemnym, czyli wynik.
                //nie moze byc samo wyszukiwanie binarne, bo dzielimy w wyszukiwaniu binarnym, i nedzie nieskonczona rekurencja
                while (left <= right) { //wyszukiwanie binarne, zeby znalezc liczbe(other*mid) mniejsza lub rowna current, bo to(other*x) odejumujemy od current
                    uint32_t mid = (left + right) / 2;
                    if (other * mid <= current) {
                        x = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                result.digits[i] = x;
                current = current - other * x; //odejmujemy wynik mnozenia przez x(to co jest na gorze), tak jak w dzieleniu pisemnym
            }
            result.trim(); //Przykład: 1000000001 / 1000000000 -> wynik to [1, 0] (dzielimy 10^9 + 1 przez 10^9). Po dzieleniu zero na końcu musi być usunięte.
            return result;
        }

        // Comparison operators
        bool operator<(const BigInt &other) const {
            if (digits.size() != other.digits.size())//sprawdza czy rozmiary tablic digits obu liczb sie roznia, jesli tak to zwraca true jesli digits jest mniejsza od other.digits, a false jak jest wieksza
                return digits.size() < other.digits.size();
            for (int i = digits.size() - 1; i >= 0; --i) {//iteruje sie od tylu, zeby sprawdzac najwieksze czesci liczby
                if (digits[i] != other.digits[i])//jesli jakas czesc sie roznia to zwraca true jesli digits jest mniejsza od other.digits, a false jak jest wieksza
                    return digits[i] < other.digits[i];
            }
            return false;
        }

        bool operator<=(const BigInt &other) const {
            return (*this < other) || (*this == other);//zwraca true jesli aktualny obiekt jest mniejsza od other lub jesli sa rowne
        }

        bool operator==(const BigInt &other) const {
            return digits == other.digits; //operator == sprawdza na wektorach, czy ich wszystkie indeksy sa rowne, sprawdza tez najpierw czy sa rowne czy nie, wiec nie trzeba tego pisac
        }

        // Stream output operator
        //ostream is a class used for output streams in C++ (like std::cout).
        //operator<< for BigInt tells how to output a BigInt object to an ostream
        //bierze dwa argumenty, pierwszy to typ ostream, a drugi to BigInt, zwraca ostream
        friend ostream &operator<<(ostream &out, const BigInt &value) { //friend to jest typ danych, ktory daje dostep do prywatnych danych klasy, w tym przypadku do digits
            if (value.digits.empty()) { //jesli nie ma cyfr to wypisuje 0
                out << 0;
                return out;
            }
            out << value.digits.back();//wypisujemy pierwszy element, bo nie musi byc on dlugosci BASE_DIGITS
            for (int i = value.digits.size() - 2; i >= 0; --i) {//-2, bo zaczynamy od przedostatniego elementu
                out << setw(BASE_DIGITS) << setfill('0') << value.digits[i]; //setw(BASE_DIGITS): Ustawia szerokość pola wyjścia na BASE_DIGITS
                //setfill('0'): Ustala, że w przypadku, gdy liczba ma mniej niż 9 cyfr, miejsce w polu szerokości zostanie wypełnione zerami (0). Na przykład, jeśli cyfra w digits[i] to 123, a szerokość pola wynosi 9, to na wyjściu będzie 000000123.
            }
            return out;
        }
    };

    int main() {
        BigInt num1("1000000000000000000");
        BigInt num2("1000000000");

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
       - Wewnątrz wyszukiwania binarnego, w każdym kroku wykonujemy mnożenie other * mid i sprawdzamy wynik. Ponieważ other może mieć n bloków cyfr,
         każda taka operacja mnożenia ma złożoność O(n), a logatymiczny czas pomijamy, bo jest on zdominowany przez operacje mnożenia.

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
