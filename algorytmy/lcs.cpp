#include <bits/stdc++.h>

using namespace std;


int lcs(string &S1, string &S2) {
    int m = S1.size(); //dlugosc m i n
    int n = S2.size();

    //tablica dwuwymiarowa, z jednym dodatkowym wierszem i kolumna, wypelniona zerami, i na poczatku wszystkie wartosci sa zerowe
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (S1[i - 1] == S2[j - 1]) //jesli litery sa takie same to zwiekszamy wartosc w dp[i][j] o 1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else //jesli nie to przypisujemy wartosc z gory lub z lewej
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];//wynik znajduje sie w dp[m][n]
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string S1 = "AGGTAB";
    string S2 = "GXTXAYB";
    cout << "Length of LCS is " << lcs(S1, S2) << endl;

    return 0;
}
