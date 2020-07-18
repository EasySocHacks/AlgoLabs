#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2 * 269 + 2;
const int M = N * N * 2 + 8 * N;
const long long INF = (long long)1e18 + 9;
const int SMALL_INF = 300;

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
vector<edge> edges;
int ost_flow[M];
bool used[N];
long long dist[N];
int par_edge[N];

vector <int> edge_index[N];

long long ans = 0;

int s, t;

long long dfs() {
    fill(used, used + N, false);
    fill(dist, dist + N, INF);
    fill(par_edge, par_edge + N, -1);

    set <pair<long long, int>> st;

    dist[s] = 0;
    st.insert({0, s});

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

    if (dist[t] == INF)
        return 0;

    long long minn = INF;

    int v = t;
    while (v != s) {
        edge e = edges[par_edge[v]];

        minn = min(minn, (long long)ost_flow[par_edge[v]]);

        v = e.v;
    }

    v = t;
    while (v != s) {
        edge e = edges[par_edge[v]];

        ans += (long long)e.c *  minn;

        ost_flow[par_edge[v]] -= minn;
        ost_flow[e.re] += minn;

        v = e.v;
    }

    return minn;
}

int a[N];

signed main() {
    cin >> n >> m;

    s = 0;
    t = 2 * n + 1;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int index = edges.size();

        edges.push_back(edge(s, i, index + 1, 0, 1));
        ost_flow[index] = 1;
        edge_index[s].push_back(index);

        edges.push_back(edge(i, s, index, 0, 1));
        ost_flow[index + 1] = 0;
        edge_index[i].push_back(index + 1);

        //!---------------------------------

        index = edges.size();

        edges.push_back(edge(i + n, t, index + 1, 0, 1));
        ost_flow[index] = 1;
        edge_index[i + n].push_back(index);

        edges.push_back(edge(t, i + n, index, 0, 1));
        ost_flow[index + 1] = 0;
        edge_index[t].push_back(index + 1);

        //!---------------------------------

        index = edges.size();

        edges.push_back(edge(i, i + n, index + 1, a[i - 1], 1));
        ost_flow[index] = 1;
        edge_index[i].push_back(index);

        edges.push_back(edge(i + n, i, index, -a[i - 1], 1));
        ost_flow[index + 1] = 0;
        edge_index[i + n].push_back(index + 1);

         //!---------------------------------

        index = edges.size();

        edges.push_back(edge(i + n, i, index + 1, 0, SMALL_INF));
        ost_flow[index] = SMALL_INF;
        edge_index[i + n].push_back(index);

        edges.push_back(edge(i, i + n, index, 0, SMALL_INF));
        ost_flow[index + 1] = 0;
        edge_index[i].push_back(index + 1);
    }

    int v, u, c;
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> c;

        int index = edges.size();

        edges.push_back(edge(v, u + n, index + 1, c, SMALL_INF));
        ost_flow[index] = SMALL_INF;
        edge_index[v].push_back(index);

        edges.push_back(edge(u + n, v, index, -c, SMALL_INF));
        ost_flow[index + 1] = 0;
        edge_index[u + n].push_back(index + 1);
    }

    while (dfs() != 0) {}

    cout << ans;

    return 0;
}
