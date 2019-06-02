#include <bits/stdc++.h>
using namespace std;

const int LEN = 2e5 + 9;

int n, m;
pair <int, int> up[LEN][20];
int tin[LEN], tout[LEN];
vector <int> g[LEN];

int timer = 0;
void dfs(int v) {
    tin[v] = timer++;

    for (int i = 1; i < 20; i++) {
        up[v][i].first = up[up[v][i - 1].first][i - 1].first;
        up[v][i].second = min(up[up[v][i - 1].first][i - 1].second, up[v][i - 1].second);
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        dfs(u);
    }

    tout[v] = timer++;
}

bool isHigher(int v, int u) {
    return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

int lca(int v, int u) {
    if (isHigher(v, u))
        swap(v, u);

    int ans = 1e9;
    int h = 19;
    while (!isHigher(up[v][0].first, u)) {
        int x = up[v][h].first;

        if (isHigher(x, u)) {
            h--;
            x = up[v][h].first;
            continue;
        } else {
            ans = min(ans, up[v][h].second);

            v = x;
            h = 19;
        }
    }

    ans = min(ans, up[v][0].second);

    return ans;
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);

    cin >> n;

    int p, c;
    for (int i = 0; i < n - 1; i++) {
        cin >> p >> c;
        p--;

        up[i + 1][0] = {p, c};
        g[p].push_back(i + 1);
    }

    dfs(0);

    cin >> m;
    int v, u;

    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;

        cout << min(lca(v, u), lca(u, v)) << "\n";
    }

    return 0;
}