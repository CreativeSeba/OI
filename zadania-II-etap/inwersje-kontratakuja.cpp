//https://szkopul.edu.pl/problemset/problem/vD-GcD4yY2k7EfSETVEjDLbf/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

const int S = 1<<20;
int t[2*S+10];

void Insert(int pos, int w) {
    pos += S;
    t[pos] += w;
    pos /= 2;
    while (pos) {
        t[pos] = t[pos*2] + t[pos*2+1];
        pos /= 2;
    }
}

int Query(int a, int b) {
    a += S; b += S;
    int wynik = 0;
    while (a <= b) {
        if (a % 2 == 1) wynik += t[a++];
        if (b % 2 == 0) wynik += t[b--];
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin();
    }

    long long inversions = 0;
    for (int i = 0; i < n; i++) {
        inversions += Query(a[i] + 1, n - 1); //sprawdza ile jest elementów wiekszych od a[i] w prawo
        Insert(a[i], 1); //dodaje a[i] na pozycje rownej a[i]
    }

    cout << inversions << "\n";

    return 0;
}
