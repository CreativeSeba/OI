//https://szkopul.edu.pl/problemset/problem/Oys6jiVOIap59lYCHRwDMbNT/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

void color(vector<vector<int> > &adj, int start, vector<int> &colors) {
    queue<int> q;
    q.push(start);
    colors[start] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor: adj[node]) {
            if (colors[neighbor] == -1) {
                colors[neighbor] = 1 - colors[node];
                q.push(neighbor);
            }
        }
    }
}

void colorGraph(vector<vector<int> > &adj, vector<int> &colors) {
    int n = adj.size();

    for (int i = 0; i < n; i++) {
        if (colors[i] == -1) {
            color(adj, i, colors);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<vector<int> > adj(n);
    vector<int> colors(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    for (vector<int> entry : adj) {
        if (entry.empty()) {
            cout<<"NIE\n";
            return 0;
        }
    }
    colorGraph(adj, colors);
    cout << "TAK\n";
    for (int color: colors) {
        if (color == 0) {
            cout << "S\n";
        } else {
            cout << "K\n";
        }
    }
    return 0;
}
