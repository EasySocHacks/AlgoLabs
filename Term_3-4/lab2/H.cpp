#include <bits/stdc++.h>
using namespace std;

const int LEN = 100009;

int n, m, s;
vector <int> g[LEN];

int win[LEN];

void dfs(int v) {

    if (g[v].size() == 0) {
        win[v] = 0;
        return;
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (win[u] == -1)
            dfs(u);
    }

    bool hasLose = false;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (win[u] == 0)
            hasLose = true;
    }

    if (hasLose)
        win[v] = 1;
    else
        win[v] = 0;
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    cin >> n >> m >> s;

    for (int i = 0; i < LEN; i++)
        win[i] = -1;

    s--;

    int v, u;
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;

        g[v].push_back(u);
    }

    dfs(s);

    if (win[s] == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }

    return 0;
}
