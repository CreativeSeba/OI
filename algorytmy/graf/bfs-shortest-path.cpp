#include <bits/stdc++.h>

using namespace std;

vector<int> reconstructPath(vector<int>& parent, int targetNode, int startNode){
    if(parent[targetNode] == -1 && targetNode != startNode) return {};

    vector<int> path;
    for(int node = targetNode; node != -1; node = parent[node]){
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

void reconstructPathRecursive(vector<int>& parent, int node, vector<int>& path, int startNode) {
    if (parent[node] == -1 && node != startNode) return;
    if(parent[node] == -1){
        path.push_back(node);
        return;
    }
    reconstructPathRecursive(parent, parent[node], path, startNode);
    path.push_back(node);
}

vector<int> bfs(int startNode, int targetNode, vector<vector<int>>& adj){
    int n = adj.size();

    vector<int> dist(n, -1), parent(n, -1);
    dist[startNode] = 0;

    queue<int> q;
    q.push(startNode);

    while(!q.empty()){
        int node = q.front();
        q.pop();
        if(node == targetNode) break;
        for(int adjacent : adj[node]){
            if(dist[adjacent] == -1){
                dist[adjacent] = dist[node] + 1;
                parent[adjacent] = node;
                q.push(adjacent);
            }
        }
    }

    for(int i = 0; i < n; i++){
        cout << dist[i] << " ";
    }
    return reconstructPath(parent, targetNode, startNode);
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }

    int startNode = 0, targetNode = n-1;
    vector<int> shortestPath = bfs(startNode, targetNode, adj);

    return 0;
}
