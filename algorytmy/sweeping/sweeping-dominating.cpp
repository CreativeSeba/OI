#include <bits/stdc++.h>

using namespace std;
const int S = 1 << 20;
pair<int, int> t[2 * S + 10];

pair<int, int> lacz(pair<int, int> s1, pair<int, int> s2) {
    if (s1.first == s2.first)
        return {s1.first, s1.second + s2.second};
    if (s1.second > s2.second)
        return {s1.first, s1.second - s2.second};
    else if (s1.second < s2.second)
        return {s2.first, s2.second - s1.second};
    else
        return {-1, 0};
}

void build() {
    for (int i = S - 1;
         i > 0; i--) { // S-1 bo to jest pierwszy wierzcholek, ktory nie jest lisciem, bo liscie sa od S do S + n-1
        t[i] = lacz(t[i * 2], t[i * 2 + 1]); // to są dzieci
    }
}

pair<int, int> Query(int a, int b) {
    a += S;
    b += S;
    pair<int, int> wynik = {-1, 0};

    while (a <= b) {
        if (a % 2 == 1) {
            wynik = lacz(wynik, t[a]);
            a++;
        }
        if (b % 2 == 0) {
            wynik = lacz(wynik, t[b]);
            b--;
        }
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m, a, b;
    cin >> n >> m;

    vector<pair<int, int>> otw[n], zam[n];
    vector<int> counter(n, 0); // liczy wystapienia kazdej wartosci
    vector<int> results(m, 0); // wyniki dla kazdego zapytania
    int queryPos[m]; // poczatkowe pozycje zapytan, czyli "a"
    int queries[m]; // status zapytania i licznik

    for (int i = 0; i < n; i++) { // zamieniamy na 0-indexed
        cin >> t[i + S].first;
        t[i + S].first--;
        t[i + S].second = 1;
    }

    build();

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--;
        queryPos[i] = a;

        pair<int, int> ans = Query(a, b);
        if (ans.first == -1) {// nie dodajemy zapytania, bo nie ma dominujacego elementu, jesli nie wystepuje to po prostu bedzie 0, bo w counterze jest 0
            continue;
        }
        otw[a].push_back({i, ans.first}); // początek zdarzenia dla zapytania
        zam[b].push_back({i, ans.first}); // zakonczenie zapytania
    }

    // sweeping dominating się rozni od tego w sweeping, bo tu przy okazji zliczamy wystapienia DANEGO elementu na tablicy, w ukladzie wspolrzednych elementy to punkty a wiec wszystkie maja wartosc 1

    // CZAS ZAMORTYZOWANY
    for (int i = 0; i < n; i++) {
        for (auto para: otw[i]) { // obsługa początków przedziałów
            queries[para.first] = counter[para.second]; // kiedy spotkamy a
        }
        //liczymy ile jest wystpaien po otw, bo queries ptrzetrymuje ilosc wystpien do otw, czyli bez pierwszego elelmntu, dopiero zam zlicza calosc, odejmuac to ile bylo przed rozpoczeciem przedzialu
        counter[t[i + S].first]++; // zwieksza nasz licznik o 1 kiedy przechodzimy od lewej do prawej
        for (auto para : zam[i]) { // obsługa końców przedziałów
            if (counter[para.second] - queries[para.first] > (i - queryPos[para.first] + 1)/ 2) { // i to b, queryPos to a. i - queryPos[para.first] + 1) / 2 jest to liczba elementow w przedziale, czyli ile jest elementow w przedziale. w nawiasie jest +1 bo dzielenie przez 2 zaokragla w dol, wiec jak sa nieparzyste to by byly zle wyniki
                results[para.first] = para.second + 1; // para.second is the candidate
            }
        }
    }

    for (int i = 0; i < m; i++) {
        cout << results[i] << "\n";
    }

    return 0;
}
