#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f //ok 2^30, czyli mniejsze od MAX_INT, wiec nie bedzie bledow z dodawaniem

typedef pair<int, int> iPair;

//O((V+E)logV) VlogV - usuwanie, bo nie bierzemy pod uwage wierzchołków, które już odwiedziliśmy, ElogV - dodawanie, bo dla każdego wierzchołka sprawdzamy wszystkich sąsiadów
//log V, bo dodajemy odleglosci miedzy wierzchjolkami, a nie edge, np. moze byc C F - 10, miezy C i F jest np. 5, ale lacznie aby dojsc do F z C to 10. I nawet jesli w kolejce jest V^2, to i tak log V, bo log V^2, to 2logV, a ignorujemy stale wartosci, wiec log V

void addEdge(vector<iPair> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void printPath(vector<int> &parent, int j) {
    // Base Case : If j is source
    if (parent[j] == -1) {
        cout << j << " ";  // This is the source node
        return;
    }

    printPath(parent, parent[j]);
    cout << j << " ";
}

void shortestPath(vector<pair<int, int>> adj[], int V, int src, int dest) {
    // Min heap to store the vertices that are being preprocessed.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    // Distance and parent vectors
    vector<int> dist(V, INF);    // Stores shortest distance to each node
    vector<int> parent(V, -1);   // Stores the path (predecessor) for each node
    vector<bool> visited(V, false); // To mark visited nodes

    pq.push(make_pair(0, src));  // Push the source node with distance 0
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        // Go through all neighbors of u
        for (auto x: adj[u]) {
            int v = x.first;
            int weight = x.second;

            // If a shorter path to v is found
            if (!visited[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;  // Set the predecessor of v as u
            }
        }
    }
    cout<<"Vertex Distance from Source\n";
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << dist[i] << "\n";
    }
    // Printing shortest distance and the path to the destination node
    if (dist[dest] == INF) {
        cout << "No path exists from " << src << " to " << dest << "\n";
    } else {
        cout << "Shortest distance from " << src << " to " << dest << " is " << dist[dest] << "\n";
        cout << "Path: ";
        printPath(parent, dest);
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m, V;
    cin >> n >> m;
    V = n + 1;

    vector<iPair> adj[V];

    for(int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        addEdge(adj, u, v, wt);
    }

    int src = 1;
    int dest = n;
    shortestPath(adj, V, src, dest);  // Find shortest path from node src to dest

    return 0;
}
