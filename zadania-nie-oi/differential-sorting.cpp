//https://codeforces.com/contest/1635/problem/C
#include <bits/stdc++.h>

using namespace std;

void solution(vector<int> &a) {
    int n = a.size();
    bool isAscending = true;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            isAscending = false;
            break;
        }
    }
    if (isAscending) {
        cout << 0 << "\n";
        return;
    }
    //we also have to check if a[n-3] (a[n-2] - a[n-1]) is less than a[n-2] and a[n-1], becuase a[n-2] could be -4 and a[n-1] could be -5, so -4 - (-5) = 1, and 1 is more than -4 and -5]
    //a[n-3] can only be equal to a[n-2] - a[n-1], becuase only n-2 (y) and n-1 (z) are greater than n-3 (x)
    a[n-3] = a[n - 2] - a[n - 1];
    if (a[n-3] <= a[n - 2] && a[n-3] <= a[n - 1]) {
        cout << n - 2 << endl;
        for (int i = 0; i < n - 2; i++) {
            cout << i + 1 << " " << n - 1 << " " << n << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (a[n - 1] < a[n - 2]) {
            cout << -1 << "\n";
        } else {
            solution(a);
        }
    }
    return 0;
}
