#include <iostream>
#include <vector>

using namespace std;

int countWaysToMakeChange(int coins[], int numCoins, int target) {
    // Create a DP array to store the number of ways to make each amount
    vector<int> dp(target + 1, 0);


    dp[0] = 1; //Base case: jest jeden sposob na uzyskanie 0, czyli nie uzywamy monet
    //kiedy patrzymy na dp[0], czyli np j=3 i nasz aktualny coin to 3, to wtedy patrzymy na ilosc ktora jest rowan aktualnej monecie, wiec dodajemy dp[0], do dp[j], bo dp[0] to 1, bo mozemy zrobic 1 sposobem 0
    // Iterate over each coin
    for (int i = 0; i < numCoins; i++) {
        // Update the dp array for all amounts from coin value to target
        for (int j = coins[i]; j <= target; j++) {
            dp[j] += dp[j - coins[i]]; // j - coin, sprawia, ze dodajemy mozliwosci zrobienia ilosci bez coina, i potem dodajemy tego coina, zeby miec oczekiwana ilosc
        } //j to amount, j=coins[i], czyli j sie rowna na poczatku aktualnemu coinowi, j-coin to ile jest mozilwosci zrobienia coina, ktorego potrzebujemy, a dp[j] to ile jest mozliwosci zrobienia j
    }

    // The answer is the number of ways to make the target amount
    return dp[target];
}

int main() {
    int coins[] = {1, 2, 5}; // Example coin denominations
    int numCoins = sizeof(coins) / sizeof(coins[0]); // Number of different coins
    int target = 6; // Target amount

    int result = countWaysToMakeChange(coins, numCoins, target);
    cout << "Number of ways to make change for " << target << " is: " << result << endl;

    return 0;
}
