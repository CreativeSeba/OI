#include <bits/stdc++.h>

using namespace std;
const int S = 1 << 20; // Size for segment tree
pair<int, int> t[2 * S + 10]; // Segment tree array

pair<int, int> lacz(pair<int, int> s1, pair<int, int> s2) {
    if (s1.first == s2.first)
        return {s1.first, s1.second + s2.second};
    if (s1.second > s2.second)
        return {s1.first, s1.second - s2.second};
    else if (s1.second < s2.second)
        return {s2.first, s2.second - s1.second};
    else
        return {-1, 0};  // No dominant element
}

void build() {
    for (int i = S - 1; i > 0; i--) {
        t[i] = lacz(t[i * 2], t[i * 2 + 1]);
    }
}

pair<int, int> Query(int a, int b) {
    a += S; // Shift index to segment tree representation
    b += S;
    pair<int, int> wynik = {-1, 0};

    while (a <= b) {
        if (a % 2 == 1) {
            wynik = lacz(wynik, t[a]);
            a++;
        }
        if (b % 2 == 0) {
            wynik = lacz(wynik, t[b]);
            b--;
        }
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m, a, b;
    cin >> n >> m; // Read number of elements and queries

    // Initialize structures
    vector<pair<int, int>> sweep[n + 1]; // n + 1, bo potem b, bedzie b + 1, zeby sprawdzac czy to koniec przedzialu
    vector<int> counter(n, 0); // Count occurrences of each value
    vector<int> results(m, 0); // Store results for each query
    int queryPos[m]; // Track starting positions of queries
    pair<bool, int> queries[m]; // Store query status and count

    // Read input data and initialize the segment tree
    for (int i = 0; i < n; i++) {
        cin >> t[i + S].first;
        t[i + S].first--; // Convert to 0-based index
        t[i + S].second = 1; // Initialize the count of each element
    }

    build(); // Build the segment tree

    // Process each query
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--; // Convert to 0-based indexing
        queryPos[i] = a; // Store starting position of the query

        pair<int, int> ans = Query(a, b);
        if (ans.first == -1) // If no dominant element found
            continue;

        // Add query results to the sweep vector
        sweep[a].push_back({i, ans.first});
        sweep[b + 1].push_back({i, ans.first});

    }

    // Count results for each index
    for (int i = 0; i <= n; i++) {
        for (auto para : sweep[i]) {
            if (queries[para.first].first) { // If query was previously checked
                if (counter[para.second] - queries[para.first].second > (i - queryPos[para.first]) / 2)
                    results[para.first] = para.second + 1; // Store result for this query.
            } else {
                queries[para.first] = {true, counter[para.second]}; // Initialize query
            }
        }
        if (i < n) {
            counter[t[i + S].first]++; // Increment count for current value
        }
    }

    // Output the results for each query
    for (int i = 0; i < m; i++)
        cout << results[i] << "\n";


    return 0;
}

