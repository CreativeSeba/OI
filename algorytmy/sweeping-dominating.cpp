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
    for (int i = S-1; i > 0; i--) { //S-1 bo to jest pierwszy wierzcholek, ktory nie jest lisciem, bo liscie sa od S do S + n-1
        t[i] = lacz(t[i * 2], t[i * 2 + 1]);// to są dzieci
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

    vector<pair<int, int>> sweep[n + 1]; // n + 1, bo potem b, bedzie b + 1, zeby sprawdzac czy to koniec przedzialu. sweep zawiera pare, gdzie indeks to "a" zapytaniam, pierwszy element to indeks zapytania w kolejnosci w ktorej wpisywalismy, a drugi to kandydat zapytania
    vector<int> counter(n, 0); //liczy wystapienia kazdej wartosci
    vector<int> results(m, 0); //wyniki dla kazdego zapytania
    int queryPos[m]; //poczatkowe pozycje zapytan, czyli "a"
    pair<bool, int> queries[m]; //status zapytania i licznik, jesli true to zapytanie sie skonczylo


    for (int i = 0; i < n; i++) {//zamieniamy na 0-indexed
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
        if (ans.first == -1) // nie dodajemy zapytania, bo nie ma dominujacego elementu, jesli nie wystepuje to po prostu bedzie 0, bo w counterze jest 0
            continue;

        sweep[a].push_back({i, ans.first});
        sweep[b + 1].push_back({i, ans.first}); //zakonczenie zapytania, nie bierzemy pod uwage b+1, bo to jest koniec przedzialu

    }
//para.first to indeks zapytania, a para.second to kandydat zapytania
    for (int i = 0; i <= n; i++) {
        for (auto para: sweep[i]) {
            if (queries[para.first].first) { // sprawdza czy zapytanie sie skonczylo, czyli czy jest b+1 (para.first to indeks zapytania)
                if (counter[para.second] - queries[para.first].second > (i - queryPos[para.first]) / 2) //i to b, queryPos to a
                    results[para.first] = para.second + 1; //para.second to kandydat zapytania, a para.first to indeks zapytania, czyli kolejnosc w ktorej wpisywalismy
            } else {
                queries[para.first] = {true, counter[para.second]}; // kiedy spotkamy a
            }
        }
        if (i < n) { //n to tak naprawde n+1, wiec dlatego i < n
            counter[t[i + S].first]++; //zwieksza nasz licznik o 1 kiedy przechodzimy od lewej do prawej
        }
    }


    for (int i = 0; i < m; i++) {
        cout << results[i] << "\n";
    }

    return 0;
}

