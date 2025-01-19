//https://codeforces.com/contest/1462/problem/E2
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        sort(a.begin(), a.end());
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            long long j = upper_bound(a.begin() + i, a.end(), a[i] + k) - a.begin() - 1;
            if (j - i >= 2) {
                ans += (j - i) * (j - i - 1) / 2;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
