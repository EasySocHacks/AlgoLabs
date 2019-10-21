#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 100009;
 
int n, m;
vector <int> g[LEN];
vector <int> rg[LEN];
set <int> newg[LEN];
int color[LEN];
bool used[LEN];
 
vector <int> topsort;
 
void dfs(int v) {
    used[v] = true;
 
    for (int u : g[v]) {
        if (used[u])
            continue;
 
        dfs(u);
    }
 
    topsort.push_back(v);
}
 
void dfs2(int v, int c) {
    used[v] = true;
    color[v] = c;
 
    for (int u : rg[v]) {
        if (color[u] != 0) {
            if (color[u] != c) {
                newg[color[u]].insert(c);
            }
 
            continue;
        }
 
        dfs2(u, c);
    }
}
 
int main() {
    cin >> n >> m;
 
    int b, e;
 
    for (int i = 0; i < m; i++) {
        cin >> b >> e;
        e--;
        b--;
 
        g[b].push_back(e);
        rg[e].push_back(b);
    }
 
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i);
    }
 
    reverse(topsort.begin(), topsort.end());
 
    for (int i = 0; i < LEN; i++)
        used[i] = false;
 
    int c = 1;
    for (int i = 0; i < n; i++) {
        if (used[topsort[i]])
            continue;
 
        dfs2(topsort[i], c);
        c++;
    }
 
    int ans = 0;
 
    for (int i = 1; i < LEN; i++) {
        ans += newg[i].size();
    }
 
    cout << ans;
 
    return 0;
}
