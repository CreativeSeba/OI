//O((V+E)logV) VlogV - usuwanie, bo nie bierzemy pod uwage wierzchołków, które już odwiedziliśmy, ElogV - dodawanie, bo dla każdego wierzchołka sprawdzamy wszystkich sąsiadów
//log V, bo dodajemy odleglosci miedzy wierzchjolkami, a nie edge, np. moze byc C F - 10, miezy C i F jest np. 5, ale lacznie aby dojsc do F z C to 10. I nawet jesli w kolejce jest V^2, to i tak log V, bo log V^2, to 2logV, a ignorujemy stale wartosci, wiec log V

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;

vector<int> path_iter(vector<int> &parent, int targetNode, int startNode) {
    if (parent[targetNode] == -1 && targetNode != startNode) return {};

    vector<int> path;
    for (int node = targetNode; node != -1; node = parent[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

void path_rec(vector<int> &parent, int node, int startNode, vector<int> &path) {
    if (parent[node] == -1 && node != startNode) return;
    if (parent[node] == -1) {
        path.push_back(node);
        return;
    }
    path_rec(parent, parent[node], startNode, path);
    path.push_back(node);
}

vector<int> dijkstra(int startNode, int targetNode, vector<vector<iPair> > &adj) {
    int n = adj.size();

    vector<int> dist(n, INT_MAX), parent(n, -1);
    dist[startNode] = 0;

    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    pq.emplace(0, startNode);

    while (!pq.empty()) {
        int node = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (node == targetNode) break;
        //we cant use >=, because the problem lies in the fact,
        //that in protiy queue we basically store the same distance as dist[node], and we wont almost every time perform 'bfs' from that node, so currentDist will be always equal to dist[node]
        //in the for loop below we make sure that we dont add any duplicates to the priority queue
        if (currentDist > dist[node]) continue;

        for (auto adjacent: adj[node]) {
            int v = adjacent.first;
            int w = adjacent.second;

            if (dist[v] > dist[node] + w) {
                dist[v] = dist[node] + w;
                pq.emplace(dist[v], v);
                parent[v] = node;
            }
        }
    }

    return path_iter(parent, targetNode, startNode);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<iPair> > adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int startNode = 0, targetNode = n - 1;
    vector<int> shortestPath = dijkstra(startNode, targetNode, adj);

    return 0;
}
