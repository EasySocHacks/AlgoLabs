#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 4009 * 5;
const int N = 209 + 3 * 2009;
const int K = 109;
const long long INF = (long long)1e18 + 9;

struct edge {
    int v, u;
    int re;
    int c;
    int f;
    int num;

    edge() {
        v = 0;
        u = 0;
        re = 0;
        c = 0;
        f = 0;
        num = -1;
    }

    edge(int v, int u, int re, int c, int f, int num) : v(v), u(u), re(re), c(c), f(f), num(num) {}
};

int n, m, k;
vector<edge> edges;
int ost_flow[M];
bool used[M];
int dist[N];
int par_edge[N];

vector <int> edge_index[N];
vector <vector<int>> path;

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

    vector <int> toPath(0);

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

bool usedN[N];

bool findPath(int v) {
    usedN[v] = true;

    if (v == n - 1) {
        return true;
    }

    for (int j : edge_index[v]) {
        if (ost_flow[j] != 0)
            continue;

        edge e = edges[j];

        if (usedN[e.u])
            continue;

        bool b = findPath(e.u);

        if (b) {
            if (e.num != -1)
                path.back().push_back(e.num);

            ost_flow[j]++;

            return true;
        }
    }

    return false;
}

signed main() {
    cin >> n >> m >> k;

    int v, u, c;

    int x = n;

    for (int i = 0; i < m; i++) {
        cin >> v >> u >> c;

        v--;
        u--;

        int index = edges.size();

        edges.push_back(edge(v, x, index + 1, c, 1, -1));
        ost_flow[index] = 1;
        edge_index[v].push_back(index);
        edges.push_back(edge(x, v, index, -c, 1, -1));
        ost_flow[index + 1] = 0;
        edge_index[x].push_back(index + 1);

        index = edges.size();

        edges.push_back(edge(x, v, index + 1, c, 1, -1));
        ost_flow[index] = 1;
        edge_index[x].push_back(index);
        edges.push_back(edge(v, x, index, -c, 1, -1));
        ost_flow[index + 1] = 0;
        edge_index[v].push_back(index + 1);

        index = edges.size();

        edges.push_back(edge(x, x + 1, index + 1, 0, 1, i + 1));
        ost_flow[index] = 1;
        edge_index[x].push_back(index);
        edges.push_back(edge(x + 1, x, index, 0, 1, i + 1));
        ost_flow[index + 1] = 1;
        edge_index[x + 1].push_back(index + 1);

        index = edges.size();

        edges.push_back(edge(x + 1, u, index + 1, c, 1, -1));
        ost_flow[index] = 1;
        edge_index[x + 1].push_back(index);
        edges.push_back(edge(u, x + 1, index, -c, 1, -1));
        ost_flow[index + 1] = 0;
        edge_index[u].push_back(index + 1);

        index = edges.size();

        edges.push_back(edge(u, x + 1, index + 1, c, 1, -1));
        ost_flow[index] = 1;
        edge_index[u].push_back(index);
        edges.push_back(edge(x + 1, u, index, -c, 1, -1));
        ost_flow[index + 1] = 0;
        edge_index[x + 1].push_back(index + 1);

        x += 2;
    }

    int cnt = 0;
    while (dfs() != 0) {
        cnt++;

        if (cnt == k)
            break;
    }

    if (cnt != k) {
        cout << "-1";
        return 0;
    }

    for (int i = 0; i < k; i++) {
        path.push_back(vector<int>(0));
        fill(usedN, usedN + N, false);
        findPath(0);
        reverse(path.back().begin(), path.back().end());
    }

    cout.precision(20);
    cout << (double)ans / 2.0 / k << "\n";

    for (int i = 0; i < k; i++) {
        cout << path[i].size() << " ";

        for (int x : path[i]) {
            cout << x << " ";
        }

        cout << "\n";
    }

    return 0;
}
