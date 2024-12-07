//https://szkopul.edu.pl/problemset/problem/C-avIJ9h36gThNQUOeaYwAD9/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int j = 0;
    for (int i = 0; i < n; i += 2) {
        b[i] = a[j];
        b[i + 1] = a[n - j - 1];
        j++;
    }
    int wynik = 0;
    for (int i = 0; i < n; i++) {
        wynik += b[i];
    }
    for (int i = 0; i < n; i++) {
        wynik += max(0, b[i + 1] - b[i]);
    }
    cout << wynik << endl;
    return 0;
}
