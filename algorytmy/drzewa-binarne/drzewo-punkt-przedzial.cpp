#include <bits/stdc++.h>
using namespace std;

const int S = 1<<20;
int t[2*S+10];

void Insert(int pos, int w) {
    pos += S;
    t[pos] += w;
    pos /= 2;
    while (pos) {  //pos jest zero kiedy jest jeden, bo 1/2 = 0, bo jest intem
        t[pos] = t[pos*2] + t[pos*2+1];
        pos /= 2;
    }
}

int Query(int a, int b) {
    a += S;
    b += S;  // a i b sa sprawdzane poprzez dodwanie S
    int wynik = 0;
    while (a <= b) {
        if (a % 2 == 1) wynik += t[a++]; // jesli a jest prawym dzieckiem to dodajemy jego wartosc i idziemy w prawo, dlatego jesli pokrywa przedzial to przechodzimy na strone b i potem sie rown b i sie konczy petla
        if (b % 2 == 0) wynik += t[b--]; // jesli b jest lewym dzieckiem to sie zmniejsza o jeden dlatego jak, a sie zwikszy i b sie zmniejszy to sie konczy petla
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int a, b;
    Insert(a, 6);
    Insert(b, 7);
    Query(a, b);
}