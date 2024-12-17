#include <bits/stdc++.h>

using namespace std;

void merge(vector<int>& arr, vector<int>& L, vector<int>& R, int left, int right) {
    int i = 0, j = 0, k = 0;

    // Łączenie dwóch tablic: L (lewa) i R (prawa) w arr
    //Jeśli j jest mniejsze od right, to dodajemy element z R do arr i zwiększamy j, jesli i jest mniejsze od right, to dodajemy element z L do arr i zwiększamy i
    while (i < left && j < right) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Przenoszenie pozostałych elementów z lewej tablicy, jeśli jakieś są
    while (i < left) {
        arr[k++] = L[i++];
    }

    // Przenoszenie pozostałych elementów z prawej tablicy, jeśli jakieś są
    while (j < right) {
        arr[k++] = R[j++];
    }
}

void mergeSort(vector<int>& arr) {
    if (arr.size() < 2) return;

    int middle = arr.size() / 2;

    vector<int> L(arr.begin(), arr.begin() + middle);
    vector<int> R(arr.begin() + middle, arr.end());

    mergeSort(L);
    mergeSort(R);

    merge(arr, L, R, L.size(), R.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Unsorted array:" << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    mergeSort(arr);

    cout << "Sorted array:" << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
