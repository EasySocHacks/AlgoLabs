#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 2009;
const ll INF = 9e18;

int n, m, s;
vector <pair<int, ll>> g[LEN];

ll d[LEN];
bool used[LEN];

void dfs(int v) {
    used[v] = true;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;

        if (used[u])
            continue;

        dfs(u);
    }
}

int main() {
    cin >> n >> m >> s;

    s--;

    int v, u;
    ll w;

    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;

        v--;
        u--;

        g[v].push_back({u, w});
    }

    for (int j = 0; j < LEN; j++) {
        d[j] = INF;
    }

    d[s] = 0;

    for (int k = 0; k <= 2* n + 10; k++) {
        for (int v = 0; v < n; v++) {
            for (int i = 0; i < g[v].size(); i++) {
                int u = g[v][i].first;
                ll w = g[v][i].second;

                if (d[v] == INF)
                    continue;

                if (d[v] + w < d[u]) {
                    d[u] = d[v] + w;

                    if (k > n + 1) {
                        if (!used[u])
                            dfs(u);
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (used[i])
            cout << "-\n";
        else {
            if (d[i] == INF)
                cout << "*\n";
            else {
                cout << d[i] << "\n";
            }
        }
    }

    return 0;
}
