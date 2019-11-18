#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 30009;
const ll INF = 1e18;

bool used[LEN];

ll d_v[LEN];
int n, m;
vector <pair<int, int>> g[LEN];

int main() {
    cin >> n >> m;

    int v, u, w;
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;
        v--;
        u--;

        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }

    for (int i = 1; i < LEN; i++)
        d_v[i] = INF;

    set <pair<int, int>> st;

    st.insert({0, 0});

    while (!st.empty()) {
        int v = (*st.begin()).second;
        int dist = (*st.begin()).first;

        st.erase(st.begin());

        for (int i = 0; i < g[v].size(); i++) {
            int u = g[v][i].first;
            int w = g[v][i].second;

            if (d_v[u] > d_v[v] + w) {
                st.erase({d_v[u], u});
                d_v[u] = d_v[v] + w;
                st.insert({d_v[u], u});
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << d_v[i] << " ";

    return 0;
}
