#include <iostream>
using namespace std;

#define mp make_pair

const int INF = 1e9;
const int LEN = 109;

string str;
int dp[LEN][LEN];
pair <int, int> par[LEN][LEN];
int n;

bool match(char a, char b) {
    return (
            (a == '(' && b == ')') ||
            (a == '[' && b == ']') ||
            (a == '{' && b == '}')
            );
}

string solve(int l, int r) {
    if (r <= l) {
        return "";
    }

    int newL = par[l][r].first;
    int newR = par[l][r].second;

    if (newL == l + 1 && newR == r - 1) {
        return str[l] + solve(newL, newR) + str[r];
    }

    if (newL == -10) {
        return solve(l, newR) + solve(newR + 1, r);
    }

    return solve(newL, newR);
}

int main() {
    cin >> str;
    n = str.size();

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 0; i < LEN - 1; i++) {
        dp[i + 1][i] = 0;
    }

    for (int i = 0; i < LEN; i++) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l < n; l++) {
            int r = l + len - 1;

            if (r >= n)
                break;

            if (match(str[l], str[r])) {
                if (dp[l][r] > dp[l + 1][r - 1]) {
                    dp[l][r] = dp[l + 1][r - 1];

                    par[l][r] = mp(l + 1, r - 1);
                }
            }

            if (dp[l][r] > dp[l + 1][r] + 1) {
                dp[l][r] = dp[l + 1][r] + 1;

                par[l][r] = mp(l + 1, r);
            }


            if (dp[l][r] > dp[l][r - 1] + 1) {
                dp[l][r] = dp[l][r - 1] + 1;

                par[l][r] = mp(l, r - 1);
            }

            for (int i = l; i < r; i++) {
                if (dp[l][r] > dp[l][i] + dp[i + 1][r]) {
                    dp[l][r] = dp[l][i] + dp[i + 1][r];

                    par[l][r] = mp(-10, i);
                }
            }
        }
    }

    cout << solve(0, n - 1);

    return 0;
}
