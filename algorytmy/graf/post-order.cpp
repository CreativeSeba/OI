//Stosowany tam, gdzie najpierw musimy odwiedzić dzieci węzła, np. obliczając wartości w poddrzewach. Obliczanie wartości dla dzieci (poddrzewa).
#include <bits/stdc++.h>

using namespace std;

void post_order(int node, vector<vector<int>>& adj, vector<bool>& visited){
    visited[node] = true;

    for(int adjacent : adj[node]){
        if(!visited[adjacent]){
            post_order(adjacent, adj, visited);
        }
    }
    cout << node << " ";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<bool> visited(n + 1, false);
    post_order(1, adj, visited);
}
