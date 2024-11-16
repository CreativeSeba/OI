#include <bits/stdc++.h>

using namespace std;

const int S = 1 << 20, MAXV = 2 * S + 10;
int t[MAXV], pch[MAXV], s, w, n;
const int MAXN = 1e5;

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
    cin.tie(0), cout.tie(0);

    cin >> s >> w >> n;
    vector<pair<int, int>> otw[MAXN], zam[MAXN+s];
    // Wczytywanie współrzędnych i normalizacja
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        otw[x].push_back({y, y + w});  // Dodawanie par (y, y + w)
        zam[x + s].push_back({y, y + w});
    }

    int maxValue = 0;  // Maksymalna liczba samorodków
    // Obsługa drzewa przedziałowego

    //sweeping sie rozni od tego w sweeping-dominating, bo tutaj tylko robimy zwykłe +1, -1 i wykorzystujemy go z drzewem przedzialowym, wlasnie dlatego ze dodajemy jedynki, dzieki temu mozemy szybko znajdywac max, albo min.
    //uzywamy go w ukladach 2D, gdzie mamy jakies zdarzenia, ktore sie przecinaja, jakies punkty, nie musimy niczego zliczac, tylko liczymy ile jest wystpaien do pewnego momentu i odejmujemy 1, dzieki temu mozemy policzyc np. ile maksymalnie punktow miesci sie w prostokacie
    //ogolnie sweepingu sie uzywa tylko do zliczania czegos, tzn nie zliczamy wszystkiego, bo to nie ma sensu, zliczamy cos konkretnego.
    //sweeping zawsze działa z jakąs inna strukturą, najczesciej drzewem przedziałowym

    //CZAS ZAMORTYZOWANY
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