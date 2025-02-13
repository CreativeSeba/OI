//https://chatgpt.com/share/675577cd-dd84-800f-848a-a0b3135c1edd
//dwumian newtona

#include <bits/stdc++.h>

using namespace std;

//Różni się od liczenia kombinacji potęgą ( czyli np. 3^n), że w potęgowaniu liczymy dla każdego elementu(czyli np jesli element moze byc 1, 2 lub 3, to potegujemy 3), a w dwumianie liczymy kombinacje w jaimś ciągu, czyli 1, 2, 3, 4
//dwumian newtona nie liczy permutacji, tylko kombinacje. Patrzy na ile sposobw mozna zrobic rozne 'okienka'
vector<vector<int> > compute_binomial_coefficients(int n, int m) {
    // Extra row (n+1) is needed to handle base case C(0, 0) = 1, and C(0, j) = 0 for j > 0.
    // Extra column (m+1) ensures we can compute all combinations C(n, j) for 0 <= j <= m, including C(n, 0) = 1.
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(i, m); j++) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
        }
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //n - liczba elementow w tablicy
    //m - liczba elementow w okienku
    int n, m;
    cin >> n >> m;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Precompute binomial coefficients
    auto dp = compute_binomial_coefficients(n, m);

    for (vector<int> v: dp) {
        for (int i: v) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
