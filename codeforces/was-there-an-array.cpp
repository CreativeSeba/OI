//https://codeforces.com/contest/2069/problem/A
#include <bits/stdc++.h>

using namespace std;

bool can_construct(const vector<int>& b) {
    for (int i = 0; i < b.size() - 1; i++) {
        if (b[i] == 1 && b[i + 1] == 0 && i + 2 < b.size() && b[i + 2] == 1) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> b(n - 2);

        for (int i = 0; i < n - 2; i++) {
            cin >> b[i];
        }

        cout << (can_construct(b) ? "YES" : "NO") << '\n';
    }

    return 0;
}
