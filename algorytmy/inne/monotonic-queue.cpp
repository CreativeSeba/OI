#include <bits/stdc++.h>

using namespace std;

//decreasing monotonic queue
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    vector<int> result; // To store the result
    deque<int> dq; // Deque to store indices of elements in nums

    for (int i = 0; i < nums.size(); i++) {
        //sprawdza czy deque nie jest pusty i czy pierwszy element deque jest mniejszy od i - k + 1, czyli czy jest w oknie, jesli nie to usuwamy (pamietaj ze trzymamy indeksy)
        if (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front(); // Remove from the front if it's out of the current window
        }
        //przesuwamy sie od tylu, usuwamy elementy, ktore sa mniejsze od obecnego, usuwamy indeksy, bo nie beda juz potrzebne, czyli ogolnie jest O(2n)
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back(); // Remove from back if the current element is greater
        }
        dq.push_back(i);

        //jesli i >= k - 1 to dodajemy do wyniku maksymalny element w oknie, bo najpierw jak i jest mneijsze to musimy przejsc przez cale okno, a jak jest wieksze to co kazda iteracje usuwamy jeden element, wiec mozna od razu dodac do wyniku po petli while
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

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
