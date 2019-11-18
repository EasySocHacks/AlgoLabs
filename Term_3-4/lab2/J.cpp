#include <bits/stdc++.h>
using namespace std;

const int LEN = 100009;

int n, m;
vector <int> g[LEN];

int gr[LEN];

void dfs(int v) {
    for (int u : g[v]) {
        if (gr[u] == -1)
            dfs(u);
    }

    set <int> st;

    for (int u : g[v]) {
        st.insert(gr[u]);
    }

    for (int i = 0;; i++) {
        if (st.count(i) != 0) {
            continue;
        }

        gr[v] = i;
        break;
    }
}

int main() {
    cin >> n >> m;

    fill(gr, gr + LEN, -1);

    int v, u;

    for (int i = 0; i < m; i++) {
        cin >> v >> u;

        v--;
        u--;

        g[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        if (gr[i] == -1)
            dfs(i);
    }

    for (int i = 0; i < n; i++)
        cout << gr[i] << "\n";

    return 0;
}
