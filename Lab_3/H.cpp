#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
#define mp make_pair

const int LEN = 14;
const int INF = 1e9;

int cost[LEN][LEN];
int dp[(1 << LEN)][LEN];
pair <int, int> par[(1 << LEN)][LEN];

int n;

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    for (int i = 0; i < (1 << LEN); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }

    for (int i = 1; i < (1 << LEN); i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if ((i | (1 << k)) == i)
                    continue;

                if (dp[i | (1 << k)][k] > dp[i][j] + cost[j][k]) {
                    dp[i | (1 << k)][k] = dp[i][j] + cost[j][k];

                    par[i | (1 << k)][k] = mp(i, j);
                }
            }
        }
    }

    int minn = INF;
    int a = (1 << n) - 1;
    int b;
    for (int i = 0; i < n; i++) {
        if (minn > dp[(1 << n) - 1][i]) {
            minn = dp[(1 << n) - 1][i];

            b = i;
        }
    }

    vector <int> ans;

    while (a != 0) {
        ans.pb(b + 1);

        int A = par[a][b].first;
        int B = par[a][b].second;

        a = A;
        b = B;
    }

    cout << minn << "\n";
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << " ";

    return 0;
}
