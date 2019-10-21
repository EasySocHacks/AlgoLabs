#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 1009;
const int INF = 1e9;
 
int n;
int matrix[LEN][LEN];
 
bool used[LEN];
vector <int> topsort;
 
void dfs(int v, int k) {
    used[v] = true;
 
    for (int u = 0; u < n; u++) {
        if (used[u])
            continue;
 
        if (matrix[v][u] > k)
            continue;
 
        dfs(u, k);
    }
 
    topsort.push_back(v);
}
 
void dfs2(int v, int k) {
    used[v] = true;
 
    for (int u = 0; u < n; u++) {
        if (used[u])
            continue;
 
        if (matrix[u][v] > k)
            continue;
 
        dfs2(u, k);
    }
}
 
bool solve(int m) {
    fill(used, used + LEN, false);
    topsort.clear();
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        dfs(i, m);
    }
 
    reverse(topsort.begin(), topsort.end());
 
    fill(used, used + LEN, false);
 
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int v = topsort[i];
 
        if (used[v])
            continue;
 
        cnt++;
 
        if (cnt > 1) break;
 
        dfs2(v, m);
    }
 
    return cnt <= 1;
}
 
int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
 
    cin >> n;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
 
    int l = -1, r = INF;
    int m;
 
    while (r - l > 1) {
        m = (l + r) / 2;
 
        if (solve(m)) {
            r = m;
        } else {
            l = m;
        }
    }
 
    cout << r;
 
    return 0;
}
