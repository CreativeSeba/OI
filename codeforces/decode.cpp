//https://codeforces.com/contest/1996/problem/E

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// (𝑥+1)⋅(𝑛−𝑦1+1)+(𝑥+1)⋅(𝑛−𝑦2+1)+⋯+(𝑥+1)⋅(𝑛−𝑦𝑘+1)
// (𝑥+1)⋅((𝑛−𝑦1+1)+(𝑛−𝑦2+1)+⋯+(𝑛−𝑦𝑘+1))

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        vector<int> p(n + 1, 0); // prefix sum array

        // Compute prefix sums
        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] + (s[i - 1] == '1' ? 1 : -1);
        }

        map<int, long long> cnt;
        long long ans = 0;

        // Iterate from 0 to n
        for (int i = 0; i <= n; i++) {
            // Calculate the contribution from the current prefix sum
            // cnt[p[i]] is like x
            // we are checking how many prefix sums with the same count were before, because they all create a balanced substring
            // the string is balanced if p[r] == p[l-1]
            // what is important is that p[i] = k, the k is the number of ones that are more than the number than zeros, so we need to find the prefix sums up to i with the same number of 1's over zeros so that when we subract them, we get a balaneced substring
            // n-i+1 is our r and cnt[p[i]] is how many x->y can fit in our l
            ans = (ans + (n - i + 1) * cnt[p[i]]) % MOD;

            // Update the count for this prefix sum
            // We add i+1, because it is like x+1
            // our cnt counts in how many l's do the x's fit
            cnt[p[i]] = (cnt[p[i]] + (i + 1)) % MOD;
        }

        cout << ans << "\n";
    }

    return 0;
}
