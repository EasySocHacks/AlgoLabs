#include <bits/stdc++.h>
using namespace std;

const int LEN = 100009;

int n, r;
map <pair<int, int>, int> mp;
vector <int> g[LEN];

bool used[LEN];
int win[LEN];

void dfs(int v) {
    used[v] = true;

    if (g[v].size() == 1 && v != r) {
        win[v] = 0;
        return;
    }

    vector <int> vec;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (used[u])
            continue;

        dfs(u);
        vec.push_back(win[u]);
    }

    int ans = 0;
    for (int x : vec) {
        ans ^= (x + 1);
    }

    win[v] = ans;
}

pair <int, int> getAns(int v, int need) {
    used[v] = true;

    int needU;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (used[u])
            continue;

        if ((win[v] ^ (win[u] + 1) ^ need) <=  (win[u] + 1)) {
            needU = u;
        }
    }

    if ((win[v] ^ (win[needU] + 1) ^ need) == 0) {
        return {needU, v};
    }

    return getAns(needU, (win[v] ^ (win[needU] + 1) ^ need) - 1);
}

int main() {
    cin >> n >> r;

    if (n == 1) {
        cout << 2;
        return 0;
    }

    r--;

    int v, u;

    for (int i = 0; i < n - 1; i++) {
        cin >> v >> u;

        v--;
        u--;

        g[v].push_back(u);
        g[u].push_back(v);

        mp[{v, u}] = i;
        mp[{u, v}] = i;
    }

    dfs(r);

    for (int i = 0; i < LEN; i++)
        used[i] = false;

    if (win[r] == 0) {
        cout << 2;
    } else {
        cout << "1\n";

        cout << (mp[getAns(r, 0)] + 1);
    }

    return 0;
}
