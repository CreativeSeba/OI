#include <bits/stdc++.h>

using namespace std;
const int S = 1 << 20;
int t[2 * S + 10];

void Insert(int pos, int w) {
    pos += S;
    t[pos] = w;
    pos /= 2;
    while (pos) {
        t[pos] = max(t[pos * 2], t[pos * 2 + 1]);
        pos /= 2;
    }
}

int Query(int a, int b) {
    a += S;
    b += S;
    int wynik = 0;
    while (a <= b) {
        if (a % 2 == 1) wynik = max(wynik, t[a++]);
        if (b % 2 == 0) wynik = max(wynik, t[b--]);
        a /= 2, b /= 2;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}