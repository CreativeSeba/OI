#include "kaslib.h"
#include <iostream>
#include <vector>
#include <algorithm> // Dodano, aby używać sort()
#include <cmath>
#include <cassert>

using namespace std;

// Generowanie dzielników liczby n
vector<long long> generuj_dzielniki(long long n) {
    vector<long long> dzielniki;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            dzielniki.push_back(i);
            if (i != n / i) {
                dzielniki.push_back(n / i);
            }
        }
    }
    return dzielniki;
}

// Funkcja zgadywania liczby
void kasyno() {
    long long n = DajN(); // Pobranie liczby n
    vector<long long> dzielniki = generuj_dzielniki(n); // Generowanie dzielników liczby n
    sort(dzielniki.begin(), dzielniki.end()); // Posortowanie dzielników rosnąco

    vector<long long> mozliwe = dzielniki; // Lista możliwych wartości dla x

    while (true) {
        if (mozliwe.size() == 1) {
            // Gdy zostaje tylko jedna możliwa liczba x, zgadujemy
            Odpowiedz(mozliwe[0]);
            continue;
        }

        // Wybór liczby y: wybieramy średnią wartość z możliwych liczb
        long long y = mozliwe[mozliwe.size() / 2];

        // Zadajemy pytanie o nwd(x, y)
        long long wynik = Pytaj(y);

        if (wynik == y) {
            // Jeśli nwd(x, y) = y, oznacza to, że x = y
            Odpowiedz(y);
            continue;
        }

        // Zawężamy przestrzeń możliwych liczb x
        vector<long long> nowe_mozliwe;
        for (long long d : mozliwe) {
            if (d % wynik == 0) {
                nowe_mozliwe.push_back(d);
            }
        }
        mozliwe = nowe_mozliwe;

        // Jeśli przestrzeń możliwych liczb jest za duża, to szturchamy maszynę
        if (mozliwe.size() > 1000) {
            Szturchnij();
            mozliwe = dzielniki; // Resetujemy możliwe wartości
        }
    }
}

int main() {
    kasyno(); // Rozpoczęcie gry
    return 0;
}
