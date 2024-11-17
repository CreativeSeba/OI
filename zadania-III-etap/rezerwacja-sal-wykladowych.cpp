#include <bits/stdc++.h>

using namespace std;

// Binary search to find the rightmost lecture that ends before `start_time`
int binary_search(const vector<pair<int, int>> &list, int goal) {
    int left = 0;
    int right = list.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (list[mid].second <= goal) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;

    vector<pair<int, int>> t(n);
    vector<int> dp(n, 0);

    for (int i = 0; i < n; i++) {
        int p, k;
        cin >> p >> k;
        t[i] = {p, k};
    }

    // Sort lectures by end time (ascending)
    sort(t.begin(), t.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    for (int i = 0; i < n; ++i) {
        int r = t[i].second - t[i].first;

        // Find the last non-overlapping lecture
        int j = binary_search(t, t[i].first);

        // Update dp[i]
        //Jeśli j == -1, to znaczy, że nie ma żadnej lekcji, która kończy się przed t[i].first, czyli sprawdzamy czy wartość r jest większa od wartości w dp[i-1], jeśli tak to przypisujemy wartość r do dp[i], jeśli nie to przypisujemy wartość dp[i-1] do dp[i]
        //Jeśli prawa srona max jest wieksza to oznacza ze wklady przed sa krotsze i nie oplaca sie ich dodawac, wiec przekazujemy do dp[i] wartosc z dp[i-1]
        dp[i] = max((j == -1 ? 0 : dp[j]) + r, (i == 0 ? dp[i] : dp[i - 1]));
    }
    cout << dp[n - 1] << endl;

    return 0;
}
