#include <bits/stdc++.h>
using namespace std;

const int LEN = 300009;

void solve(int n, int m) {
    vector <int> g[n + 1];
    vector <int> rg[n + 1];

    int v, u;
    int win[n + 1];
    int counter[n + 1];

    for (int i = 0; i < n + 1; i++) {
        win[i] = -1;
        counter[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> v >> u;

        v--;
        u--;

        g[v].push_back(u);
        rg[u].push_back(v);
    }

    queue <int> q;

    for (int i = 0; i < n; i++) {
        if (g[i].size() == 0) {
            q.push(i);
            win[i] = 0;
        }
    }

    while (!q.empty()) {
        v = q.front();
        q.pop();

        if (win[v] == 0) {
            for (int u : rg[v]) {
                if (win[u] != -1)
                    continue;

                win[u] = 1;
                q.push(u);
            }
        } else {
            for (int u : rg[v]) {
                counter[u]++;

                if (counter[u] == g[u].size()) {
                    win[u] = 0;
                    q.push(u);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        switch (win[i]) {
            case -1: cout << "DRAW\n"; break;
            case 0: cout << "SECOND\n"; break;
            case 1: cout << "FIRST\n"; break;
        }
    }
}

int main() {
    int n, m;

    while (cin >> n >> m) {
        solve(n, m);
        cout << "\n";
    }

    return 0;
}
