//https://szkopul.edu.pl/problemset/problem/A7ZI0Wwn6tTiCJoYblblTAqz/site/?key=statement
#include <bits/stdc++.h>

using namespace std;

//wynik to 2 do potegi scc bez 1 lub 0, bo jesli w scc jest 0 lub 1, to kazdy node musi byc 1 lub 0. Jesli natomiast w SCC jest 0 i 1, to jest 0 rozwiazan, bo jest sprzecznosc

class BigInt {
private:
    vector<uint32_t> digits; // Each element stores a part of the number
    static const uint64_t BASE = 1000000000; // Base 10^9, used for arithmetic operations
    static const int BASE_DIGITS = 9; // Number of digits in the base, used for string formatting

    // Helper function to remove leading zeros
    void trim() {
        while (!digits.empty() && digits.back() == 0)
            digits.pop_back();
    }

public:
    // Constructors
    BigInt() : digits(1, 0) {}
    BigInt(uint64_t value) { *this = value; }
    BigInt(const string &str) { *this = str; }

    // Assignment operators
    BigInt &operator=(uint64_t value) {
        digits.clear();

        do {
            digits.push_back(value % BASE);
            value /= BASE;
        } while (value > 0);
        return *this;
    }

    BigInt &operator=(const string &str) { //Passed by reference, because strings are large and const, because we don't want to change the value of the string
        digits.clear();
        int len = str.length();
        for (int i = len; i > 0; i -= BASE_DIGITS) {
            int end = i;
            int start = max(0, i - BASE_DIGITS);
            digits.push_back(stoul(str.substr(start, end - start)));
        }
        trim();

        return *this;
    }


    // Multiplication operator
    BigInt operator*(const BigInt &other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size());
        for (size_t i = 0; i < digits.size(); ++i) {
            uint64_t carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                uint64_t prod = result.digits[i + j] + digits[i] * 1ULL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = prod % BASE;
                carry = prod / BASE;
            }
        }
        result.trim();
        return result;
    }

    // Comparison operators
    bool operator<(const BigInt &other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator<=(const BigInt &other) const {
        return (*this < other) || (*this == other);
    }

    bool operator==(const BigInt &other) const {
        return digits == other.digits;
    }

    // Stream output operator
    friend ostream &operator<<(ostream &out, const BigInt &value) {
        if (value.digits.empty()) {
            out << 0;
            return out;
        }
        out << value.digits.back();
        for (int i = value.digits.size() - 2; i >= 0; --i) {
            out << setw(BASE_DIGITS) << setfill('0') << value.digits[i];
        }
        return out;
    }
};


// Function to perform DFS and store the finish order of nodes
void DFS(int node, vector<vector<int> > &adj, vector<bool> &visited, stack<int> &finishStack) {
    visited[node] = true;
    for (int adjacent: adj[node]) {
        if (!visited[adjacent]) {
            DFS(adjacent, adj, visited, finishStack);
        }
    }
    finishStack.push(node);
}

