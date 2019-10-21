#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 200009;
 
vector <int> g[LEN];
int n, m;
map <pair<int, int>, int> edges;
bool used[LEN];
int up[LEN];
int h[LEN];
 
vector <int> bridges;
 
int dfs(int v, int p) {
    if (p != -1)
        h[v] = h[p] + 1;
 
    up[v] = h[v];
    used[v] = true;
 
    int ans = h[v];
 
    for (int u : g[v]) {
        if (used[u]) {
            if (u != p)
                up[v] = min(up[v], h[u]);
        } else {
            int ret = dfs(u, v);
 
            ans = min(ans, ret);
        }
    }
 
    ans = min(ans, up[v]);
 
    if (p != -1 && ans >= h[v]) {
        bridges.push_back(edges[{v, p}]);
    }
 
    return ans;
}
 
int main() {
    for (int i = 0; i < LEN; i++)
        up[i] = 1e9;
 
    cin >> n >> m;
 
    int b, e;
 
    for (int i = 0; i < m; i++) {
        cin >> b >> e;
 
        e--, b--;
        g[e].push_back(b);
        g[b].push_back(e);
 
        edges[{e, b}] = i + 1;
        edges[{b, e}] = i + 1;
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        h[i] = 0;
        dfs(i, -1);
    }
 
    sort(bridges.begin(), bridges.end());
 
    cout << bridges.size() << "\n";
    for (int i = 0; i < bridges.size(); i++) {
        cout << bridges[i] << " ";
    }
 
    return 0;
}
