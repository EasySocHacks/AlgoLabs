#include <bits/stdc++.h>
using namespace std;

const int LEN = 109;
const int INF = 1e7;

int n;
int matrix[LEN][LEN];
int d[LEN];
int par[LEN];

vector <int> ans;

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];

            if (matrix[i][j] == 100000)
                matrix[i][j] = INF;
        }
    }

    int x = -1;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == INF)
                    continue;

                if (d[j] > d[i] + matrix[i][j])  {
                    d[j] = d[i] + matrix[i][j];
                    par[j] = i;

                    if (k == n - 1)
                        x = j;
                }
            }
        }
    }


    if (x == -1) {
        cout << "NO";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        x = par[x];
    }

    int y = par[x];

    for (; y != x; y = par[y]) {
        ans.push_back(y);
    }

    ans.push_back(x);

    cout << "YES\n" << ans.size() << "\n";

    reverse(ans.begin(), ans.end());

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}
