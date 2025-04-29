//https://codeforces.com/problemset/problem/1648/B
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        vector<int> a(n), cnt(c + 1);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt[a[i]] = 1;
        }

        //it is used to check if there is a single element of a rane <x, y> in the array
        vector<int> prefix(c + 1);
        prefix[0] = 0;
        for (int i = 1; i <= c; i++) {
            prefix[i] = prefix[i - 1] + cnt[i];
        }

        bool isIntegral = true;

        //we are using contradicitng logic here, we only check the r's that arent in the array, and we check if some pairs of x and y produce this r
        for (int r = 1; r <= c; ++r) {
            if (cnt[r]) continue;
            //c/y are all possible y's not greater than c that can be used to produce r
            for (int y = 1; y <= c / r; ++y) {
                if (!cnt[y]) continue;

                int l = r * y;
                int r = min(c, (r + 1) * y - 1);

                if (l > r) continue; // no valid range

                if (prefix[r] - prefix[l - 1] > 0) {
                    isIntegral = false;
                    break;
                }
            }

            if (!isIntegral) break;
        }

        cout << (isIntegral ? "Yes" : "No") << '\n';
    }

    return 0;
}
