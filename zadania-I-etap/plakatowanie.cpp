//https://szkopul.edu.pl/problemset/problem/au-E9FH96-3U9rCKhcNsD5n9/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    deque<int> q;
    int result = 0;
    for (int i = 0; i < n; i++) {
        int d, w;
        cin >> d >> w;
        while (!q.empty() && q.back() > w) {
            q.pop_back();
        }
        if (q.empty() || q.back() < w) {
            q.push_back(w);
            result++;
        }
    }

    cout << result;
    return 0;
}
