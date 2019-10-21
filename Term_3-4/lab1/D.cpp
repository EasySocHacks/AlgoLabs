#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 200009;
 
int n, m;
map <int, int> g[LEN];
 
bool used[LEN];
int h[LEN];
int up[LEN];
set <pair <int, int>> bridges;
 
int dfs(int v, int p) {
    used[v] = true;
 
    h[v] = (p == -1 ? 0 : h[p] + 1);
 
    int upp = h[v];
    up[v] = h[v];
 
    for (pair <int, int> u : g[v]) {
        if (used[u.first]) {
            if (u.first == p) {
                if (u.second > 1) {
                    up[v] = min(up[v], h[u.first]);
                }
 
                continue;
            }
 
            up[v] = min(up[v], h[u.first]);
            continue;
        }
 
        int ret = dfs(u.first, v);
 
        upp = min(upp, ret);
    }
 
    upp = min(upp, up[v]);
 
    if (p != -1 && upp >= h[v]) {
        bridges.insert({v, p});
        bridges.insert({p, v});
    }
 
    return upp;
}
 
int ans[LEN];
 
void resolve(int v, int c) {
    used[v] = true;
    ans[v] = c;
 
    for (auto u : g[v]) {
        if (used[u.first])
            continue;
 
        if (bridges.count({v, u.first}) != 0) {
            continue;
        }
 
        resolve(u.first, c);
    }
}
 
int main() {
    cin >> n >> m;
 
    int b, e;
 
    for (int i = 0; i < m; i++) {
        cin >> b >> e;
 
        b--;
        e--;
 
        g[b][e]++;
        g[e][b]++;
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        dfs(i, -1);
    }
 
    fill(used, used + LEN, false);
 
    int c = 1;
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        resolve(i, c);
        c++;
    }
 
    cout << c - 1 << "\n";
 
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
 
    return 0;
}
