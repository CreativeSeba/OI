#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // Wczytanie długości obu ciągów
    int n, m;
    cin >> n >> m;

    // Deklaracja ciągów A i B, oraz pomocniczych tablic
    vector<int> A(n + 1), B(m + 1);
    vector<int> lastA(n + 1, 0), lastB(m + 1, 0);  // lastA[i] = ostatnie wystąpienie A[i]
    // dp przechowuje dlugosz najdluzszego zająknięcia dla j-tego elementu z B
    vector<int> dp(m + 1, 0), equal(m + 1, 0);      // dp[j] = długość zająknięcia dla B[j]
    // equal[j]: Przechowuje pozycję w tablicy A, która odpowiada aktualnie dopasowanemu
    // zająknięciu kończącemu się na pozycji j w tablicy B. Dzięki temu sprawdzane jest,
    // czy pary w A i B są wyrównane i zachowana jest ich kolejność.

    // Wczytanie ciągów A i B
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> B[i];
    }

    // Wyszukiwanie ostatnich wystąpień dla każdego elementu w ciągu A
    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j > 0; --j) {
            if (A[i] == A[j]) {
                lastA[i] = j;  // Zapamiętujemy ostatnie wystąpienie A[i] przed pozycją i
                break;
            }
        }
    }

    // Wyszukiwanie ostatnich wystąpień dla każdego elementu w ciągu B
    for (int i = 1; i <= m; ++i) {
        for (int j = i - 1; j > 0; --j) {
            if (B[i] == B[j]) {
                lastB[i] = j;  // Zapamiętujemy ostatnie wystąpienie B[i] przed pozycją i
                break;
            }
        }
    }

    // Dynamiczne obliczanie najdłuższego wspólnego zająknięcia
    for (int i = 1; i <= n; ++i) {
        if (lastA[i] != 0) {  // Sprawdzamy, czy istnieje wcześniejsze wystąpienie A[i]
            for (int j = 1; j <= m; ++j) {
                // Warunki, aby zaktualizować dp[j]:
                // - Jeśli dp[j-1] > dp[j], oznacza to, że poprzednia część ciągu B była dłuższa,
                // - Albo jeśli A[i] == B[j] i spełnione są dodatkowe warunki na zająknięcie.
                bool isValid = false; // sprawdza czy można zwiększyć długość zająknięcia

                if (dp[j - 1] > dp[j]) { // jesli dp[j-1] > dp[j] to znaczy ze dp[j] ma miejsce by byc zwiększony
                    isValid = true;  // Zająknięcie w B może być wydłużone
                }

                // Sprawdzamy, czy możemy rozciągnąć najdłuższe wspólne zająknięcie (LCS) przez dopasowanie A[i] i B[j]:
                // 1. A[i] musi być równe B[j],
                // 2. B[j] musi mieć wcześniejsze wystąpienie (lastB[j] != 0),
                // 3. Długość zająknięcia dla B[j] musi być taka sama, jak dla poprzedniego elementu w B,
                // 4. Pozycja, na której znaleziono dopasowanie w A (equal[lastB[j] - 1]), musi być mniejsza od pozycji A[i],
                //    aby zachować poprawną kolejność elementów w A i B.
                if (A[i] == B[j] && lastB[j] != 0 && dp[j] == dp[lastB[j] - 1] && equal[lastB[j] - 1] < lastA[i]) {
                    isValid = true;
                }

                if (isValid) {
                    dp[j]++;  // Zwiększamy długość zająknięcia
                    equal[j] = i;  // Zapisujemy, że w tej pozycji A[i] odpowiada B[j]
                }
            }
        }
    }

    // Wynik to podwójna długość najdłuższego wspólnego zająknięcia
    cout << dp[m] * 2 << endl;

    return 0;
}
