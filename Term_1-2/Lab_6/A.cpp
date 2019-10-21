#include <bits/stdc++.h>
using namespace std;

const int LEN = 1e5 + 9;

int n;
int up[LEN][20];
vector <int> g[LEN];

void dfs(int v) {
    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        dfs(u);
    }
}

int main() {
    cin >> n;

    int p;
    for (int i = 0; i < n; i++) {
        cin >> p;

        up[i + 1][0] = p;
        g[p].push_back(i + 1);
    }

    dfs(0);

    for (int i = 1; i <= n; i++) {
        cout << i << ": ";

        for (int j = 0; j < 20; j++) {
            if (up[i][j] == 0)
                continue;

            cout << up[i][j] << " ";
        }

        cout << "\n";
    }

    return 0;
}