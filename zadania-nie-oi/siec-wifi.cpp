//https://szkopul.edu.pl/problemset/problem/iKfCtavbe7p1LfYk2N_tRs2z/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

double binary_search(const vector<double>& acc, int n) {
    double left = 0, right = acc[acc.size() - 1] - acc[0]; // Inicjalizujemy zakres dla wyszukiwania binarnego
    double shortest = right;
    double epsilon = 1e-5; // Ustalamy tolerancję (epsilon), aby zakończyć wyszukiwanie binarne

    while (right - left > epsilon) { // Wyszukiwanie binarne aż do osiągnięcia wystarczającej precyzji
        double mid = left + (right - left) / 2.0; // Obliczamy środek zakresu (średnia)
        int usedAcc = 1; // Zaczynamy od pierwszego access pointu
        double currAcc = acc[0] + mid; // Pierwszy AP pokrywa klasy w promieniu `mid` wokół `acc[0]`

        // Pętla, która iteruje przez wszystkie klasy (poza pierwszą, bo już jest pokryta)
        for (int i = 1; i < acc.size(); i++) {
            // Sprawdzamy, czy obecna klasa `acc[i]` jest poza zasięgiem obecnego AP
            if (acc[i] - mid > currAcc) {
                usedAcc++; // Potrzebujemy nowego access pointu
                currAcc = acc[i] + mid; // Ustawiamy nowy AP na klasie `acc[i]` i ustawiamy jego zasięg
            }
        }

        // Jeśli liczba użytych access pointów przekroczyła dozwoloną liczbę `n`, to zasięg `mid` jest za mały
        if (usedAcc > n) {
            left = mid + epsilon; // Zwiększamy dolną granicę, szukamy większego zasięgu
        } else {
            right = mid - epsilon; // Zmniejszamy górną granicę, szukamy mniejszego zasięgu
            shortest = mid; // Zapamiętujemy najlepszy (minimalny) znaleziony zasięg
        }
    }
    return shortest; // Zwracamy minimalny zasięg, który spełnia warunki
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cout << fixed << setprecision(1);

    int test;
    cin >> test;
    while (test--) {
      //n - liczba access pointów, m - liczba klas
        int n, m;
        cin >> n >> m;
        //odleglosci miedzy klasami
        vector<double> acc(m);
        for (int i = 0; i < m; i++) {
            cin >> acc[i];
        }
        sort(acc.begin(), acc.end()); // Ensure access points are sorted
        double result = binary_search(acc, n);
        cout << result << endl; // Output the result
    }

    return 0;
}
