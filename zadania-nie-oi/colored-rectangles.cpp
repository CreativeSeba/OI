//https://codeforces.com/contest/1398/problem/D
//zachlanny tu nie zadziala, bo na przyklad dla 2 1 1  5 5  9  8, jak obliczysz maksa dla 5,9,8, czyli dla pierwszej kolumny, to przestaniesz brac pod uwage 5, i nie policzysz 5*5
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int r, g, b;
    cin >> r >> g >> b;

    vector<int> red(r), green(g), blue(b);
    vector<vector<vector<int>>> dp(r+1, vector<vector<int>>(g+1, vector<int>(b+1, 0)));

    for (int i = 0; i < r; i++) cin >> red[i];
    for (int i = 0; i < g; i++) cin >> green[i];
    for (int i = 0; i < b; i++) cin >> blue[i];

    sort(red.rbegin(), red.rend());
    sort(green.rbegin(), green.rend());
    sort(blue.rbegin(), blue.rend());

    for (int i = 0; i <= r; i++) {
        for (int j = 0; j <= g; j++) {
            for (int k = 0; k <= b; k++) {
                if (i > 0 && j > 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + red[i-1] * green[j-1]);
                if (i > 0 && k > 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + red[i-1] * blue[k-1]);
                if (j > 0 && k > 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k-1] + green[j-1] * blue[k-1]);
            }
        }
    }

    cout << dp[r][g][b] << endl;
    return 0;
}