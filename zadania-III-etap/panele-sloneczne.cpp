//https://szkopul.edu.pl/problemset/problem/hzKdkq0maus68ExIKeHyERTJ/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

bool is_valid_multiple(int x, int min_val, int max_val) {
    //nie mozna dzielic przez 0
    if (x == 0) return false;
    // jeśli min_val / x != max_val / x, to oznacza ze należą do innych grup dzielenia, czyli x mieści gdzieś pomiędzy nimi
    // jeśli jeśli min_val / x == max_val / x, to oznacza, że ze należą do tej samej grupy dzielenia, czyli x nie mieści gdzieś pomiędzy nimi
    // min_val % x == 0, to jest specjalny przypadek gdy min_val / x == max_val / x, ale min_val jest podzielne przez x.
    // Nie musimy sprawdzac nigdy dodatkowo max_val % x == 0, bo jeśli min_val / x == max_val / x, to znaczy że max_val zostało zaokrąglone w dół
    return (min_val / x != max_val / x) || (min_val % x == 0);
}

int get_maximum_cell_size(tuple<int, int, int, int> limits) {
    auto [smin, smax, wmin, wmax] = limits;
    int max_side = 0;
    int sqrt_limit = sqrt(max(smax, wmax));

    for (int i = 1; i < sqrt_limit; i++) {
        // tu sprawdzamy mniejsze wartości w parach dzielników
        if (is_valid_multiple(i, smin, smax) && is_valid_multiple(i, wmin, wmax)) {
            max_side = max(max_side, i);
        }
        // tu sprawdzamy większe wartości w parach dzielników
        int candidate1 = smax / i;
        int candidate2 = wmax / i;

        if (is_valid_multiple(candidate1, smin, smax) && is_valid_multiple(candidate1, wmin, wmax)) {
            max_side = max(max_side, candidate1);
        }
        if (is_valid_multiple(candidate2, smin, smax) && is_valid_multiple(candidate2, wmin, wmax)) {
            max_side = max(max_side, candidate2);
        }
    }

    return max_side;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        tuple<int, int, int, int> limits;
        cin >> get<0>(limits) >> get<1>(limits) >> get<2>(limits) >> get<3>(limits);
        cout << get_maximum_cell_size(limits) << "\n";
    }

    return 0;
}
