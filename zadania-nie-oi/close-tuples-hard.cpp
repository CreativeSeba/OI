//https://codeforces.com/contest/1462/problem/E2
#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

//dwumian newtona nie liczy permutacji, tylko kombinacje. Patrzy na ile sposobw mozna zrobic rozne 'okienka'
vector<vector<int>> compute_binomial_coefficients(int n, int m) {
    // Extra row (n+1) is needed to handle base case C(0, 0) = 1, and C(0, j) = 0 for j > 0.
    // Extra column (m+1) ensures we can compute all combinations C(n, j) for 0 <= j <= m, including C(n, 0) = 1.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(i, m); j++) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
        }
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        //n - liczba elementow w tablicy
        //m - liczba elementow w okienku
        //k - maksymalna roznica miedzy pierwszym i ostatnim elementem w okienku
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n);

        // Read the array
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // Sort the array
        sort(a.begin(), a.end());

        // Precompute binomial coefficients
        auto dp = compute_binomial_coefficients(n, m);

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            //zwraca iterator, ale - a.begin() zwraca odleglosc od poczatku tablicy (zamienia na indeks) i -1, zeby miec <= k a nie > k
            long long j = upper_bound(a.begin() + i, a.end(), a[i] + k) - a.begin() - 1;
            //j-i+1 - liczba elementow w okienku (musi byc >= m)
            if (j - i + 1 >= m) {
                //j-1 do liczba elementow w przedziale(n), a m-1 (bo jest indeksowanie od zera w dp) to liczba elementow w okienku
                ans += dp[j - i][m - 1];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
