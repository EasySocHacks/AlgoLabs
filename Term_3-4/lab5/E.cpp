#include <bits/stdc++.h>
using namespace std;
 
const int K = 109;
const int N = 59;
const int INF = 1e8;
 
struct edge {
    int a, b, d, w, rx;
    bool canGo;
 
    edge() {
        a = 0;
        b = 0;
        d = 0;
        w = 0;
        rx = 0;
        canGo = false;
    }
 
    edge(int a, int b, int d, int w, bool canGo, int rx) : a(a), b(b), d(d), w(w), canGo(canGo), rx(rx) {}
};
 
int n, mm, m, k, s, t, td;
vector <edge> e;
vector <int> ans;
vector <int> memAns;
vector <int> g[N][N][K];
 
bool used[N][N][K];
map <int, vector<pair<int, int>>> mp;
 
void clearUsed() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                used[i][j][k] = false;
            }
        }
    }
}
 
void clearAns() {
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = memAns[i];
    }
}
 
int dfs(int va, int vb, int d, int minW) {
    used[va][vb][d] = true;
 
    if (d > td)
        return 0;
 
    if (va == t && vb == t && d == td) {
        return minW;
    }
 
    for (auto x : g[va][vb][d]) {
        edge vu_edge = e[x];
        int ua = vu_edge.a;
        int ub = vu_edge.b;
        int w = ans[x];
        int ud = vu_edge.d;
 
        if (used[ua][ub][ud])
            continue;
 
        if (w == 0)
            continue;
 
        int ret = dfs(ua, ub, ud, min(minW, w));
 
        if (ret != 0) {
            ans[x] -= ret;
            ans[vu_edge.rx] += ret;
 
            return ret;
        }
    }
 
    return 0;
}
 
bool findPath(int va, int vb, int d, int k, int last) {
    used[va][vb][d] = true;
 
    if (va == t && vb == t && d == td) {
        return true;
    }
 
    for (auto x : g[va][vb][d]) {
        edge vu_edge = e[x];
        int ua = vu_edge.a;
        int ub = vu_edge.b;
        int w = ans[x];
        int ud = vu_edge.d;
 
        if (!vu_edge.canGo)
            continue;
 
        if (used[ua][ub][ud])
            continue;
 
        if (w >= vu_edge.w)
            continue;
 
        bool b = findPath(ua, ub, ud, k, (ua == ub ? ua : last));
 
        if (b) {
            ans[x] += 1;
            ans[vu_edge.rx] -= 1;
 
            if (ua == ub &&  va != vb && ua != last) { 
                mp[ud].push_back({k, ua});
            }
 
            return true;
        }
    }
 
    return false;
}
 
int main() {
    cin >> n >> mm >> k >> s >> t;
 
    m = 0;
 
    s--;
    t--;
 
    int a, b;
 
    for (int i = 0; i < mm; i++) {
        cin >> a >> b;
 
        a--;
        b--;
 
        for (int j = 0; j < K - 2; j++) {
            e.push_back(edge(a, b, j, 1, true, m + 5));
            ans.push_back(1);
            g[a][a][j].push_back(m);
            m++;
 
            e.push_back(edge(a, b, j, 1, true, m + 5));
            ans.push_back(1);
            g[b][b][j].push_back(m);
            m++;
 
            e.push_back(edge(b, a, j, 1, true, m + 5));
            ans.push_back(1);
            g[a][b][j].push_back(m);
            m++;
 
            e.push_back(edge(a, a, j + 1, 1, true, m + 5));
            ans.push_back(1);
            g[b][a][j].push_back(m);
            m++;
 
            e.push_back(edge(b, b, j + 1, 1, true, m + 5));
            ans.push_back(1);
            g[b][a][j].push_back(m);
            m++;
 
            //-----------------------------
 
            e.push_back(edge(a, a, j, 0, false, m - 5));
            ans.push_back(0);
            g[a][b][j].push_back(m);
            m++;
 
            e.push_back(edge(b, b, j, 0, false, m - 5));
            ans.push_back(0);
            g[a][b][j].push_back(m);
            m++;
 
            e.push_back(edge(a, b, j, 0, false, m - 5));
            ans.push_back(0);
            g[b][a][j].push_back(m);
            m++;
 
            e.push_back(edge(b, a, j, 0, false, m - 5));
            ans.push_back(0);
            g[a][a][j + 1].push_back(m);
            m++;
 
            e.push_back(edge(b, a, j, 0, false, m - 5));
            ans.push_back(0);
            g[b][b][j + 1].push_back(m);
            m++;
        }
    }
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < K - 2 ; j++) {
            e.push_back(edge(i, i, j + 1, INF, true, m + 1));
            ans.push_back(INF);
            g[i][i][j].push_back(m);
            m++;
 
            //---------------------------
 
            e.push_back(edge(i, i, j, 0, false, m - 1));
            ans.push_back(0);
            g[i][i][j + 1].push_back(m);
            m++;
        }
    }
 
    for (int i = 0; i < ans.size(); i++) {
        memAns.push_back(ans[i]);
    }
 
    for (int i = 0; i < K - 2; i++) {
        td = i;
 
        clearAns();
        clearUsed();
 
        while (dfs(s, s, 0, INF) != 0) {
            clearUsed();
        }
 
        int maxFlow = 0;
 
        for (auto x : g[s][s][0]) {
            edge vu_edge = e[x];
 
            if (!vu_edge.canGo)
                continue;
 
            maxFlow += vu_edge.w - ans[x];
        }
 
        if (maxFlow >= k) {
            clearUsed();
 
            for (int i = 0; i < k; i++) {
                findPath(s, s, 0, i, s);
                clearUsed();
            }
 
            int d = 1;
            for (; mp.count(d) != 0; d++) {}
            d--;
 
            cout << d << "\n";
 
            for (int i = 1; i <= d; i++) {
                cout << mp[i].size() << "  ";
 
                for (auto x : mp[i]) {
                    cout << x.first + 1 << " " << x.second + 1 << "  ";
                }
 
                cout << "\n";
            }
 
            break;
        }
    }
 
    return 0;
}