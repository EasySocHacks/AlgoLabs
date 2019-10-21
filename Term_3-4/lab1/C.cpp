#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 200009;
 
vector <int> g[LEN];
int n, m;
bool used[LEN];
int up[LEN];
int h[LEN];
 
vector <int> anss;
 
int dfs(int v, int p) {
    if (p != -1)
        h[v] = h[p] + 1;
 
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
        anss.push_back(v);
    }
 
    ans = min(ans, up[v]);
 
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
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        h[i] = 0;
        dfs(i, -1);
    }
 
    sort(anss.begin(), anss.end());
    cout << anss.size() << "\n";
    for (int i = 0; i < anss.size(); i++) {
        cout << anss[i] + 1 << " ";
    }
 
    return 0;
}
