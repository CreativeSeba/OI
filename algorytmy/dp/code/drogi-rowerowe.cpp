#include <bits/stdc++.h>

using namespace std;

// Function to perform DFS and store the finish order of nodes
void DFS(int node, vector <vector<int>> &adj, vector<bool> &visited, stack<int> &finishStack) {
    visited[node] = true;
    for (int adjacent: adj[node]) {
        if (!visited[adjacent]) {
            DFS(adjacent, adj, visited, finishStack);
        }
    }
    finishStack.push(node);
}

// Function to perform DFS on the transposed graph to find SCCs
void DFSUtil(int node, vector <vector<int>> &transposed, vector<bool> &visited, vector<int> &scc) {
    visited[node] = true;
    scc.push_back(node);
    for (int adjacent: transposed[node]) {
        if (!visited[adjacent]) {
            DFSUtil(adjacent, transposed, visited, scc);
        }
    }
}

// Function to calculate the number of nodes reachable from each SCC
int countReachable(int sccId, vector <vector<int>> &adj, vector<bool> &visited, vector<int> &dp) {
    if (visited[sccId]) return dp[sccId]; //nie musimy przeprowadzac kolejnego dfsa na tym samym scc, bo kazy node w scc ma tyle samo reachable nodes
    visited[sccId] = true;

    int reachableNodes = dp[sccId]; // Start by counting the nodes in this SCC itself
    for (int nextSccId: adj[sccId]) {
        reachableNodes += countReachable(nextSccId, adj, visited, dp);
    }

    return dp[sccId] = reachableNodes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector <vector<int>> adj(n), transposed(n);
    pair<int, int> edges[m];

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        transposed[v - 1].push_back(u - 1);
        edges[i] = {u - 1, v -
                           1}; //jesli nie uzyjem edges to potem w SCCGraph bedziemy musieli przechodzic po wszystkich krawedziach, co bedzie mniej wydajne
    }

    // Step 1: Perform DFS to get nodes in finishing order
    stack<int> finishStack;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i, adj, visited, finishStack);
        }
    }

    // Step 2: Find SCCs using DFS on the transposed graph
    vector <vector<int>> SCCs;
    fill(visited.begin(), visited.end(), false);

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();

        if (!visited[node]) {
            vector<int> scc;
            DFSUtil(node, transposed, visited, scc);
            SCCs.push_back(scc);
        }
    }

    // Step 3: Build a graph of SCCs (condensed graph)
    vector<int> sccId(n);  // Maps each node to its SCC ID
    vector<int> sccReachCount(SCCs.size());  // Reach count for each SCC
    vector <vector<int>> SCCGraph(SCCs.size());  // Graph of SCCs

    for (int i = 0; i < SCCs.size(); i++) {
        for (int node: SCCs[i]) {
            sccId[node] = i;
        }
        sccReachCount[i] = SCCs[i].size();  // Initially, reach count is the size of the SCC itself
    }

    // Add edges between SCCs
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        if (sccId[u] != sccId[v]) {
            SCCGraph[sccId[u]].push_back(sccId[v]);  // Create edge between SCCs
        }
    }

    // Step 4: For each SCC, compute how many nodes are reachable
    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < SCCs.size(); i++) {
        if (!visited[i]) {
            countReachable(i, SCCGraph, visited, sccReachCount);
        }
    }

    // Step 5: Output the number of reachable nodes for each original node
    for (int i = 0; i < n; i++) {
        cout << sccReachCount[sccId[i]] - 1 << endl;
    }
//    for (int i = 0; i < SCCs.size(); i++) {
//        cout << "SCC " << i + 1 << ": ";
//        for (int j: SCCs[i]) {
//            cout << j + 1 << " "; // Print nodes in the SCC
//        }
//        cout << "\n";
//    }
//
//    cout << "Condensed graph edges (SCCs as nodes):\n";
//    for (int i = 0; i < SCCs.size(); i++) {
//        for (int j: SCCGraph[i]) {
//            cout << "SCC " << i + 1 << " -> SCC " << j + 1 << "\n"; // Print edges between SCCs
//        }
//    }

    return 0;
}
