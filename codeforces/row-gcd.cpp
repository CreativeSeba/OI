//https://codeforces.com/contest/1459/problem/C
#include <bits/stdc++.h>

using namespace std;

//x%y = x - y*(x/y) - mnożymy przez y, bo x/y to to ile y zmiesci sie w x, wiec y*(x/y), to najwiekszy iloczyn y jaki zmiesci sie w x

//Zaluzmy ze a>b (To nic nie zmienia, latwiej zrozumiec)
//NWD(a, b) = NWD(b, a%b) = NWD(a, a-b)
//NWD(b, a%b)- to dziala, bo b to jest mniejsza liczba z poprzedniego wywolania gcd (bo patrzymy ile razy zmiesci sie mniejsza w wiekszej), a a%b to jest reszta z dzielenia z tez poprzedniego wywolania
//NWD(a, a-b) - to działa, bo zaluzmy ze g to jest NWD dla a i b, to a=g*k1, b=g*k2, czyli a-b=g*k2-g*k1=g*(k2-k1), czyli g jest dzielnikiem a-b

// Mozna to obliczyc na dwa sposoby:

//1. Odejmujac a[0]
//a1+bj zostaje z przodu, bo nie ma co odejmowac, dlatego nie objemujemy tego w base
//Tutaj odejmujemy a[0] od wszystkich elementow (tak jakby takie duze NWD(a, a-b))
//NWD(a1+bj, a2+bj, a3+bj, a4+bj, a5+bj) = NWD(a1+bj, (a2+bj)-(a1+bj), (a3+bj)-(a1+bj), (a4+bj)-(a1+bj), (a5+bj)-(a1+bj))
//NWD(a1+bj, a2+bj, a3+bj, a4+bj, a5+bj) = NWD(a1+bj, a2-a1, a3-a1, a4-a1, a5-a1)

//2. Odejmujac a[i-1]
//NWD(a1+bj, a2+bj, a3+bj, a4+bj, a5+bj) = NWD(a1+bj, (a2+bj)-(a1+bj), (a3+bj)-(a2+bj), (a4+bj)-(a3+bj), (a5+bj)-(a4+bj))
//NWD(a1+bj, a2+bj, a3+bj, a4+bj, a5+bj) = NWD(a1+bj, a2-a1, a3-a2, a4-a3, a5-a4)

//NWD(a1, a2, a3, a4, a5) = NWD(NWD(NWD(a1, a2), NWD(a3, a4)), a5)
//NWD(a1, a2, a3, a4) = NWD(NWD(NWD(a1, a1-a2), NWD(a2, a3-2))NWD(a3, a4-a3))
//NWD(a1, a2, a3, a4, a5) = NWD(a1, a2-a1, a3-a2, a4-a3, a5-a4)
//NWD(a1, a2-a1) = a  NWD(a, a3-a2) = b  NWD(b, a4-a3) = c  NWD(c, a5-a4) = d   base=d

//Wazne jest to aby nie pomijac zadnych liczb (kazde a musi byc uwzglednione w conajmniej jednej operacji odejmowania, bo jesli tego nie zrobimy to wtedy to a nie bedzie mialo wpływu na NWD)
//Powyższe złożone NWD(duzo argumentow) działają, bo zawsze na poczatku jest to a1, ktore niczego nie odejmuje, czyli w NWD(a1, a2, a3, a4, a5), tak jakby tym a-b, sa wszystkie elementy oprocz pierwszego elementu (a1)
//Widzimy ze w obu przypdkach jest pewna stała, ktora nazywamy base, i to co zostaje to a1+bj, wiec wynik to NWD(base, a1+bj)

long long calculateBase(const vector<long long>& a) {
    //tu liczymy pierwszy element, czyli i=1(bo i=0 nie zawiera sie w base, liczymy nizej)
    long long base = abs(a[1] - a[0]);
    //tu liczymy reszte elementow od i=2, bo i=1 juz policzylismy
    for (size_t i = 2; i < a.size(); ++i) {
        base = gcd(base, abs(a[i] - a[0]));
    }
    return base;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<long long> a(n), b(m);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    //Jesli n=1, to mamy tylko jedna a, wiec NWD(a1+bj)
    if (n == 1) {
        for (long long i = 0; i < m; ++i) {
            cout << a[0] + b[i] << ' ';
        }
        cout << '\n';
        return 0;
    }

    long long base = calculateBase(a);

    for (long long i = 0; i < m; ++i) {
        cout << gcd(base, a[0] + b[i]) << ' ';
    }
    cout << '\n';

    return 0;
}
