#include <bits/stdc++.h>
using namespace std;

const int LEN = 2e5 + 9;

int n, m;
int up[LEN][20];
int tin[LEN], tout[LEN];
vector <int> g[LEN];

int timer = 0;
void dfs(int v) {
    tin[v] = timer++;

    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
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
        return v;

    if (isHigher(u, v))
        return u;

    int h = 19;
    while (!isHigher(up[v][0], u)) {
        int x = up[v][h];

        if (isHigher(x, u)) {
            h--;
            x = up[v][h];
            continue;
        } else {
            v = x;
            h = 19;
        }
    }

    return up[v][0];
}

int main() {
    cin >> n;

    int p;
    for (int i = 0; i < n - 1; i++) {
        cin >> p;
        p--;

        up[i + 1][0] = p;
        g[p].push_back(i + 1);
    }

    dfs(0);

    cin >> m;
    int v, u;

    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;

        cout << (lca(v, u) + 1) << "\n";
    }

    return 0;
}