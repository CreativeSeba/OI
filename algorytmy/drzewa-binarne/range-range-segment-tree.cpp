//przedzial-przedzial, oznacza, ze insert wykonujemy na przedziale i query na przedziale, a sum-sum, ze podczas insertu na przedziale wykonujmey sume, a podczas query tez sume
#include <bits/stdc++.h>

using namespace std;
const int S = 1 << 20, MAXV = 2 * S + 10; //1<<20, to binana operacja, mnozy 1 przez 2^20
int t[MAXV], pch[MAXV];
//pch[v] jest używane to przechowywania wartości do aktualizacji wierzchołków z kilku insertów
//pch[v] na początku zawsze jest rowne 0 dopiero jak warunek drugiego if w Insert jest spełniony to jest dodawane w
//funkcja pchaj działa dopiero jak robimy kilka insertow, pierwszy insert i pierwsze query nie wymaga jej użycia, bo nie ma nic do aktualizacji, aktualizujemy tylko wtedy, gdy jakis przedzial pokrywa sie czesciowo z a i b i nie wiemy, ktore jego dziecko pokrywa sie z a i b
//jeśli p i k nie zawiera sie w pelni w a i b to, pchaj dzieli przedzial na pol i wywoluje sie rekurencyjnie na obu polowach
//pchaj w Query jest po to, aby zaktualizować wartości wierzcholkow, ktore zostaly pominiete w Insert, a pomijane są, gdy spełniony jest warunek drugiego if w Insert
//a i b jest sprawdzane za pomocą p i k
//root node to suma wszystkiego
void pchaj(int v, int p, int k) {
    t[v * 2] += (k - p + 1) / 2 * pch[v];  // k-p+1 - liczba elementów w przedziale
    t[v * 2 + 1] += (k - p + 1) / 2 * pch[v];
    pch[2 * v] += pch[v], pch[2 * v + 1] += pch[v];
    pch[v] = 0; // nie chcemy wielokrotnie dodawać tej samej wartości
}

void Insert(int v, int p, int k, int a, int b, long long w) {
    if (b < p || a > k) {
        return;
    }
    if (a <= p && b >= k) { //sprawdzasz czy przedział [p,k] zawiera się w [a,b]
        pch[v] += w;
        t[v] += (k - p + 1) * w;
        return;
    }
    pchaj(v, p, k); //bierzemy pod uwage nakladajace sie przedzialy
    Insert(v * 2, p, (p + k) / 2, a, b, w);
    Insert(v * 2 + 1, (p + k) / 2 + 1, k, a, b, w);
    t[v] = t[v * 2] + t[v * 2 + 1]; //wywola sie dopiero jak wrocimy z rekurencji, czyli jak wszystkie inserty cos zwroca
}

long long Query(int v, int p, int k, int a, long long b) {
    if (b < p || a > k) {
        return 0;
    }
    if (a <= p && b >= k) {
        return t[v];
    }
    pchaj(v, p, k);//pchaj jest wykonywane na rodzicu, wiec jesli sie wierzcholek pokrywa w przedziale to juz rodzic mu wywolal pchaj
    return Query(v * 2, p, (p + k) / 2, a, b) + Query(v * 2 + 1, (p + k) / 2 + 1, k, a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int a, b;

    Insert(1, 0, S - 1, a, b, 1); //"tablica" zaczyna sie od 0, wiec ostatni element to S - 1. a, b, p i k nie odnosza sie do tablicy, tylko do przedzialow do tablicy odnosi sie v
    Query(1, 0, S - 1, 0, S - 1);
}