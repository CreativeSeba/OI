#include <bits/stdc++.h>

using namespace std;

//nie moze byc tablicy, bo jakbys robil unie, to bys musial przepisywac wszystkie elementy, jakby zmieniac rodzica wszystkich elelnmtow i to by bylo O(n)

const int MAX = 1e6 - 1;  // Maximum number of nodes
int root[MAX], nodeRank[MAX];
pair <pair<long long, int>, pair<int, int >> p[MAX];  // jesli chcesz sam koszt to usun pierwsza pare i zmien na long long, bo int to indeksy wierzcholka przed sortowaniem
vector<int> mstEdges;  // Vector to store the indices of edges in the MST

// Find the parent with path compression
//path compresion wywoluje sie tylko raz, bo jak raz sie wywola to juz bedzie rootem i wywoluje sie tylko podczas wywolywania union, nie po operacji, tylko na poczatku
//path compreswion nie dziala dla calego disjoint set, tylko dla jednego elementu(tego o ktorego root sie pytamy), bo jakby dla calego to bys musial przepisac wszystkie elementy, a tak to tylko dla jednego
//reukrencja maksymalnie, zajmuje 4 operacje (funkcja akermana)

//CZAS ZAMORTYZOWANY
int parent(int a) {
    if (root[a] != a) { //tylko sie wywoluje kiedy a nie jest rootem
        root[a] = parent(root[a]);  // Path compression
    }
    return root[a];
}

// Union by nodeRank
void union_find(int a, int b) {
    int rootA = parent(a);
    int rootB = parent(b);

    if (rootA != rootB) {
        // Union by nodeRank: attach smaller tree under larger one
        if (nodeRank[rootA] < nodeRank[rootB]) {
            root[rootA] = rootB;
        } else if (nodeRank[rootA] > nodeRank[rootB]) {
            root[rootB] = rootA;
        } else {
            root[rootB] = rootA;
            nodeRank[rootA]++;  // Increase nodeRank if both have the same nodeRank
        }
    }
}

long long kruskal(int edges, int nodes) {
    long long minCost = 0;
    sort(p, p + edges);
    for (int i = 0; i < nodes; ++i) {
        root[i] = i;       // Each node is its own parent
        nodeRank[i] = 0;   // Initially, all ranks are 0
    }
    for (int i = 0; i < edges; ++i) {
        int a = p[i].second.first;  // First node
        int b = p[i].second.second;  // Second node
        long long cost = p[i].first.first; // Edge weight

        if (parent(a) != parent(b)) {  // Only select edge if it does not create a cycle
            minCost += cost;            // Update total cost of MST
            mstEdges.push_back(p[i].first.second);      // Store the index of the included edge
            union_find(a, b);           // Union the sets
        }
    }
    return minCost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long long minCost;
    int n, m; // Number of nodes and edges
    cin >> n >> m;  // Read number of nodes and edges

    // Read edges and their weights
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;  // Input format: node1 node2 weight
        p[i] = make_pair(make_pair(c, i), make_pair(a, b));  // Store edges
    }
    // Sort edges by weight

    // Run Kruskal's algorithm to find the minimum spanning tree cost
    minCost = kruskal(m, n);
    cout << "Minimum cost of the MST: " << minCost << endl;
    cout << "Edges in the MST:\n";
    for (int index: mstEdges) {
        cout << index + 1 << endl;  // Convert back to 1-based indexing for output
    }
    cout << endl;

    return 0;
}

