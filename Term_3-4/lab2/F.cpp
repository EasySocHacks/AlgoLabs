#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 100009;
const ll INF = 1e18;

int n, m;
vector <pair<int, int>> g[LEN];
int a, b, c;

vector <ll> solve(int s) {
    vector <ll> d(LEN, INF);

    set <pair<ll, int>> st;
    d[s] = 0;
    st.insert({0, s});

    while(!st.empty()) {
        int v = (*st.begin()).second;
        ll w = (*st.begin()).first;

        st.erase(st.begin());

        for (int i = 0; i < g[v].size(); i++) {
            int u = g[v][i].first;
            ll w = g[v][i].second;

            if (d[u] > d[v] + w) {
                st.erase({d[u], u});
                d[u] = d[v] + w;
                st.insert({d[u], u});
            }
        }
    }

    return d;
}

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

    cin >> a >> b >> c;

    a--;
    b--;
    c--;

    vector <ll> d_a = solve(a);
    vector <ll> d_b = solve(b);
    vector <ll> d_c = solve(c);

    set <ll> ans;

    if (d_a[b] == INF || d_a[c] == INF || d_b[c] == INF) {
        cout << -1;
        return 0;
    }

    ans.insert(d_a[b] + d_b[c]);
    ans.insert(d_a[c] + d_c[b]);
    ans.insert(d_b[a] + d_a[c]);
    ans.insert(d_b[c] + d_c[a]);
    ans.insert(d_c[a] + d_a[b]);
    ans.insert(d_c[b] + d_b[a]);

    cout << (*ans.begin());

    return 0;
}
