#include <bits/stdc++.h>
using namespace std;

const int LEN = 259;

int n, m;
vector <int> g[LEN];
int rg[LEN];
bool used[LEN];

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

int main() {
    cin >> n >> m;

    int v;

    for (int i = 0; i < n; i++) {
        while (true) {
            cin >> v;

            if (v == 0)
                break;

            v--;

            g[i].push_back(v);
        }
    }

    fill(rg, rg + LEN, -1);

    for (int i = 0; i < n; i++) {
        if (dfs(i))
            fill(used, used + LEN, false);
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (rg[i] != -1)
            ans++;
    }

    cout << ans << "\n";
    for (int i = 0; i < m; i++) {
        if (rg[i] == -1)
            continue;

        cout << (rg[i] + 1) << " " << (i + 1) << "\n";
    }

    return 0;
}
