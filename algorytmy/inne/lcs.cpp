#include <bits/stdc++.h>

using namespace std;

int lcs(string &S1, string &S2) {
    int m = S1.size(); // Length of S1
    int n = S2.size(); // Length of S2

    // Create two arrays to store the current and previous row of the DP table
    vector<int> prev(n + 1, 0);  // Previous row
    vector<int> curr(n + 1, 0);  // Current row

    // Traverse through the strings
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (S1[i - 1] == S2[j - 1]) {
                // If characters match, the current value is 1 + the diagonal value from the previous row
                curr[j] = prev[j - 1] + 1;
            } else {
                // Otherwise, the current value is the max of the top or left cell
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        // After each row calculation, move the current row to the previous row for the next iteration
        swap(prev, curr);
    }

    // The result is in the last element of the previous row
    return prev[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    string S1 = "AGGTAB";
    string S2 = "GXTXAYB";

    cout << "Length of LCS is " << lcs(S1, S2) << endl;

    return 0;
}