// Function to perform DFS on the transposed graph to find SCCs
void DFSUtil(int node, vector<vector<int> > &transposed, vector<bool> &visited, vector<int> &scc) {
    visited[node] = true;
    scc.push_back(node);
    for (int adjacent: transposed[node]) {
        if (!visited[adjacent]) {
            DFSUtil(adjacent, transposed, visited, scc);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int x; // Number of equations
    cin >> x;
    while (x--) {
        int k; // Number of variables
        cin >> k;
        vector<int> lengths(k); // Lengths of each variable
        for (int i = 0; i < k; i++) {
            cin >> lengths[i];
        }

        int l; // Length of the left side of the equation
        cin >> l;
        string leftSide;
        cin >> leftSide;

        int r; // Length of the right side of the equation
        cin >> r;
        string rightSide;
        cin >> rightSide;

        // Step 1: Create graph adjacency list
        unordered_map<char, int> variableIndex; // Map variables to their starting index// Store lengths of variables
        int idx = 0;

        // Map each variable to its starting index and calculate the total number of vertices
        for (int i = 0; i < k; i++) {
            char variable = 'a' + i;
            variableIndex[variable] = idx;
            idx += lengths[i];
        }

        // Check if '0' or '1' appear in the input
        bool hasZero = leftSide.find('0') != string::npos || rightSide.find('0') != string::npos;
        bool hasOne = leftSide.find('1') != string::npos || rightSide.find('1') != string::npos;

        int totalVertices = idx + (hasZero ? 1 : 0) + (hasOne ? 1 : 0); // Include vertices for 0 and 1 if they appear
        vector<vector<int> > adj(totalVertices);
        vector<int> leftExpanded, rightExpanded;

        // Step 2: Expand left and right sides of the equation
        auto expand = [&](const string &side, vector<int> &expanded) {
            for (char c: side) {
                if (isalpha(c)) {
                    int startIdx = variableIndex[c];
                    int len = lengths[c - 'a'];
                    for (int i = 0; i < len; i++) {
                        expanded.push_back(startIdx + i);
                    }
                } else {
                    if (c == '0' && hasZero) {
                        expanded.push_back(idx); // Map 0 to its index
                    } else if (c == '1' && hasOne) {
                        expanded.push_back(idx + (hasZero ? 1 : 0)); // Map 1 to its index
                    }
                }
            }
        };

        // Expand left and right sides
        expand(leftSide, leftExpanded);
        expand(rightSide, rightExpanded);

        if (leftExpanded.size() != rightExpanded.size()) {
            cout << 0 << "\n";
            continue;
        }

        // Step 3: Create edges based on the expanded representation
        for (int i = 0; i < leftExpanded.size(); i++) {
            int u = leftExpanded[i];
            int v = rightExpanded[i];
            adj[u].push_back(v);
            adj[v].push_back(u); // If the graph should be undirected
        }

        // Step 4: Transpose graph creation (for SCC finding)
        vector<vector<int> > transposed(totalVertices);
        for (int u = 0; u < totalVertices; u++) {
            for (int v: adj[u]) {
                transposed[v].push_back(u);
            }
        }

        // Step 5: Perform DFS to find SCCs
        stack<int> finishStack;
        vector<bool> visited(totalVertices, false);

        // Step 5.1: Perform DFS on the original graph to get finishing times
        for (int i = 0; i < totalVertices; i++) {
            if (!visited[i]) {
                DFS(i, adj, visited, finishStack);
            }
        }

        // Step 5.2: Perform DFS on the transposed graph to discover SCCs
        vector<vector<int> > SCCs;
        fill(visited.begin(), visited.end(), false);

        while (!finishStack.empty()) {
            int node = finishStack.top();
            finishStack.pop();

            if (!visited[node]) {
                vector<int> scc;
                DFSUtil(node, transposed, visited, scc);
                SCCs.push_back(scc);
            }
        }

        // Step 6: Output SCCs and calculate the number of solutions
        int exponent = 0;
        bool isContradictory = false;
        for (const auto &scc: SCCs) {
            bool hasZeroInSCC = false, hasOneInSCC = false;
            cout << "SCC: ";
            for (int node: scc) {
                if (node < idx) {
                    for (const auto &[var, startIdx]: variableIndex) {
                        if (node >= startIdx && node < startIdx + lengths[var - 'a']) {
                            cout << var << (node - startIdx + 1) << " ";
                            break;
                        }
                    }
                } else {
                    if (hasZero && node == idx) {
                        cout << "0 ";
                        hasZeroInSCC = true;
                    } else if (hasOne && node == idx + (hasZero ? 1 : 0)) {
                        cout << "1 ";
                        hasOneInSCC = true;
                    }
                }
            }
            cout << "\n";
            if (!hasZeroInSCC && !hasOneInSCC) {
                exponent++;
            } else if (hasZeroInSCC && hasOneInSCC) {
                isContradictory = true;
                break;
            }
        }
        if (isContradictory) {
            cout << 0 << "\n";
            continue;
        }

        BigInt result(1);
        for(int i = 0; i < exponent; i++) {
            result = result * BigInt(2);
        }
        cout << result << "\n";
    }

    return 0;
}
