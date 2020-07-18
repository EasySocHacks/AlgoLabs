#include <bits/stdc++.h>
using namespace std;

const int M = 50;
const int N = 50;
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

int index = 0;

void addEdge(int v, int u, int f, int c) {
    int i = index;
    index++;

    edges[i] = edge(v, u, i + m, c, f);
    ost_flow[i] = f;
    edge_index[v].push_back(i);

    edges[i + m] = edge(u, v, i, -c, f);
    ost_flow[i + m] = 0;
    edge_index[u].push_back(i + m);
}

int r1, r2, s1, s2, p1, p2;

int main() {
    cin >> r2 >> s2 >> p2 >> r1 >> s1 >> p1;

    n = 8;
    m = 15;

    addEdge(0, 1, r1, 0);
    addEdge(0, 2, s1, 0);
    addEdge(0, 3, p1, 0);

    addEdge(1, 4, INF, 0);
    addEdge(1, 5, INF, 0);
    addEdge(1, 6, INF, 1);

    addEdge(2, 4, INF, 1);
    addEdge(2, 5, INF, 0);
    addEdge(2, 6, INF, 0);

    addEdge(3, 4, INF, 0);
    addEdge(3, 5, INF, 1);
    addEdge(3, 6, INF, 0);

    addEdge(4, 7, r2, 0);
    addEdge(5, 7, s2, 0);
    addEdge(6, 7, p2, 0);

    while (dfs() != 0) {}

    cout << ans;

    return 0;
}
