//https://codeforces.com/contest/1658/problem/C
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);

    int ones_count = 0, one_index = -1;

    // Read input and count occurrences of 1
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i] == 1) {
            ones_count++;
            one_index = i;
        }
    }

    // If there is not exactly one "1", it's invalid
    if (ones_count != 1) {
        cout << "NO\n";
        return;
    }

    // Rotate the array to place "1" at the start
    rotate(c.begin(), c.begin() + one_index, c.end());

    // Check if the sequence increases exactly by 1
    for (int i = 1; i < n; i++) {
        if (c[i] - c[i - 1] > 1) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
