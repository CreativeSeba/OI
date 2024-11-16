#include <bits/stdc++.h>

using namespace std;

const int S = 1 << 20, MAXV = 2 * S + 10;
int t[MAXV], pch[MAXV];

//działa tak samo jak w drzewo-przedział-przedział.cpp tylko zamiast sumowac wszystkie nody, to dodajemy tylko jedna wartosc i potem bierzemy rekurencyjnie maxa
void pchaj(int v, int p, int k) {
    t[v] += pch[v];//aktualizujemy wszystkie potrzebne wiezcholki
    if (p != k) { //sprawdzamy czy jestesmy na samym dole drzewa
        pch[v * 2] += pch[v], pch[v * 2 + 1] += pch[v];
    }
    pch[v] = 0;
}

void Insert(int v, int p, int k, int a, int b, int w) {
    pchaj(v, p, k); //pchaj jest po to wczesniej, aby zaktualizowac wartosi obu dzieci, bo musimmy miec accurate maxa, wiec nawet jak przedzial sie nie pokrywa, to i tak musimy zaktualizowac wartosci w sumie to nie ma znaczenia, bo nie musimy miec aktualnych informacji o obu synach
    if (k < a || p > b) {
        return;
    }
    if (a <= p && b >= k) {
        pch[v] += w;
        pchaj(v, p, k); //mamy zaległą wartość, więc musimy ją zaktualizować
        return;
    }
    Insert(v * 2, p, (p + k) / 2, a, b, w);
    Insert(v * 2 + 1, (p + k) / 2 + 1, k, a, b, w);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

int Query(int v, int p, int k, int a, int b) {
    pchaj(v, p, k);//mozemy miec nie wywolane aktualizacje wierzcholkow taka sama sytuacja jak w drzewo-przedział-przedział.cpp, tylko musimy wywolac pchaj przed warunkami, bo warunki maja returny a my musimy miec aktualne wartosci na obu dzieciach
    if (k < a || p > b) {
        return 0;
    }
    if (a <= p && k <= b) {
        return t[v];
    }
    return max(Query(v * 2, p, (p + k) / 2, a, b), Query(v * 2 + 1, (p + k) / 2 + 1, k, a, b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}