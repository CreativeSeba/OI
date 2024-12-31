#include <bits/stdc++.h>

using namespace std;

//Pre-order – stosowany przy odwiedzaniu i przetwarzaniu węzłów w kolejności hierarchii (od korzenia w dół).

// A function to perform DFS on a graph
void DFS(int node, vector <vector<int>> &adj, vector<bool> &visited) {
    // Mark the current node as visited
    visited[node] = true;
    cout << node << " ";  // Output the visited node

    // Recur for all adjacent vertices of the current node
    for (int adjacent: adj[node]) {
        if (!visited[adjacent]) {
            DFS(adjacent, adj, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // Number of nodes (vertices) in the graph
    int n = 6;

    // Adjacency list representation of the graph
    vector <vector<int>> adj(n);

    // Example edges in the graph
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(5);

    // Vector to keep track of visited nodes
    vector<bool> visited(n, false);

    // Perform DFS starting from node 0
    cout << "DFS traversal starting from node 0:\n";
    DFS(0, adj, visited);

    return 0;
}
