#include <bits/stdc++.h>
using namespace std;

const int LEN = 5009;
const int INF = 1e9;

int n, m, e;
int wn[LEN], wm[LEN];
bool used[LEN];
pair <int, int> rg[LEN];

vector <pair<int, int>> g[LEN];

bool cmp (int a, int b) {
    return wn[a] > wn[b];
}

bool cmp3 (pair<int, int> a, pair<int, int> b) {
    return wm[a.first] > wm[b.first];
}

pair<int, int> dfs(int v) {
    if (used[v])
        return {-INF, -1};
    used[v] = true;

    int maxVal = -INF;
    int needU = -1;
    for (pair <int, int> uu : g[v]) {
        int u = uu.first;

        if (rg[u].first == -1) {
            if (maxVal < wm[u]) {
                maxVal = wm[u];
                needU = u;
            }
        } else {
            pair<int, int> tmp = dfs(rg[u].first);

            if (tmp.first != -INF && maxVal < tmp.first) {
                maxVal = tmp.first;
                needU = tmp.second;
            }
        }
    }

    return {maxVal, needU};
}

bool changePath(int v, int needU) {
    if (used[v])
        return false;
    used[v] = true;

    for (pair <int, int> uu : g[v]) {
        int u = uu.first;

        if (rg[u].first == -1 && u == needU) {
            rg[u] = {v, uu.second};
            return true;
        }

        if (rg[u].first != -1 && changePath(rg[u].first, needU)) {
            rg[u] = {v, uu.second};
            return true;
        }
    }

    return false;
}

long long w = 0;
vector <int> ans(0);
vector <int> f(0);

int main() {
    cin >> n >> m >> e;

    for (int i = 0; i < n; i++) {
        cin >> wn[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> wm[i];
    }

    int a, b;

    for (int i = 0; i < e; i++) {
        cin >> a >> b;

        a--;
        b--;

        g[a].push_back({b, i + 1});
    }

    for (int i = 0; i < n; i++) {
        f.push_back(i);
    }

    sort(f.begin(), f.end(), cmp);

    for (int i = 0; i < n; i++) {
        if (!g[i].empty())
            sort(g[i].begin(), g[i].end(), cmp3);
    }

    fill(used, used + LEN, false);

    for  (int i = 0; i < LEN; i++) {
        rg[i] = {-1, -1};
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> tmp = dfs(f[i]);

        if (tmp.first != -INF) {
            fill(used, used + LEN, false);
            changePath(f[i], tmp.second);
        }

        fill(used, used + LEN, false);
    }

    for (int i = 0; i < m; i++) {
        if (rg[i].first == -1)
            continue;

        ans.push_back({rg[i].second});
        w += wm[i];
        w += wn[rg[i].first];
    }

    cout << w << "\n";
    cout << ans.size() << "\n";
    for (int v : ans) {
        cout << v << " ";
    }

    return 0;
}
