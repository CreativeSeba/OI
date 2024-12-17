#include <bits/stdc++.h>

using namespace std;

// A function to perform BFS on a graph
void BFS(int startNode, vector <vector<int>> &adj, vector<bool> &visited) {
    // Create a queue for BFS
    queue<int> q;

    // Mark the start node as visited and enqueue it
    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        // Dequeue a vertex from the queue and print it
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, mark it visited and enqueue it
        for (int adjacent: adj[node]) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                q.push(adjacent);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
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

    // Perform BFS starting from node 0
    cout << "BFS traversal starting from node 0:\n";
    BFS(0, adj, visited);

    return 0;
}
