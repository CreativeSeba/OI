//https://szkopul.edu.pl/problemset/problem/VZifqMhw2OhTWnQqv7mC5Cge/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;

    vector<int> row(n, 0);
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        // Insert rows
        for (int j = 0; j < n; j++) {
            int cell;
            cin >> cell;
            if (cell == 0) {
                row[j] += 1;
            } else {
                row[j] = 0;
            }
        }
        // Compute max area using max monotonic queue on histogram (row)
        // row[j] is height of a histogram (rectangle)
        deque<int> q;
        for (int j = 0; j < n; j++) {
            while (!q.empty() && row[q.back()] > row[j]) {
                int height = row[q.back()];
                q.pop_back();
                int width;
                if (q.empty()) {
                    width = j;
                } else {
                    // calculate rectangle width, from last element in queue to current element
                    width = j - q.back() - 1;
                }
                maxArea = max(maxArea, height * width);
            }
            q.push_back(j);
        }
        // Process remaining heights in the deque
        // It happens when there are multiple elements of the same height, when the biggest element is at the end (always), or when there are smaller values that werent overriden by any bigger ones
        // Here we check the elements that their biggest rectangle is to the end of the row, becuse they werent overriden so there wasnt any value that would limit their heights
        while (!q.empty()) {
            int height = row[q.back()];
            q.pop_back();
            int width;
            if (q.empty()) {
                width = n;
            } else {
                //calculate rectangle width, from last element in queue to end of row
                width = n - q.back() - 1;
            }
            maxArea = max(maxArea, height * width);
        }
    }
    cout << maxArea;
    return 0;
}
