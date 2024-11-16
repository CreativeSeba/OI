#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

//    string inputFileName = "C:\\Users\\lagan\\Downloads\\sprocen\\spr\\in\\spr2ocen.in";
//    ifstream inputFile(inputFileName);

    int n;
    cin >> n;
    vector<int> a(n), b(n), result(n, 0);
    long long sumaBajtyna = 0, sumaBitek = 0;

    // Read values for Bajtyna and Biteka
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sumaBajtyna += a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        sumaBitek += b[i];
    }

    // Create a vector of pairs to hold the differences and indices
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++) {
        items[i] = {b[i] - a[i], i};  // Store the difference and original index
    }

    // Sort by difference (descending), then by index (ascending)
    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) {
            return a.second < b.second; // Sort by index if differences are equal
        }
        return a.first < b.first; // Sort by difference otherwise
    });

    // Precompute minimum values from the left for Bajtyna and right for Biteka
    vector<int> minBajtyna(n), minBitek(n);
    minBajtyna[0] = a[items[0].second];
    for (int i = 1; i < n; i++) {
        minBajtyna[i] = min(minBajtyna[i - 1], a[items[i].second]);
    }
    minBitek[n - 1] = b[items[n - 1].second];
    for (int i = n - 2; i >= 0; i--) {
        minBitek[i] = min(minBitek[i + 1], b[items[i].second]);
    }

    // Assignment of items
    long long bajtyna = sumaBajtyna, bitek = 0;
    for (int i = 0; i < n; i++) {
        int idx = items[i].second;  // Get the original index
        bajtyna -= a[idx];
        bitek += b[idx];

        // Check the jealousy conditions
        if (bajtyna >= sumaBajtyna - bajtyna - minBajtyna[i] &&
            bitek >= sumaBitek - bitek - minBitek[i + 1]) {
            result[idx] = 1;  // Assign to Bajtyna
            break;
        } else {
            result[idx] = 1;  // Assign to Biteka
        }
    }

    // Output results
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
