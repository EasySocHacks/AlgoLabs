#include <bits/stdc++.h>
using namespace std;
 
const int M = 1e5 + 9;
const int N = 1e5 + 9;
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
 
int n, m, s, t;
edge e[M * 2 + 100];
int ans[M * 2 + 100];
vector <int> g[N];
 
bool used[N];
bool usedE[M];
 
int dfs(int v, int minW) {
    used[v] = true;
 
    if (v == t) {
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
 
vector <int> vec;
 
void findPath(int v) {
    used[v] = true;
 
    if (v == t) {
        return;
    }
 
    for (auto x : g[v]) {
        edge vu_edge = e[x];
        int u = vu_edge.u;
        int w = ans[x];
 
        if (used[u])
            continue;
 
        if (w != 0)
            continue;
 
        if (usedE[x])
            continue;
 
        if (x >= m)
            continue;
 
        usedE[x] = true;
        vec.push_back(v);
 
        findPath(u);
 
        return;
    }
}
 
int main() {
    cin >> n >> m >> s >> t;
 
    s--;
    t--;
 
    int a, b;
 
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
 
        a--;
        b--;
 
        e[i] = edge(a, b, 1);
        e[i + m] = edge(b, a, 0);
 
        g[a].push_back(i);
        g[b].push_back(i + m);
 
        ans[i] = 1;
        ans[i + m] = 0;
    }
 
    while (dfs(s, INF) != 0) {
        fill(used, used + N, false);
    }
 
    int maxFlow = 0;
 
    for (auto x : g[s]) {
        if (x >= m)
            continue;
 
        edge vu_edge = e[x];
 
        maxFlow += vu_edge.w - ans[x];
    }
 
    if (maxFlow <= 1) {
        cout << "NO";
        return 0;
    }
 
    cout << "YES\n";
 
    fill(used, used + N, false);
 
    findPath(s);
 
    vec.push_back(t);
 
    for (int x : vec) {
        cout << x + 1 << " ";
    }
 
    cout << "\n";
 
    fill(used, used + N, false);
 
    vec.clear();
 
    findPath(s);
 
    vec.push_back(t);
 
    for (int x : vec) {
        cout << x + 1 << " ";
    }
 
    return 0;
}