//https://szkopul.edu.pl/problemset/problem/TYf8i2qvrGI0l8QHEYJXO5dG/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

const int S = 1 << 20, MAXV = 2 * S + 10;
int t[MAXV], pch[MAXV], s, w, n;
const int MAX_COORD = 30010;
const int MAXN = 2 * MAX_COORD;

void Pchaj(int v, int p, int k) {
    t[v] += pch[v];
    if (p != k)
        pch[v * 2] += pch[v], pch[v * 2 + 1] += pch[v];
    pch[v] = 0;
}

void Insert(int v, int p, int k, int a, int b, int w) {
    Pchaj(v, p, k);
    if (k < a || p > b)
        return;
    if (a <= p && k <= b) {
        pch[v] += w;
        Pchaj(v, p, k);
        return;
    }
    Insert(v * 2, p, (p + k) / 2, a, b, w);
    Insert(v * 2 + 1, (p + k) / 2 + 1, k, a, b, w);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

int Query(int v, int p, int k, int a, int b) {
    Pchaj(v, p, k);
    if (k < a || p > b)
        return 0;
    if (a <= p && k <= b)
        return t[v];
    return max(Query(v * 2, p, (p + k) / 2, a, b), Query(v * 2 + 1, (p + k) / 2 + 1, k, a, b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> s >> w >> n;
    vector<pair<int, int>> otw[MAXN], zam[MAXN+s];
    // Wczytywanie współrzędnych i normalizacja
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x += MAX_COORD;  // Normalizacja współrzędnych x
        y += MAX_COORD;  // Normalizacja współrzędnych y
        otw[x].push_back({y, y + w});  // Dodawanie par (y, y + w)
        zam[x + s].push_back({y, y + w});
    }

    int maxValue = 0;  // Maksymalna liczba samorodków
    // Obsługa drzewa przedziałowego

    for (int i = 0; i < MAXN; i++) {
        for (auto &p : otw[i]) {
            Insert(1, 0, S - 1, p.first, p.second, 1);
        }

        maxValue = max(maxValue, Query(1, 0, S - 1, 0, S - 1));  // Zapisywanie maksymalnej wartości

        for (auto &p : zam[i]) {
            Insert(1, 0, S - 1, p.first, p.second, -1);
        }
    }

    cout << maxValue << "\n";

    return 0;
}