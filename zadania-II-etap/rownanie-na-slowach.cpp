//https://szkopul.edu.pl/problemset/problem/A7ZI0Wwn6tTiCJoYblblTAqz/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

// Function to perform DFS and store the finish order of nodes
void DFS(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& finishStack) {
    visited[node] = true;
    for (int adjacent : adj[node]) {
        if (!visited[adjacent]) {
            DFS(adjacent, adj, visited, finishStack);
        }
    }
    finishStack.push(node);
}

// Function to perform DFS on the transposed graph to find SCCs
void DFSUtil(int node, vector<vector<int>>& transposed, vector<bool>& visited, vector<int>& scc) {
    visited[node] = true;
    scc.push_back(node);
    for (int adjacent : transposed[node]) {
        if (!visited[adjacent]) {
            DFSUtil(adjacent, transposed, visited, scc);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int x;  // Number of equations
    cin >> x;

    while (x--) {
        int k; // Number of variables
        cin >> k;
        vector<int> var(k); // Lengths of each variable
        for (int i = 0; i < k; i++) {
            cin >> var[i];
        }

        int l; // Length of the left side of the equation
        cin >> l;
        string leftSide;
        cin >> leftSide;

        int r; // Length of the right side of the equation
        cin >> r;
        string rightSide;
        cin >> rightSide;

        // Step 1: Create graph adjacency list
        unordered_map<char, int> variableIndex; // Map variables to their starting index
        vector<int> lengths;                   // Store lengths of variables
        int idx = 0;

        // Map each variable to its starting index and calculate the total number of vertices
        for (int i = 0; i < k; i++) {
            char variable = 'a' + i;
            variableIndex[variable] = idx;
            idx += var[i];
            lengths.push_back(var[i]);
        }

        // Check if '0' or '1' appear in the input
        bool hasZero = leftSide.find('0') != string::npos || rightSide.find('0') != string::npos;
        bool hasOne = leftSide.find('1') != string::npos || rightSide.find('1') != string::npos;

        int totalVertices = idx + (hasZero ? 1 : 0) + (hasOne ? 1 : 0); // Include vertices for 0 and 1 if they appear
        vector<vector<int>> adj(totalVertices);
        vector<int> leftExpanded, rightExpanded;

        // Step 2: Expand left and right sides of the equation
        auto expand = [&](const string& side, vector<int>& expanded) {
            for (char c : side) {
                if (isalpha(c)) {
                    int startIdx = variableIndex[c];
                    int len = lengths[c - 'a'];
                    for (int i = 0; i < len; i++) {
                        expanded.push_back(startIdx + i);
                    }
                } else {
                    if (c == '0' && hasZero) {
                        expanded.push_back(idx); // Map 0 to its index
                    } else if (c == '1' && hasOne) {
                        expanded.push_back(idx + (hasZero ? 1 : 0)); // Map 1 to its index
                    }
                }
            }
        };

        // Expand left and right sides
        expand(leftSide, leftExpanded);
        expand(rightSide, rightExpanded);

        // Step 3: Create edges based on the expanded representation
        for (int i = 0; i < leftExpanded.size(); i++) {
            int u = leftExpanded[i];
            int v = rightExpanded[i];
            adj[u].push_back(v);
            adj[v].push_back(u); // If the graph should be undirected
        }

        // Step 4: Transpose graph creation (for SCC finding)
        vector<vector<int>> transposed(totalVertices);
        for (int u = 0; u < totalVertices; u++) {
            for (int v : adj[u]) {
                transposed[v].push_back(u);
            }
        }

        // Step 5: Perform DFS to find SCCs
        stack<int> finishStack;
        vector<bool> visited(totalVertices, false);

        // Step 5.1: Perform DFS on the original graph to get finishing times
        for (int i = 0; i < totalVertices; i++) {
            if (!visited[i]) {
                DFS(i, adj, visited, finishStack);
            }
        }

        // Step 5.2: Perform DFS on the transposed graph to discover SCCs
        vector<vector<int>> SCCs;
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

        // Step 6: Output SCCs and calculate the number of solutions
        long long result = 1;
        for (const auto& scc : SCCs) {
            bool hasZeroInSCC = false, hasOneInSCC = false;
            cout << "SCC: ";
            for (int node : scc) {
                if (node < idx) {
                    for (const auto& [var, startIdx] : variableIndex) {
                        if (node >= startIdx && node < startIdx + lengths[var - 'a']) {
                            cout << var << (node - startIdx + 1) << " ";
                            break;
                        }
                    }
                } else {
                    if (hasZero && node == idx) {
                        cout << "0 ";
                        hasZeroInSCC = true;
                    } else if (hasOne && node == idx + (hasZero ? 1 : 0)) {
                        cout << "1 ";
                        hasOneInSCC = true;
                    }
                }
            }
            cout << "\n";
            if (!hasZeroInSCC && !hasOneInSCC) {
                result *= 2;
            } else if (hasZeroInSCC && hasOneInSCC) {
                result = 0; // If 0 and 1 are in the same SCC, no solution exists
                break;
            }
        }

        cout << result << "\n";
    }

    return 0;
}