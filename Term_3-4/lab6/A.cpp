#include <bits/stdc++.h>
using namespace std;

const int M = 4009;
const int N = 109;
const int INF = 1e9 + 9;

struct edge {
    int v, u;
    int re;
    int c;
    int f;

    edge() {
        v = 0;
        u = 0;
        re = 0;
        c = 0;
        f = 0;
    }

    edge(int v, int u, int re, int c, int f) : v(v), u(u), re(re), c(c), f(f) {}
};

int n, m;
edge edges[M];
int ost_flow[M];
bool used[M];
int dist[N];
int par_edge[N];

vector <int> edge_index[N];

long long ans = 0;

int dfs() {
    fill(used, used + M, false);
    fill(dist, dist + N, INF);
    fill(par_edge, par_edge + N, -1);

    set <pair<int, int>> st;

    dist[0] = 0;
    st.insert({0, 0});

    while (!st.empty()) {
        auto it = st.begin();
        int v = (*it).second;

        used[v] = true;

        st.erase(it);

        for (int j : edge_index[v]) {
            if (ost_flow[j] == 0)
                continue;

            edge e = edges[j];

            if (dist[v] + e.c < dist[e.u]) {
                st.erase({dist[e.u], e.u});

                dist[e.u] = dist[v] + e.c;
                par_edge[e.u] = j;

                st.insert({dist[e.u], e.u});
            }
        }
    }

    if (dist[n - 1] == INF)
        return 0;

    int minn = INF;

    int v = n - 1;
    while (v != 0) {
        edge e = edges[par_edge[v]];

        minn = min(minn, ost_flow[par_edge[v]]);

        v = e.v;
    }

    v = n - 1;
    while (v != 0) {
        edge e = edges[par_edge[v]];

        ans += (long long)e.c *  minn;

        ost_flow[par_edge[v]] -= minn;
        ost_flow[e.re] += minn;

        v = e.v;
    }

    return minn;
}

int main() {
    cin >> n >> m;

    int v, u, c, f;

    for (int i = 0; i < m; i++) {
        cin >> v >> u >> f >> c;

        v--;
        u--;

        edges[i] = edge(v, u, i + m, c, f);
        ost_flow[i] = f;
        edge_index[v].push_back(i);

        edges[i + m] = edge(u, v, i, -c, f);
        ost_flow[i + m] = 0;
        edge_index[u].push_back(i + m);
    }

    while (dfs() != 0) {}

    cout << ans;

    return 0;
}
