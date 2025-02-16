//https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/site/?key=statement
//dekompozycja pierwiastkowa
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, k;
    cin >> n >> k;

    int nsqrt = sqrt(n);
    vector<int> result(n + 1, 0);
    vector<vector<int> > query(n + 1, vector<int>(nsqrt + 1, 0));

    for (int i = 0; i < k; i++) {
        int a, l, d;
        cin >> a >> l >> d;
        int end = a + (l - 1) * d;
        if (d <= nsqrt) {
            query[a][d] += 1;
            if (end + d <= n) {
                query[end + d][d] -= 1;
            }
        } else {
            for (int i = a; i <= end; i += d) {
                result[i] += 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= nsqrt; j++) {
            result[i] += query[i][j];
            if (i + j <= n) {
                query[i + j][j] += query[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    return 0;
}
