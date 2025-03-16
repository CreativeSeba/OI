//https://szkopul.edu.pl/problemset/problem/Y2sHfxzqdwT7qKzabT0fzmlB/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

const int MAX_M = 1e6 + 5; // Górne ograniczenie dla M
const long long INF = 1e18; // Duża wartość do ograniczenia

//Dzięki tabeli ostatnia mamy czas O(MlogM), bo nawet jak mamy kilka takich samych ai, to nie odwiedzamy tych samych paczek i maksymalnie dla kazdego ai odwiedzimy M/ai paczek, czyli zawsze bedzie szereg harmoniczny
vector<long long> ostatnia(MAX_M, 0);  // Ostatnia zakupiona paczka dla danej wielokrotności
vector<bool> paczka(MAX_M, false);     // Czy dana paczka została kupiona?
vector<bool> bon(MAX_M, false);        // Czy w tej paczce znajduje się bon?

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int m;
    cin >> m;

    long long M = 0; // Maksymalny numer paczki z bonem
    vector<long long> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        bon[b[i]] = true;
        M = max(M, b[i]);
    }

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M = max(M, a[i]); // Upewniamy się, że nie rozpatrujemy paczek większych niż M
    }

    vector<long long> result;
    long long liczba_klientow = 0;

    for (int i = 0; i < n; i++) {
        long long p = a[i];
        long long akt = ostatnia[p] + p;
        long long uczestnik = 1;

        while (akt <= M && uczestnik <= p) {
            if (!paczka[akt]) {  // Sprawdzamy, czy paczka była już kupiona
                paczka[akt] = true;
                if (bon[akt]) {  // Jeśli paczka zawiera bon, zapisujemy numer klienta
                    result.push_back(liczba_klientow + uczestnik);
                }
                uczestnik++;
            }
            if (uczestnik <= p) {
                akt += p;  // Przechodzimy do kolejnej wielokrotności p
            }
        }

        ostatnia[p] = akt;  // Zapamiętujemy ostatnią zakupioną paczkę dla tego p
        liczba_klientow += p;  // Zwiększamy licznik klientów
    }

    // Wypisywanie wyniku
    cout << result.size() << "\n";
    for (long long x : result) {
        cout << x << "\n";
    }

    return 0;
}
