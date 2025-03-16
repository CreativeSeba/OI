#include <bits/stdc++.h>

using namespace std;

int binarySearch(vector<int>& arr, int goal) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == goal) {
            return mid;
        }
        //we need to add one and subtract one, becuase the loop wont end, becuase it will be stuck on the equal element
        //we also need this, becuase we dont need to check the mid element, becuase we have already checkes if it is the goal in the if statement above
        if (arr[mid] < goal) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Element not found
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    int goal;
    cin >> goal;

    int result = binarySearch(arr, goal);
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}
