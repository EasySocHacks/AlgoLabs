#include <iostream>
using namespace std;

const int LEN = 1009;
const int INF = 1e9;

string a, b;

long long dp[LEN][LEN];

int main() {

    cin >> a >> b;

    a = " " + a;
    b = " " + b;

    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            dp[i][j] = INF;

    dp[0][0] = 0;

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {

            if (i > 0 && j > 0 && a[i] == b[j]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            } else {

                if (i > 0 && j > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);

                if (i > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);

                if (j > 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
        }
    }

    cout << dp[a.size() - 1][b.size() - 1];

    return 0;
}
