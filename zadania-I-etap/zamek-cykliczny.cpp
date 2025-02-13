//https://szkopul.edu.pl/problemset/problem/mLyF3KRZMSxwdnrKhXMOjUFJ/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    string n;
    cin >> n;
    if (n.size() == 1 && n[0] == '1') {
        cout << 0;
        return 0;
    }

    if (n[0] == '1') {
        bool canEnd = true;
        for (int i = 1; i < n.size(); i++) {
            if (n[i] != '0') {
                canEnd = false;
                break;
            }
        }
        if (canEnd) {
            cout << 1;
            return 0;
        }
    }

    int result = INT_MAX;
    int i = 0;
    do {
        int curResult = 0;
        bool skip = true;
        for (int j = n.size() - 1 - i; j >= 0; j--) {
            if (j != n.size() - 1 - i) {
                if (n[j] != '9') {
                    skip = false;
                }
                if (n[j] == '0' || skip) {
                    continue;
                }
            }
            if (j == n.size() - 1 - i) {
                //check if the first digit is 0, if it is than we cant just skip further digits when they are 9, we have to first do our late calculations and than we can skip the 9s, by setting skip to true again
                //we dont have backtrack i to calculate the 9 incrementaitons in zero because the next iteration would do 99 - something and it would include the 9 incrementations
                if (j == n.size() - 1 && n[j] == '0') {
                    skip = false;
                    continue;
                }
                if (n[j - 1] == '9') {
                    skip = true;
                }
                curResult += pow(10, i + 1) - 1 - stoi(n.substr(n.size() - 1 - i, n.size()));
            } else {
                curResult += 9 - stoi(string(1, n[j])) + 1;
            }
        }
        result = min(result, curResult);
        i++;
        //i must be <= 7 becuase 10^7 is million and million is the maximum number of digits in n, so that is how many moves we can do.
        //n.size() >= 11 because we need at least 11 digits to have a chance to get a better result moving, becuase with 11 digits we can move 10 digits and increment 0 nine times, example: 99999999990
        //what is also important to notice, is that if the first digit is different from zero we must increment it and we are doing it, but with zero we can either skip it by making it leading zero or increment it and we have to check both, so only >= 11 makes sense to check both, becuase below 11 we can just skip the leading zero and we are done
    } while (i <= 7 && n.size() >= 11);

    cout << result + 2;
    return 0;
}
