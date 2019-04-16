#include <iostream>
using namespace std;

const int LEN = 109;
const int MOD = 1e9;

int go[10][2] = {{5, 7}, {6, 8}, {3, 7}, {2, 8}, {-1, -1}, {0, 6}, {1, 5}, {0, 2}, {1, 3}, {3, 5}};

int modSumm(int a, int b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

int n;
int dp[LEN][10];

int main() {
    cin >> n;

    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }

    dp[1][7] = 0;
    dp[1][9] = 0;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 4)
                continue;

            dp[i][j] = modSumm(dp[i][j], dp[i - 1][go[j][0]]);
            dp[i][j] = modSumm(dp[i][j], dp[i - 1][go[j][1]]);

            if (j == 3 || j == 5) {
                dp[i][j] = modSumm(dp[i][j], dp[i - 1][9]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 10; i++) {
        ans = modSumm(ans, dp[n][i]);
    }

    cout << ans;

    return 0;
}
