#include <bits/stdc++.h>
using namespace std;

const int LEN = 159;

int k;

int n, m;
set <pair<int, int>> ng;
vector <int> g[LEN];
int rg[LEN];
bool used[LEN];
vector <int> ansM, ansN;
bool markN[LEN], markM[LEN];

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;

    for (int u : g[v]) {
        if (rg[u] == -1 || dfs(rg[u])) {
            rg[u] = v;
            return true;
        }
    }

    return false;
}

void dfs2(int v) {
    if (markM[v])
        return;

    markM[v] = true;

    for (int u : g[v]) {
        if (markN[u])
            continue;
        markN[u] = true;

        if (rg[u] != -1)
            dfs2(rg[u]);
    }
}

void clearUsed() {
    fill(used, used + LEN, false);
}

void clearData() {
    ansM.clear();
    ansN.clear();
    ng.clear();
    for (int i = 0; i < LEN; i++) {
        g[i].clear();
        rg[i] = -1;
        clearUsed();
        markN[i] = false;
        markM[i] = false;
    }
}

void solve() {
    cin >> m >> n;

    clearData();

    int x;
    for (int i = 0; i < m; i++) {
        while (true) {
            cin >> x;

            if (x == 0)
                break;

            x--;

            ng.insert({i, x});
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (ng.count({i, j}) == 0) {
                g[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (dfs(i))
            clearUsed();
    }

    clearUsed();

    for (int i = 0; i < n; i++) {
        if (rg[i] == -1) {
            continue;
        }
        used[rg[i]] = true;
    }

    for (int i = 0; i < m; i++) {
        if (!used[i]) {
            dfs2(i);
        }
    }

    for (int i = 0; i < m; i++) {
        if (markM[i])
            ansM.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        if (!markN[i])
            ansN.push_back(i);
    }

    cout << ansN.size() + ansM.size() << "\n";
    cout << ansM.size() << " " << ansN.size() << "\n";

    for (int x : ansM) cout << (x + 1) << " "; cout << "\n";
    for (int x : ansN) cout << (x + 1) << " "; cout << "\n";
    cout << "\n";
}

int main() {
    freopen("birthday.in", "r", stdin);
    freopen("birthday.out", "w", stdout);

    cin >> k;

    for (int i = 0; i < k; i++) {
        solve();
    }

    return 0;
}
