#include <iostream>
using namespace std;

const int LEN = 1009;
const int INF = 1e9;

int n, m;
int matrix[LEN][LEN];
int dp[2][LEN];
string path[2][LEN];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < LEN; j++) {
            dp[1][j] = -INF;
        }

        if (i == 0)
            dp[1][0] = 0;

        for (int j = 0; j < m; j++) {
            if (i != 0 && dp[1][j] < dp[0][j] + matrix[i][j]) {
                dp[1][j] =  dp[0][j] + matrix[i][j];

                path[1][j] = path[0][j] + "D";
            }

            if (j != 0 && dp[1][j] < dp[1][j - 1] + matrix[i][j]) {
                dp[1][j] = dp[1][j - 1] + matrix[i][j];

                path[1][j] = path[1][j - 1] + "R";
            }
        }

        swap(dp[0], dp[1]);
        swap(path[0], path[1]);
    }

    cout << dp[0][m - 1] + matrix[0][0] << "\n";
    cout << path[0][m - 1];

    return 0;
}
