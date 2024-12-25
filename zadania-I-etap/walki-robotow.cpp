//https://szkopul.edu.pl/problemset/problem/lk3fxEbWZRKSfjpHbEQT9wGN/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

//const int S = 1 << 20;
//pair<int, int> t[2 * S + 10];  // Segment tree
//
//// Function to combine two robots and determine the result
//pair<int, int> lacz(pair<int, int> s1, pair<int, int> s2) {
//    if (s2.first > s1.first && s2.second > s1.second) {
//        return s2;
//    }
//    if (s1.first > s2.first && s1.second > s2.second) {
//        return s1;
//    }
//    return {-1, 0};
//}
//
//// Function to build the segment tree
//void build() {
//    for (int i = S - 1; i > 0; i--) {
//        t[i] = lacz(t[i * 2], t[i * 2 + 1]);  // Combine the results of the two children
////        if(t[i].first != 0 && t[i].second != 0) {
////            cout << t[i*2].first << " " << t[i*2+1].second << " " << t[i].first << " " << t[i].second << endl;
////        }
//    }
//}

string moznaWyeliminowac(vector<pair<int, int>> roboty, int n) {
    //porownujemy w kolejnosci posortowaych sil, roboty o mniejszej o 1 zwinnosci, i jeszcze jeden base case ( kiedy pierwszy robot ma z = 1, to mozna go od razu wyeliminowac, bo kazy go wyelminuje)
    //jednak to nie zadziała, ale może zadziałac sprawdzanie ile wygramych bedzie łacznie jesli jest nieparzystali cba robotow, to powinno byc parzyscie wygranych, a jesli nieparzyscie, to nieparzyscie wygranych

    vector<bool> eliminated(n, false);
    pair<int, int> cur = roboty[n];
    if (roboty[n].second == n) {
        return "NIE";
    }
    for (int i = n; i > 0; i--) {
        //cout<<roboty[i].first << " " << roboty[i].second << endl;
        if (eliminated[i]) {
            continue;
        }
        if (eliminated[cur.first]) {
            cur = roboty[i];
            continue;
        }

    }
    /*vector<bool> eliminated(n, false);
    pair<int, int> cur = roboty[n];
    if (roboty[n].second == n) {
        return "NIE";
    }
    for (int i = n; i > 0; i--) {
        //cout<<roboty[i].first << " " << roboty[i].second << endl;
        if (eliminated[i]) {
            continue;
        }
        if (eliminated[cur.first]) {
            cur = roboty[i];
            continue;
        }
        if (cur.second > roboty[i].second) {
            //cout<<cur.first << " " << cur.second << " won with " << roboty[i].first << " " << roboty[i].second << endl;
            eliminated[i] = true;
        } else if (cur.second < roboty[i].second) {
            //cout<<cur.first << " " << cur.second << " drew with " << roboty[i].first << " " << roboty[i].second << endl;
            eliminated[i] = true;
            eliminated[cur.first] = true;
        }
    }
    *//*   cout<<cur.first << " " << cur.second << endl;
       cout << "Eliminated: "<<eliminated[cur.first] << endl;*//*
    bool wynik = eliminated[cur.first];
    if (wynik) {
        return "TAK";
    } else {
        if (cur.second < n && !eliminated[cur.first]) { // ten warunek jest zły
            return "TAK";
        } else {
            return "NIE";
        }
    }*/
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> roboty(n + 1);
    vector<
    // Initialize roboty to default values

    for (int i = 0; i < n; i++) {
        int s, z;
        cin >> s >> z;
        s++, z++;
        // Ensure s is in the valid range
//        if (s < 1 || s > n) {
//            cerr << "Invalid value for s: " << s << endl;
//
//        }

        roboty[s] = {s, z};  // Assign to the corresponding position
    }
    cout << moznaWyeliminowac(roboty, n) << endl;
    // Initialize leaves of the segment tree
//    for (int i = 0; i < n; i++) {
//        int z = roboty[i].second;
//        z--;
//        t[z + S] = roboty[i];
//    }

    // Build the segment tree
//    build();

    // The result is at the root of the tree (t[1])
//    pair<int, int> wynik = t[1];
//    cout << wynik.first << " " << wynik.second << endl;



    return 0;
}