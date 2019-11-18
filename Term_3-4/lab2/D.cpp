#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 1e4 + 9;
const int K = 109;
const ll INF = 1e18;

int n, m, k, s;
vector <pair<int, int>> g[LEN];
ll d[K][LEN];

int main() {
    cin >> n >> m >> k >> s;

    s--;

    int v, u, w;
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;

        v--;
        u--;

        g[v].push_back({u, w});
    }

    for (int k = 0; k < K; k++) {
        for (int i = 0; i < LEN; i++) {
            d[k][i] = INF;
        }
    }

    d[0][s] = 0;

    for (int q = 1; q <= k; q++) {
        for (int v = 0; v < n; v++) {
            for (int i = 0; i < g[v].size(); i++) {
                int u = g[v][i].first;
                int w = g[v][i].second;

                if (d[q - 1][v] == INF)
                    continue;

                d[q][u] = min(d[q][u], d[q - 1][v] + w);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (d[k][i] == INF)
            d[k][i] = -1;

        cout << d[k][i] << "\n";
    }

    return 0;
}

