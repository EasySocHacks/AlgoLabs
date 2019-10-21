#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 200009;
 
int n, m;
vector <int> g[LEN];
bool used[LEN];
 
int up[LEN];
int h[LEN];
 
set <int> ts;
vector <pair<int, int>> edges;
 
int dfs(int v, int p) {
    h[v] = (0 ? p == -1 : h[p] + 1);
 
    up[v] = h[v];
    used[v] = true;
 
    int ans = h[v];
    bool isCurr = false;
    int cnt = 0;
 
    for (int u : g[v]) {
        if (used[u]) {
            if (u != p)
                up[v] = min(up[v], h[u]);
        } else {
            cnt++;
            int ret = dfs(u, v);
 
            if (ret >= h[v]) {
                isCurr = true;
            }
 
            ans = min(ans, ret);
        }
    }
 
    if ((p != -1 && isCurr && cnt > 0) || (p == -1 && cnt > 1)) {
        ts.insert(v);
    }
 
    up[v] = min(ans, up[v]);
 
    return up[v];
}
 
int color = 1;
 
map <pair<int, int>, int> ans;
void resolve(int v, int p, int c) {
    used[v] = true;
 
    for (int u : g[v]) {
        if (used[u]) {
            if (u == p)
                continue;
 
            if (h[u] < h[v]) {
                ans[{v, u}] = c;
                ans[{u, v}] = c;
            }
 
 
            continue;
        }
 
        if (ts.count(v) != 0 && up[u] >= h[v]) {
            ans[{v, u}] = color;
            ans[{u, v}] = color;
            resolve(u, v, color++);
        } else {
            ans[{v, u}] = c;
            ans[{u, v}] = c;
 
            resolve(u, v, c);
        }
    }
}
 
int main() {
    cin >> n >> m;
 
    int b, e;
 
    for (int i = 0; i < m; i++) {
        cin >> b >> e;
 
        b--;
        e--;
 
        edges.push_back({b, e});
 
        g[b].push_back(e);
        g[e].push_back(b);
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        dfs(i, -1);
    }
 
    fill(used, used + LEN, false);
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        if (g[i].size() == 0)
            continue;
 
        if (ts.count(i) != 0)
            color--;
 
        resolve(i, -1, color++);
    }
 
    cout << color - 1 << "\n";
    for (int i = 0; i < m; i++) {
        cout << ans[edges[i]] << " ";
    }
 
    return 0;
}
