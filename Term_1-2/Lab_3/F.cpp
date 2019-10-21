#include <iostream>
#include <vector>
using namespace std;

const int LEN = 109;
const int INF = 1e9;

int n;
int cost[LEN];
int dp[LEN][LEN][LEN];
int par[LEN][LEN][LEN];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> cost[i + 1];
    }

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            for (int k = 0; k < LEN; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;
    //Day
    //Carry
    //Left

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= j; k++) {

                if (dp[i][j][k] > dp[i - 1][j][k + 1]) {
                    dp[i][j][k] = dp[i - 1][j][k + 1];
                    par[i][j][k] = 0;
                }

                if (j > 0 && cost[i] > 100 && k > 0 && dp[i][j][k] > dp[i - 1][j - 1][k - 1] + cost[i]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + cost[i];
                    par[i][j][k] = 1;
                }

                if (cost[i] <= 100 && dp[i][j][k] > dp[i - 1][j][k] + cost[i]) {
                    dp[i][j][k] = dp[i - 1][j][k] + cost[i];

                    par[i][j][k] = 2;
                }
            }
        }
    }

    int minn = INF;
    int a, b;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (dp[n][i][j] == INF)
                continue;

            if (dp[n][i][j] < minn) {
                minn = dp[n][i][j];

                a = i;
                b = j;
            }

            if (dp[n][i][j] == minn && j > b) {
                a = i;
                b = j;
            }
        }
    }

    cout << minn << "\n";
    cout << b << " " << (a - b) << "\n";

    vector <int> ans;
    for (int i = n; i > 0; i--) {
        if (par[i][a][b] == 0) {
            ans.push_back(i);

            b++;
        } else if (par[i][a][b] == 1) {
            a--;
            b--;
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << "\n";

    return 0;
}
