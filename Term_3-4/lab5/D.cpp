#include <bits/stdc++.h>
using namespace std;
 
const int N = 5009;
const int M = 5 * N + 9;
const int INF = 1e8;
 
struct edge {
    int v, u, w;
 
    edge() {
        v = 0;
        u = 0;
        w = 0;
    }
 
    edge(int v, int u, int w) : v(v), u (u), w(w) {}
};
 
int ww;
int n, m, s, t;
int w, h;
edge e[M * 2 + 100];
int ans[M * 2 + 100];
vector <int> g[N];
char matrix[59][59];
 
bool used[N];
 
int dfs(int v, int minW) {
    used[v] = true;
 
    if (v == t + n) {
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
 
void findCut(int v) {
    used[v] = true;
 
    for (auto x : g[v]) {
        edge vu_edge = e[x];
        int u = vu_edge.u;
        int w = ans[x];
 
        if (used[u])
            continue;
 
        if (w == 0)
            continue;
 
        findCut(u);
    }
}
 
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
 
set<int> minCut;
 
int main() {
    cin >> h >> w;
ww = w;
    n = w * h;
    m = 0;
 
    string str;
 
    for (int i = 0; i < h; i++) {
        cin >> str;
 
        for (int j = 0; j < w; j++) {
            matrix[i][j] = str[j];
        }
    }
 
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int v = i * w + j;
 
            if (matrix[i][j] == 'A')
                s = v;
            if (matrix[i][j] == 'B')
                t = v;
 
            if (matrix[i][j] != '.') {
                e[m] = edge(v, v + n, INF);
                ans[m] = INF;
 
                g[v].push_back(m);
 
                m++;
            } else {
                e[m] = edge(v, v + n, 1);
                ans[m] = 1;
 
                g[v].push_back(m);
 
                m++;
            }
 
            if (matrix[i][j] == '#')
                continue;
 
            for (int k = 0; k < 4; k++) {
                int newI = i + dy[k];
                int newJ = j + dx[k];
 
                if (newI < 0 || newJ < 0 || newI >= h || newJ >= w)
                    continue;
 
                if (matrix[newI][newJ] == '#')
                    continue;
 
                int u = newI * w + newJ;
 
                e[m] = edge(v + n, u, INF);
                ans[m] = INF;
 
                g[v + n].push_back(m);
 
                m++;
            }
        }
    }
 
    for (int i = 0; i < m; i++) {
        e[i + m] = edge(e[i].u, e[i].v, 0);
        ans[i + m] = 0;
 
        g[e[i].u].push_back(i + m);
    }
 
    fill(used, used + N, false);
 
    while (dfs(s, 1e9) != 0) {
        fill(used, used + N, false);
    }
 
    long long maxFlow = 0;
 
    for (auto x : g[s]) {
        if (x >= m)
            continue;
 
        edge vu_edge = e[x];
 
        maxFlow += (long long)vu_edge.w - (long long)ans[x];
    }
 
    if (maxFlow >= (long long)INF) {
        cout << -1;
        return 0;
    }
 
    fill(used, used + N, false);
 
    findCut(s);
 
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i])
            continue;
 
        for (int x : g[i]) {
            edge vu_edge = e[x];
            int u = vu_edge.u;
 
            if (x >= m)
                continue;
 
            if (used[u])
                continue;
 
            minCut.insert(e[x % m].u % n);
        }
    }
 
    cout << minCut.size() << "\n";
 
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int v = i * w + j;
 
            if (minCut.count(v) != 0) {
                cout << "+";
            } else {
                cout << matrix[i][j];
            }
        }
 
        cout << "\n";
    }
 
    return 0;
}