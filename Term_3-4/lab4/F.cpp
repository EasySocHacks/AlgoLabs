#include <bits/stdc++.h>
using namespace std;

const int LEN = 10009;

int n, m, a, b;
bool matrix[109][109];

bool used[LEN];

vector <int> g [LEN];
int rg[LEN];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;

    for (int u : g[v]) {
        if (rg[u] == -1 || dfs(rg[u])) {
            rg[u] = v;
            return true;
        }
    }

    return false;
}

int main() {
    freopen("dominoes.in", "r", stdin);
    freopen("dominoes.out", "w", stdout);

    cin >> n >> m >> a >> b;
    int cnt = 0;

    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;

        for (int j = 0; j < m; j++) {
            if (str[j] == '*') {
                matrix[i][j] = true;
                cnt++;
            }
        }
    }

    if (2 * b <= a) {
        cout << cnt * b;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pos = i * m + j;

            if ((i % 2 == 1 && j % 2 == 0) || (i % 2 == 0 && j % 2 == 1))
                continue;

            if (!matrix[i][j])
                continue;

            for (int d = 0; d < 4; d++) {
                int x = j + dx[d];
                int y = i + dy[d];

                if (x < 0 || y < 0 || x >= m || y >= n)
                    continue;

                if (!matrix[y][x])
                    continue;

                g[pos].push_back(y * m + x);
            }
        }
    }

    fill(rg, rg + LEN, -1);

    for (int i = 0; i < LEN; i++) {
        int y = i / m;
        int x = i % m;

        if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
            continue;
        }

        if (dfs(i))
            fill(used, used + LEN, false);
    }

    fill(used, used + LEN, false);

    long long ans = 0;

    for (int i = 0; i <= n * m - 1; i++) {
        int y = i / m;
        int x = i % m;

        if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1)) {
            continue;
        }

        if (rg[i] == -1 && matrix[y][x])
            ans += b;

        if (rg[i] != -1) {
            ans += a;
            used[rg[i]] = true;
        }
    }

    for (int i = 0; i <= n * m - 1; i++) {
        int y = i / m;
        int x = i % m;

        if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
            continue;
        }

        if (!used[i] && matrix[y][x])
            ans += b;
    }

    cout << ans;

    return 0;
}
