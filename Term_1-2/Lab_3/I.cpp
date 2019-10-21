#include <iostream>
using namespace std;

typedef long long ll;

const int LEN = 14;

int n, m;
char matrix[LEN][LEN];
ll dp[(1 << LEN)][LEN][LEN];

int main() {
    cin >> n >> m;
    string str;

    for (int i = 0; i < n; i++) {
        cin >> str;

        for (int j = 0; j < m; j++) {
            matrix[i][j] = str[j];
        }
    }

    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int mask = 0; mask < (1 << m); mask++) {

                    if (j == m) {
                        dp[mask][i + 1][0] += dp[mask][i][m];
                        continue;
                    }

                    if ((mask & (1 << j)) == 0 && matrix[i][j] == '.') {
                        if (j != m - 1 && matrix[i][j + 1] == '.' && (mask & (1 << (j + 1))) == 0) {
                            dp[mask | (1 << (j + 1))][i][j + 1] += dp[mask][i][j];
                        }

                        if (i != n - 1 && matrix[i + 1][j] == '.') {
                            dp[mask | (1 << j)][i][j + 1] += dp[mask][i][j];
                        }
                    } else {
                        dp[mask & (~(1 << j))][i][j + 1] += dp[mask][i][j];
                    }
                }
            }
        }

    ll ans = 0;
    for (int i = 0; i < (1 << m); i++) {
        ans += dp[i][n][0];
    }

    cout << ans;

    return 0;
}
