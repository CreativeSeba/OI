#include <bits/stdc++.h>

using namespace std;

// Funkcja obliczająca najdłuższe wspólne zająknięcie
int lcs(vector<int> &A, vector<int> &B, int n, int m) {
    // Wektory do przechowywania poprzednich i aktualnych wartości dp
    vector<int> current(n + 1, 0), previous(n + 1, 0);
    map<int, int> ostx;  // Przechowuje indeksy ostatnich takich samych elementów dla A
    map<int, int> osty;   // Przechowuje indeksy ostatnich takich samych elementów dla B
    map<pair<int,int>, int> values; // Przechowuje wartości dla danego indeksu
    // Szukanie ostatnich takich samych elementów w ciągu A
    for (int i = 0; i < n; i++) {
        if(ostx.find(i) == ostx.end()) {
            ostx[i] = -1;
        }
        for (int j = i + 1; j < n; j++) {
            if (A[j] == A[i]) {
                ostx[j] = i;
                break;
            }
        }
    }

    // Szukanie ostatnich takich samych elementów w ciągu B
    for (int i = 0; i < m; i++) {
        if(osty.find(i) == osty.end()) {
            osty[i] = -1;
        }
        for (int j = i + 1; j < m; j++) {
            if (B[j] == B[i]) {
                osty[j] = i;
                break;
            }
        }
    }
//    for(auto &i: ostx) {
//        cout<<i.first<<" "<<i.second<<endl;
//    }
//    cout<<endl;
//    for(auto &i: osty) {
//        cout<<i.first<<" "<<i.second<<endl;
//    }
    for(auto &i: osty) {
        for(auto &j: ostx) {
            if(A[j.first] == B[i.first] && j.second != -1 && i.second != -1) {
                values[make_pair(i.second, j.second)]=0;
            }
        }
    }
    // Dynamiczne programowanie - szukanie najdłuższego wspólnego zająknięcia
    for (int i = 0; i <= m; ++i) { // Iterujemy po ciągu B
        for (int j = 1; j <= n; ++j) { // Iterujemy po ciągu A
            // Przepisujemy wartość z poprzedniego wiersza
            current[j] = max(previous[j], current[j - 1]);

            // Jeśli elementy się zgadzają, próbujemy wydłużyć zająknięcie
            if (A[j - 1] == B[i - 1]) {
                int prev_x = ostx[j - 1];
                int prev_y = osty[i - 1];
                for(auto &k: values) {
                    if(k.first.first == i && k.first.second == j) {
                        k.second = previous[j-1];
                        break;
                    }
                }
                if(prev_x != -1 && prev_y != -1 && A[prev_x] == B[prev_y]) {
                    current[j] = max(current[j], values[make_pair(prev_y, prev_x)] + 2);
                }
            }
        }
        // Zamieniamy wektory, aby przejść do następnego wiersza
//        for(auto &i: current) {
//            cout << i << " ";
//        }
//        cout<<endl;
        swap(current, previous);
    }
//    cout<<endl<<endl;
//    for(auto &i: values) {
//        cout<<i.first.first<<" "<<i.first.second<<" "<<i.second<<endl;
//    }
    // Zwracamy wynik
    return previous[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    // Wczytanie danych
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    // Wywołanie funkcji lcs i wypisanie wyniku
    cout << lcs(A, B, n, m) << endl;

    return 0;
}

//#include <bits/stdc++.h>
//
//using namespace std;
//
//int lcs(vector<int> &A, vector<int> &B, int& n, int& m) {
//    // Tablica dp do dynamicznego programowania, wypełniona zerami
//    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
//    vector<int> ostx(n, -1);  // Przechowuje indeksy ostatnich takich samych elementów dla A
//    vector<int> osty(m, -1);  // Przechowuje indeksy ostatnich takich samych elementów dla B
//
//    // Szukanie ostatnich takich samych elementów w ciągu A
//    for (int i = 0; i <=n; i++) {
//        for (int j = i+1; j <=n; j++) {
//            if (A[j] == A[i]) {
//                ostx[j] = i;
//                break;
//            }
//        }
//    }
//
//    // Szukanie ostatnich takich samych elementów w ciągu B
//    for (int i = 0; i <=m; i++) {
//        for (int j = i+1; j <=m; j++) {
//            if (B[j] == B[i]) {
//                osty[j] = i;
//                break;
//            }
//        }
//    }
//
////    for(int i = 0; i < n; i++) {
////        cout << ostx[i] << " ";
////    }
////    cout << endl;
////    for(int i = 0; i < m; i++) {
////        cout << osty[i] << " ";
////    }
//    // Dynamiczne programowanie - szukanie najdłuższego wspólnego zająknięcia
//    for (int i = 1; i <= m; ++i) { // Rows for B
//        for (int j = 1; j <= n; ++j) { // Columns for A
//            // Checking for valid indices and matching characters
//            int prev_x = ostx[j - 1]; // last occurrence in A (for column j)
//            int prev_y = osty[i - 1]; // last occurrence in B (for row i)
//
//            if (A[j - 1] == B[i - 1]) { // Matching current characters
//                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // Get max from previous row or column
//
//                if (prev_x != -1 && prev_y != -1 && A[prev_x] == B[prev_y]) {
//                    // If previous characters match, add 2 to the result from dp[prev_y+1][prev_x+1]
//                    dp[i][j] = max(dp[i][j], dp[prev_y][prev_x] + 2);
//                }
//            } else {
//                // Standard LCS transition
//                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//            }
//        }
//    }
//
//    // Debug: Wyświetlenie tablicy dp (opcjonalne)
////    cout << "Tablica dp:" << endl;
////     for (int i = 0; i <= m; i++) {
////         for (int j = 0; j <= n; j++) {
////             cout << dp[i][j] << " ";
////         }
////         cout << endl;
////     }
//
//    // Wynik to dp[m][n]
//    return dp[m][n];
//}
//
//int main() {
//    int n, m;
//    // Wczytanie danych
//    cin >> n >> m;
//    vector<int> A(n), B(m);
//    for (int i = 0; i < n; i++) {
//        cin >> A[i];
//
//    }
//    for (int i = 0; i < m; i++) {
//        cin >> B[i];
//    }
//    // Wywołanie funkcji lcs i wypisanie wyniku
//    cout << lcs(A, B, n, m) << endl;
//
//    return 0;
//}
