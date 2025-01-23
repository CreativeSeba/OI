//https://codeforces.com/contest/1395/problem/C
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    /*To działa tak, że OR na c jest zawsze równy i, jeśli wszystkie OR elementów c z i równają się i, bo musi być chociaż jeden element, który
     sprawia że wcześniej operacja OR nie równała się i, czyli prowadzi to do tego, że zawsze jest jeden element, który ma te najważniejsze bity
     */
    //i jest zawsze większe od operacji AND, bo jeśli nie, to znaczy że ta większa liczba zamieni jeden bit 0 na 1, bo jest większa i nie będzie równa i
    //operacja OR nigdy nie usuwa bitów, tylko dodaje
    for (int i = 0; i < 512; i++) {
        bool check = true;
        for (int j = 0; j < n; j++) {
            //Operacja OR z i działa jak "maskowanie". Sprawdzamy, czy dany wynik a[j]&b[k] jest zgodny z i (czyli czy nie dodaje nowych bitów poza tymi, które są w i).
            //Jeśli i=511 (wszystkie bity od 0 do 8 ustawione, czyli 111111111), to każdy wynik a[j]&b[k] zawsze spełni warunek
            bool ase = false; // ase - a possible solution exists
            for (int k = 0; k < m; k++) {
                if (((a[j] & b[k]) | i) == i) {
                    ase = true;
                    break;
                }
            }
            // if one iteration over b doesn't find a solution, then there is no solution for i
            if (!ase) {
                check = false;
                break;
            }
        }
        if (check) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}