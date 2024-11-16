#include <bits/stdc++.h>

using namespace std;

int binary_search(const vector<int>& list, int goal) {
    int left = 0;
    int right = list.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        // Sprawdzamy, czy cel znajduje się na środku
        if (list[mid] == goal) {
            return mid;
        }
        // Jeśli cel jest większy, ignorujemy lewą połowę
        if (list[mid] < goal) {
            left = mid + 1;
        }
            // Jeśli cel jest mniejszy, ignorujemy prawą połowę
        else {
            right = mid - 1;
        }
    }
    // Zwracamy -1, jeśli element nie został znaleziony
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    vector<int> list = {2, 3, 4, 10, 40};
    int goal = 10;

    int result = binary_search(list, goal);

    if (result != -1) {
        cout << "Element znaleziony na indeksie: " << result << endl;
    } else {
        cout << "Element nie jest obecny w liście." << endl;
    }

    return 0;
}
