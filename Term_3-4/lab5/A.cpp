#include <bits/stdc++.h>
using namespace std;
 
const int M = 5009;
const int N = 109;
const int INF = 1e9;
 
struct edge {
    int v, u, w;
 
    edge() {
        v = 0;
        u = 0;
        w = 0;
    }
 
    edge(int v, int u, int w) : v(v), u (u), w(w) {}
};
 
int n, m;
edge e[M * 2 + 100];
int ans[M * 2 + 100];
vector <int> g[N];
 
bool used[N];
 
int dfs(int v, int minW) {
    used[v] = true;
 
    if (v == n - 1) {
        return minW;
    }
 
    for (auto x : g[v]) {
        edge vu_edge = e[x];
        int u = vu_edge.u;
        int w = ans[x];
 
        if (used[u])
            continue;
 
        if (w == 0)
            continue;
 
        int ret = dfs(u, min(minW, w));
 
        if (ret != 0) {
            ans[x] -= ret;
            ans[(x + m) % (2 * m)] += ret;
 
            return ret;
        }
    }
 
    return 0;
}
 
int main() {
    cin >> n >> m;
 
    int a, b, c;
 
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
 
        a--;
        b--;
 
        e[i] = edge(a, b, c);
        e[i + m] = edge(b, a, c);
 
        g[a].push_back(i);
        g[b].push_back(i + m);
 
        ans[i] = c;
        ans[i + m] = c;
    }
 
    while (dfs(0, INF) != 0) {
        fill(used, used + N, false);
    }
 
    int maxFlow = 0;
 
    for (auto x : g[0]) {
        edge vu_edge = e[x];
 
        maxFlow += vu_edge.w - ans[x];
    }
 
    cout << maxFlow << "\n";
 
    for (int i = 0; i < m; i++) {
        edge vu_edge = e[i];
 
        cout << (-ans[i] + ans[i + m]) / 2 << "\n";
    }
 
    return 0;
}