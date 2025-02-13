#include <bits/stdc++.h>

using namespace std;

// A function to perform BFS on a graph and find the shortest path
vector<int> BFS(int startNode, int targetNode, vector <vector<int>> &adj) {
    int n = adj.size();
    // Vector to keep track of visited nodes
    vector<bool> visited(n, false);
    // Vector to store the parent of each node (for path reconstruction)
    vector<int> parent(n, -1);
    // Vector to store the distance of each node from the start node
    vector<int> distance(n, -1);

    // Create a queue for BFS
    queue<int> q;
    visited[startNode] = true;
    distance[startNode] = 0; // Distance from the start node to itself is 0
    q.push(startNode);

    // Perform BFS
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // If we have reached the target node, break
        if (node == targetNode) {
            break;
        }

        // Explore all adjacent vertices of the current node
        for (int adjacent : adj[node]) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                parent[adjacent] = node;
                distance[adjacent] = distance[node] + 1;
                q.push(adjacent);
            }
        }
    }

    // If the target node is unreachable, return an empty path
    if (distance[targetNode] == -1) {
        return {};
    }

    // Reconstruct the shortest path from targetNode to startNode
    vector<int> path;
    for (int node = targetNode; node != -1; node = parent[node]) {
        path.push_back(node);
    }

    // Reverse the path to get it from startNode to targetNode
    reverse(path.begin(), path.end());

    // Optionally, print the distance to the target node
    cout << "Distance from node " << startNode << " to node " << targetNode << ": " << distance[targetNode] << endl;

    return path;
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

    // Find the shortest path from node 0 to node 5
    int startNode = 0, targetNode = 5;
    vector<int> path = BFS(startNode, targetNode, adj);

    if (!path.empty()) {
        cout << "Shortest path from node " << startNode << " to node " << targetNode << ":\n";
        for (int node : path) {
            cout << node << " ";
        }
    } else {
        cout << "No path found from node " << startNode << " to node " << targetNode << ".\n";
    }

    return 0;
}
