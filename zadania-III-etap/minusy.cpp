#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    char var[n - 1];

    for (int i = 0; i < n - 1; i++) {
        cin >> var[i];
    }

    string result;
    char prev = '-';

    for (int i = 0; i < n - 1; i++) {
        if (var[i] == prev) {
            result += '-';
        } else if (var[i] == '+') {
            result += "(-";
            prev = var[i];
        } else if (var[i] == '-') {
            result += ")-";
            prev = var[i];
        }
    }

    if (prev == '+') {
        result += ")";
    }

    cout << result << endl;
    return 0;
}
