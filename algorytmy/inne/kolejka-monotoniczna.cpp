#include <iostream>
#include <vector>
#include <deque> // For deque
using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    vector<int> result; // To store the result
    deque<int> dq; // Deque to store indices of elements in nums

    for (int i = 0; i < nums.size(); i++) {
        // Step 1: Remove indices that are out of the bounds of the current window
        //sprawdza czy deque nie jest pusty i czy pierwszy element deque jest mniejszy od i - k + 1, czyli czy jest w oknie, jesli nie to usuwamy (pamietaj ze trzymamy indeksy)
        if (!dq.empty() && dq.front() < i - k + 1) { //i - k + 1 to
            dq.pop_front(); // Remove from the front if it's out of the current window
        }
        // Step 2: Remove elements from the back of the deque while nums[i] is greater
        //przesuwamy sie od tylu, usuwamy elementy, ktore sa mniejsze od obecnego, usuwamy indeksy, bo nie beda juz potrzebne, czyli ogolnie jest O(2n)
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back(); // Remove from back if the current element is greater
        }

        // Step 3: Add current index to the deque
        dq.push_back(i);

        // Step 4: Once we have processed the first k elements, we can start to add results
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]); // The front of the deque is the max for the current window
        }
    }

    return result; // Return the result containing max elements for each window
}

int main() {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> result = maxSlidingWindow(nums, k);

    cout << "The maximum elements in each sliding window of size " << k << " are: ";
    for (int max : result) {
        cout << max << " ";
    }
    cout << endl;

    return 0;
}
