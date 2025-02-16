//https://szkopul.edu.pl/problemset/problem/aKBekEIo5lK0oSLz2UF4F_d9/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    vector<int> b(n);

    for (int i = 0; i < 2*n; i++) {
        if (i<n) {
            cin >> a[i].first;
            a[i].second = i;
        } else {
            cin >> b[i-n];
        }
    }

    sort(a.rbegin(), a.rend());

    vector<int> result(n);

    //algorytm zachłanny (3 podzadanie):
    //Każde ai = bi, skoro Bitek miał mniej i dajemy mu aktualnie najmniejsy przedmiot, to Bajtyna mu i tak nie zazdrości, bo nie liczymy tego przedmiotu dla Bajtyny.
    //Ten algorytm w dalszych podzadaniach służy do wyznaczania przydzielenia przedmiotów dla Bajtyny, ponieważ można je zamienić z przedmiotami Bitka, i to nic nie zmieni, bo zamieniają się tylko osoby i zamiana nie ma wpływu na zazdrość, bo bitek nie zazdrościł Bajtynie i Bajtyna Bitkowi
    long long sum_bajtyna = 0, sum_bitek = 0;
    for (int i = 0; i < n; i++) {
        if (sum_bajtyna <= sum_bitek) {
            sum_bajtyna += a[i].first;
            result[a[i].second] = 0;
        } else {
            sum_bitek += a[i].first;
            result[a[i].second] = 1;
        }
    }

    //Teraz mając pewność, że jak zamienimy przedmioty Bitka z przedmiotami Bajtyny, to Bajtyna nie zacznie zazdrościć Bitkowi, więc możemy sprawdzić czy Bitek zazdrości Bajtynie według jego wartości, i jeśli tak, to zamieniamy przedmioty między nimi, bo skoro Bitek miał według jego wartości mniej, to Bajtyna według jego wartościmiała więcej
    long long bitek_check = 0, bajtyna_check = 0, bajtyna_min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (result[i] == 1) {
            bitek_check += b[i];
        } else {
            bajtyna_check += b[i];
            bajtyna_min = min(bajtyna_min, b[i]*1LL);
        }
    }
    //Zamiana przedmiotów między Bitkiem i Bajtyną, jeśli suma przedmitow dla Bitka, po przydzieleniu wedlug Bajtyny jest mniejsza od przedmiotw Najtyny wedlug Bitka odjąc najmniejszy przedmiot Bajtyny według Bitka
    if (bitek_check < bajtyna_check  - bajtyna_min) {
        for (int i = 0; i < n; i++) {
            if (result[i] == 1) {
                result[i] = 0;
            } else {
                result[i] = 1;
            }
        }
    }

    for (int entry : result) {
        cout << entry << " ";
    }
    return 0;
}

