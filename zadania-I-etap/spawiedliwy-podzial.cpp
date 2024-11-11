#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Struktura przechowująca przedmioty
struct Item {
    int valueA;
    int valueB;
};

int main() {
    int n;
    cin >> n;
    vector<Item> items(n);
    vector<int> a(n), b(n);

    // Wczytanie wartości dla Bajtyny i Bitka
    for (int i = 0; i < n; ++i) {
        cin >> items[i].valueA;
    }
    for (int i = 0; i < n; ++i) {
        cin >> items[i].valueB;
    }

    long long totalA = 0, totalB = 0;
    for (int i = 0; i < n; ++i) {
        totalA += items[i].valueA;
        totalB += items[i].valueB;
    }

    // Tablica DP, przechowuje informacje o możliwych różnicach sum
    // offset pozwala uniknąć ujemnych indeksów
    const int offset = 500000;
    vector<vector<bool>> dp(n + 1, vector<bool>(2 * offset + 1, false));
    vector<vector<int>> assignment(n + 1, vector<int>(2 * offset + 1, -1));

    dp[0][offset] = true; // Początkowy stan: żadnych przedmiotów, różnica sum to 0

    // Dynamiczne przypisywanie przedmiotów
    for (int i = 0; i < n; ++i) {
        for (int diff = -offset; diff <= offset; ++diff) {
            int index = diff + offset;
            if (!dp[i][index]) continue;

            // Przypadek przypisania przedmiotu i do Bajtyny
            int newDiff = diff + items[i].valueA - items[i].valueB;
            if (newDiff >= -offset && newDiff <= offset) {
                dp[i + 1][newDiff + offset] = true;
                assignment[i + 1][newDiff + offset] = 0; // 0 - przypisane do Bajtyny
            }

            // Przypadek przypisania przedmiotu i do Bitka
            newDiff = diff - items[i].valueA + items[i].valueB;
            if (newDiff >= -offset && newDiff <= offset) {
                dp[i + 1][newDiff + offset] = true;
                assignment[i + 1][newDiff + offset] = 1; // 1 - przypisane do Bitka
            }
        }
    }

    // Szukanie rozwiązania
    int targetDiff = -1;
    for (int diff = 0; diff <= offset; ++diff) {
        if ((dp[n][diff + offset] || dp[n][offset - diff]) &&
            (totalA >= totalB - diff && totalB >= totalA - diff)) {
            targetDiff = (dp[n][diff + offset] ? diff : -diff);
            break;
        }
    }

    // Rekonstrukcja przydziału przedmiotów
    vector<int> result(n, 0);
    int currentDiff = targetDiff + offset;
    for (int i = n; i > 0; --i) {
        if (assignment[i][currentDiff] == 0) {
            result[i - 1] = 0;
            currentDiff -= (items[i - 1].valueA - items[i - 1].valueB);
        } else {
            result[i - 1] = 1;
            currentDiff += (items[i - 1].valueA - items[i - 1].valueB);
        }
    }

    // Wypisz wynik
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;


    return 0;
}
