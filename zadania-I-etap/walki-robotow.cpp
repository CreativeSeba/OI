//https://szkopul.edu.pl/problemset/problem/lk3fxEbWZRKSfjpHbEQT9wGN/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

//nie mozemy dawac rootow ktore wygrywaja ze wszystkimi bo jest tylko jeden taki robot.
//musimy dac roboty ktore nie przegrywaja, ktore tylko remisuja

struct Robot {
    int s, z;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Robot> robots(n);
    for (int i = 0; i < n; i++) {
        cin >> robots[i].s >> robots[i].z;
    }
    //przehodzimy od ostatniego, bo ostatni nigdy nie przegra bo jest najsilniejszy
    sort(robots.begin(), robots.end(), [](Robot a, Robot b) {
        return a.s > b.s;
    });

    vector<Robot> notLoosingRobots, losingRobots;
    //musimy sprawdzic czy aktualny robot jest zwinniejszy od poprzednich, tzn. czy jest wyzej na ukladzie wspolrzednych, bo wiemy ze nie jest dalej na prawo, gdyz posortowalismy tablice wedlug sily
    int maxAgility = 0;
    for (Robot curRobot: robots) {
        if (curRobot.z > maxAgility) {
            maxAgility = curRobot.z;
            notLoosingRobots.push_back(curRobot);
        } else {
            losingRobots.push_back(curRobot);
        }
    }
    Robot mostLoosingAgile{}, mostLoosingStrong{};
    for (auto &robot : losingRobots) {
        if (robot.s > mostLoosingStrong.s) {
            mostLoosingStrong = robot;
        }
        if (robot.z > mostLoosingAgile.z) {
            mostLoosingAgile = robot;
        }
    }
    bool canEmpty = false;
    //patrzymy czy najzwinniejszy robot, lub najsilniejszy robot, ktore nie sa w zbiorze majoryzującym remisują z jakimkolwiek robotem ze zbioru majoryzującego
    //roboty ze zbioru majorujacego są w stanie "wyczyścic" roboty pod nimi w ukladzie wspolrzednych, dlatego trzeba sprawdzic czy jest jeden robot ktory moze sprawic ze nieparzyste notLoosingRobots beda parzyste
    if (notLoosingRobots.size()%2 == 0) {
        canEmpty = true;
    } else {
        for (auto &winningRobot : notLoosingRobots) {
            if (winningRobot.s < mostLoosingStrong.s || winningRobot.z < mostLoosingAgile.z) {
                canEmpty = true;
                break;
            }
        }
    }
    if (canEmpty) {
        cout<<"TAK\n";
    } else {
        cout<<"NIE\n";
    }

    return 0;
}
