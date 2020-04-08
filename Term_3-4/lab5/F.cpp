#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 109;
const int INF = 1e9;
 
struct edge {
    int a, b, w, rx;
    bool canGo;
 
    edge() {
        a = 0;
        b = 0;
        w = 0;
        rx = 0;
        canGo = false;
    }
 
    edge(int a, int b, int w, bool canGo, int rx) : a(a), b(b), w(w), canGo(canGo), rx(rx) {}
};
 
int n;
char matrix[LEN][LEN];
bool used[LEN][LEN];
int a[LEN];
 
vector <int> g[LEN][LEN];
vector <edge> e;
vector <int> ans;
 
int dfs(int va, int vb, int minW) {
    used[va][vb] = true;
 
    if (va == n + 1 && vb == n + 1) {
        return minW;
    }
 
    for (auto x : g[va][vb]) {
        edge vu_edge = e[x];
        int ua = vu_edge.a;
        int ub = vu_edge.b;
        int w = ans[x];
 
        if (used[ua][ub])
            continue;
 
        if (w == 0)
            continue;
 
        int ret = dfs(ua, ub, min(minW, w));
 
        if (ret != 0) {
            ans[x] -= ret;
            ans[vu_edge.rx] += ret;
 
            return ret;
        }
    }
 
    return 0;
}
 
int findPath(int va, int vb, int minW) {
    used[va][vb] = true;
 
    if (va == n + 1 && vb == n + 1) {
        return minW;
    }
 
    for (auto x : g[va][vb]) {
        edge vu_edge = e[x];
        int ua = vu_edge.a;
        int ub = vu_edge.b;
        int w = ans[x];
 
        if (!vu_edge.canGo)
            continue;
 
        if (used[ua][ub])
            continue;
 
        if (w >= vu_edge.w)
            continue;
 
       int ret = findPath(ua, ub, min(minW, vu_edge.w - w));
 
        if (ret != 0) {
            ans[x] += ret;
            ans[vu_edge.rx] -= ret;
 
            if (ua == ub && ua != n + 1) {
                int a = va;
                int b = vb;
 
                if (ua != a) {
                    swap(a, b);
                }
 
                if (ret == 3) {
                    matrix[a][b] = 'W';
                    matrix[b][a] = 'L';
                }
 
                if (ret == 2) {
                    matrix[a][b] = 'w';
                    matrix[b][a] = 'l';
                }
 
                if (ret == 1) {
                    matrix[a][b] = 'l';
                    matrix[b][a] = 'w';
                }
            }
 
            return ret;
        }
    }
 
    return 0;
}
 
void clearUsed() {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            used[i][j] = false;
        }
    }
}
 
int main() {
    cin >> n;
    string str;
 
    for (int i = 1; i <= n; i++) {
        cin >> str;
 
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = str[j - 1];
        }
    }
 
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (matrix[i][j] == '.' || matrix[i][j] == '#')
                continue;
 
            if (matrix[i][j] == 'W') {
                a[i] -= 3;
            }
 
            if (matrix[i][j] == 'w') {
                a[i] -= 2;
            }
 
            if (matrix[i][j] == 'l') {
                a[i] -= 1;
            }
        }
    }
 
    e.clear();
    ans.clear();
 
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (matrix[i][j] != '.')
                continue;
 
            e.push_back(edge(i, j, 3, true, e.size() + 3));
            ans.push_back(3);
            g[0][0].push_back(e.size() - 1);
 
            e.push_back(edge(i, i, 3, true, e.size() + 3));
            ans.push_back(3);
            g[i][j].push_back(e.size() - 1);
 
            e.push_back(edge(j, j, 3, true, e.size() + 3));
            ans.push_back(3);
            g[i][j].push_back(e.size() - 1);
 
            //!------------------------
 
            e.push_back(edge(0, 0, 0, false, e.size() - 3));
            ans.push_back(0);
            g[i][j].push_back(e.size() - 1);
 
            e.push_back(edge(i, j, 0, false, e.size() - 3));
            ans.push_back(0);
            g[i][i].push_back(e.size() - 1);
 
            e.push_back(edge(i, j, 0, false, e.size() - 3));
            ans.push_back(0);
            g[j][j].push_back(e.size() - 1);
        }
    }
 
    for (int i = 1; i <= n; i++) {
        e.push_back(edge(n + 1, n + 1, a[i], true, e.size() + 1));
        ans.push_back(a[i]);
        g[i][i].push_back(e.size() - 1);
 
        //!------------------------
 
        e.push_back(edge(i, i, 0, false, e.size() - 1));
        ans.push_back(0);
        g[n + 1][n + 1].push_back(e.size() - 1);
    }
 
    clearUsed();
 
    while (dfs(0, 0, INF) != 0) {
        clearUsed();
    }
 
    clearUsed();
 
    while (findPath(0, 0, INF) != 0) {
        clearUsed();
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << matrix[i][j];
        }
 
        cout << "\n";
    }
 
    return 0;
}