//Graf dwudzielny - kolorowanie grafu
#include <bits/stdc++.h>

using namespace std;

bool isBipartite(vector<vector<int>>& adj, int start, vector<int>& colors) {
    queue<int> q;
    q.push(start);
    colors[start] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (colors[neighbor] == -1) { // If not colored
                //colors[node] to albo 0, albo 1, wiec 1 - colors[node] to zawsze przeciwny kolor
                colors[neighbor] = 1 - colors[node]; // Assign opposite color
                q.push(neighbor);
            } else if (colors[neighbor] == colors[node]) {
                return false; // Found the same color in adjacent nodes
            }
        }
    }
    return true;
}

// Sprawdza dla całego grafu, nawet jeśli nie jest spójny
// kolorujemy wszystkie wierzchołki połączone do danego wierzchołka, tylko nie robimy tego pojedynczo, tylko po prostu mamy tablicę colors, która ma rozmiar n i n to jest liczba tych sasiednich wierzchołków, wiec jeśli zmienimy wartość color to kolorujemy wszystkie sąsiednie wierzcholki
bool checkBipartite(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> colors(n, -1); // -1: Uncolored, 0: First color, 1: Second color

    for (int i = 0; i < n; i++) {
        if (colors[i] == -1) { // If not yet visited
            if (!isBipartite(adj, i, colors)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    vector<vector<int>> adj(n);
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (checkBipartite(adj)) {
        cout << "The graph is bipartite." << endl;
    } else {
        cout << "The graph is not bipartite." << endl;
    }

    return 0;
}