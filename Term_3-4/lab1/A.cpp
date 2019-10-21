#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 100009;
 
int n, m;
vector <int> g[LEN];
 
int used[LEN];
vector <int> top;
 
void dfs(int v) {
    used[v] = 1;
 
    for (int u : g[v]) {
        if (used[u] == 1) {
            cout << -1;
            exit(0);
        }
 
        if (used[u] == 2)
            continue;
 
 
        dfs(u);
    }
 
    top.push_back(v);
    used[v] = 2;
}
 
int main() {
    cin >> n >> m;
 
    int v, u;
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;
 
        g[v].push_back(u);
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i] == 0)
            dfs(i);
    }
 
    reverse(top.begin(), top.end());
 
    for (int i = 0; i < n; i++) {
        cout << (top[i] + 1) << " ";
    }
 
    return 0;
}
