//https://szkopul.edu.pl/problemset/problem/wOKsnzwNqHqXqiX6m3AkufgX/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3000;
vector<int> bitada_adj[MAXN + 1];
vector<int> bajtograd_adj[MAXN + 1];
int n, m, k;
vector<vector<int>> dp;

bool isValidAssignment(int house, int mask, int tower) {
    for (int neighbor : bitada_adj[house + 1]) {
        if ((mask & (1 << (neighbor - 1))) && find(bajtograd_adj[tower + 1].begin(), bajtograd_adj[tower + 1].end(), neighbor) == bajtograd_adj[tower + 1].end()) {
            return false;
        }
    }
    return true;
}

int dfs(int mask, int last_tower) {
    if (dp[mask][last_tower] != -1) {
        return dp[mask][last_tower];
    }

    if (__builtin_popcount(mask) == n) {
        return 1;
    }

    int result = 0;
    for (int house = 0; house < n; house++) {
        if (!(mask & (1 << house)) && isValidAssignment(house, mask, last_tower)) {
            result = (result + dfs(mask | (1 << house), house)) % k;
        }
    }

    return dp[mask][last_tower] = result;
}

int main() {
    cin >> n >> m >> k;

    dp.resize(1 << n, vector<int>(n + 1, -1));

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        bitada_adj[x].push_back(y);
        bitada_adj[y].push_back(x);
    }

    for (int i = 0; i < m - 1; ++i) {
        int x, y;
        cin >> x >> y;
        bajtograd_adj[x].push_back(y);
        bajtograd_adj[y].push_back(x);
    }

    cout << dfs(0, 0) << endl;

    return 0;
}