//https://codeforces.com/contest/1649/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll calculateManhattanSum(vector<ll>& positions) {
    //nie musimy robić wartości bezwzględnej, bo po sortowaniu mamy zawsze rosnące wartości
    sort(positions.begin(), positions.end());
    ll sum = 0, sum_before = 0, count_before = 0;

    for (ll i = 0; i < positions.size(); i++) {
        //mnozymy przez count_before, bo musimy znalezc sume odleglosci miedzy wszystkimi punktami i odejmujemy sum-before, bo sum_before to suma prefiksowa odleglosci wczsniejszych punktow, a wiec jesli ja odejmiemy to zostanie nam suma odleglosci od i-tego punktu do wszystkich poprzednich punktow
        //nie musimy liczyc odleglosci 'ponizej' i-tego punktu, bo one zostana policzone w kolejnych iteracjach
        //count_before * positions[i] jest jak x1, a sum before jest jak x2 (|x1-x2|)
        //zaluzmy ze mamy |x1-x2| + |x1-x3| + |x1-x4|, skoro x1 jest wieksze od x2,x3,x4 to x1-x2 + x1-x3 + x1-x4 = 3x1 - x2 - x3 - x4   3x1 to count before, a druga czesc rownania to sum_before
        sum += count_before * positions[i] - sum_before;
        //prefix sum
        sum_before += positions[i];
        count_before++;
    }

    return sum;
}

ll calculateTotalDistance(unordered_map<ll, vector<ll>>& colorPositions) {
    ll totalSum = 0;

    for (auto& entry : colorPositions) {
        totalSum += calculateManhattanSum(entry.second);
    }

    return totalSum;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    unordered_map<ll, vector<ll>> colorRowPositions, colorColPositions;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            ll color;
            cin >> color;
            colorRowPositions[color].push_back(i);
            colorColPositions[color].push_back(j);
        }
    }

    ll totalDistance = calculateTotalDistance(colorRowPositions) + calculateTotalDistance(colorColPositions);
    cout << totalDistance << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
