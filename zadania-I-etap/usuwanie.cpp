#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    long long a, b;
    cin>>a>>b;
    long long trueCount = b - a + 1, wynik = 0;
    //sprawdzamy podzielność przez 4, bo zawsze możemy usunąć elementy po kolei jeśli ich ilość jest podzielna przez 4. Jeśli nie jest podzielna przez 4, to w zależności od reszty z dzielenia zostaje nam odpowiednio jeden lub dwa elementy, których nie możemy usunąć
    if(trueCount%4 == 0){
        wynik = trueCount;
    }
    else if(trueCount%4 == 1 || trueCount%4 == 3){
        wynik = trueCount - 1;
    }
    else if(trueCount%4 == 2){
        wynik = trueCount - 2;
    }

    cout<<wynik;

    return 0;
}

