#include <bits/stdc++.h>

using namespace std;

int maximalSquare(vector<vector<char> > &matrix) {
    int n = matrix.size(), m = matrix[0].size();
    int ans = 0;

    vector<int> dp(m + 1, 0);

    int diagonal = 0;

    //we iterate from the end of the matrix, becuase it requires less nested ifs to check if we dont exceed the dp bounds, becuase our dp array is 1 element bigger than the matrix, so we dont have to check the bounds
    //if we would iterate from the start, we would have to check if we dont exceed the bounds of the dp array, because we cant check -1 index
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int tmp = dp[j];

            if (matrix[i][j] == '0') {
                dp[j] = 0;
            } else {
                dp[j] = 1 + min({dp[j], diagonal, dp[j + 1]});
            }

            diagonal = tmp;

            ans = max(ans, dp[j]);
        }
    }

    return ans * ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char> > matrix(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << maximalSquare(matrix) << "\n";
    return 0;
}
