#include <bits/stdc++.h>

using namespace std;

double binary_search(const vector<double>& acc, int n) {
    double left = 0, right = acc[acc.size() - 1] - acc[0]; // Initialize range
    double shortest = right;
    double epsilon = 1e-5; // Set a reasonable epsilon

    while (right - left > epsilon) { // Using epsilon to check proximity
        double mid = left + (right - left) / 2.0;
        int usedAcc = 1;
        double currAcc = acc[0] + mid;

        for (int i = 1; i < acc.size(); i++) {
            if (acc[i] - mid > currAcc) {
                usedAcc++;
                currAcc = acc[i] + mid;
            }
        }

        // Debugging output
        //cout << "Used Access Points: " << usedAcc << " Mid: " << mid << " Left: " << left << " Right: " << right << endl;

        if (usedAcc > n) {
            left = mid + epsilon; // Move left beyond mid
        } else {
            right = mid - epsilon; // Move right below mid
            shortest = mid; // Update shortest found
        }
    }
    return shortest; // Return the shortest distance found
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(1);

    int test;
    cin >> test;
    while (test--) {
        int n, m;
        cin >> n >> m;
        vector<double> acc(m);
        for (int i = 0; i < m; i++) {
            cin >> acc[i];
        }
        sort(acc.begin(), acc.end()); // Ensure access points are sorted
        double result = binary_search(acc, n);
        cout << result << endl; // Output the result
    }

    return 0;
}
