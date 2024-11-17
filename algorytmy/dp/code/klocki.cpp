#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int max_weight(int k, int s, vector<int>& weights) {
    // Inicjalizacja jednowymiarowej tablicy dp o rozmiarze S + 1
    vector<int> dp(s + 1, INF);
    dp[0] = 0; // Do osiągnięcia masy 0 potrzebujemy 0 klocków

    // Przechodzimy przez każdy klocek
    for (int w : weights) {
        // Przetwarzamy tablicę dp od tyłu, aby nie nadpisać wyników, bo może byc ze uzyejmy dwa razy ten sam klocek, np. dp[2] = 1, dp[4] = 2, dp[6] = 3, itd, wtedy uzywamy klocka 2 kilka razy i to jest bledne
        // iteracja od tylu, pozwala na to, ze dodajemy klocek tylko wtedy kiedy nie bylismy w stanie osiagnac tej masy wczesniej, wiec uzywamy go raz dla kazdej kombinacji
        for (int j = s; j >= w; --j) {
            // Aktualizujemy dp[j] minimalną liczbą klocków potrzebnych do osiągnięcia masy j
            dp[j] = min(dp[j], dp[j - w] + 1);
        }
    }

    // Szukamy największej możliwej masy, którą można osiągnąć przy użyciu co najwyżej k klocków
    for (int j = s; j >= 0; --j) {
        if (dp[j] <= k) {
            return j; // Zwracamy największą osiągalną masę
        }
    }

    return 0; // Jeśli żadna masa nie jest osiągalna
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k, s;
    cin >> n >> k >> s;
    vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << max_weight(k, s, weights) << endl;
    return 0;
}
