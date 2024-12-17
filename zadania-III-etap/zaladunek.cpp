//https://szkopul.edu.pl/problemset/problem/tbAODT0mS1ZwmNfteVw6W8JZ/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, s;
    cin >> n >> s;

    vector<long long> t(n + 1);      // Czasy przyjazdów pociągów
    vector<long long> dp(n + 1, INF); // Tablica dp, początkowo ustawiona na INF

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    // Zabezpiecz, by czasy przyjazdów były unikalne (pociągi nie mogą wyruszać w tym samym czasie)
    for (int i = 2; i <= n; i++) {
        if (t[i - 1] >= t[i]) {
            t[i] = t[i - 1] + 1;
        }
    }

    dp[0] = 0;  // Inicjalizacja dp dla początkowego pociągu
    int lk = 0;  // pociąg, który skonczyl trase przed i-tym pociagiem, pociag, ktory sie nie pokrywa w zaden sposob z i-tym. lk dzieli pociagi na grupy, w ktorych moga jechac razem

    //CZAS ZAMORTYZOWANY O(n)
    for (int i = 1; i <= n; i++) {
        int ilepociagow = i - lk - 1;  // Liczba pociągów między aktualnym a ostatnim, odejmujemy 1, zeby nie liczyć obecnego pociagu
        // Czas zamortyzowany, bo musimy miec dla kazdego obliczony najlepszy czas, dlatego przerywamy petle jak juz tego czasu nie ma
        while (lk < i) {
            //jeśli dp[lk] + ilepociagow jest większe od t[i], to daltego dodajemy jeszcze raz ilepociagow, bo pociągi muszą na siebie jeszcze czekać na dole
            //jesli dp[lk] + ilepociagow jest wieksze, to znaczy ze i-ty pociag musi poczekac na pociagi, ktore juz wyruszyly, jesli t[i] jest wieksze, to znaczy ze i-ty pociag moze wyruszyc od razu
            long long czasPowrotu = max(dp[lk] + ilepociagow, t[i]) + ilepociagow + 2 * s; //bierzemy maxa miedzy czasem powrotu ostatniego pociagu i czasem przyjazdu obecnego pociagu, aby nie było sytuacji, ze pociag przyjedzie przed tymi ktore wystartowaly przed nim

            // Jeśli znaleźliśmy lepszy czas powrotu, aktualizujemy dp[i]
            // zawsze wykona sie przynajmniej raz, bo dp[i] = INF, a czasPowrotu jest zawsze mniejszy od INF
            if (czasPowrotu < dp[i]) {
                dp[i] = czasPowrotu;
                lk++;
                ilepociagow--;  // Zmniejsz liczbę oczekujących pociągów
            } else { // Jeśli nie znaleźliśmy lepszego czasu powrotu od ostatniego, to przerywamy pętlę
                break;
            }
        }
        lk--; // jeśli w petli while warunek w if-ie nie zostanie spelniony, to mamy zinkrementowane lk, które nie ma najlepszego czasu powrotu
    }

    cout << dp[n] << endl;  // Minimalny czas powrotu ostatniego pociągu
    return 0;
}
