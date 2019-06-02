#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;
#define pb push_back

const int LEN = 1e5 + 9;

int start;
int n, m;;
int up[LEN][20];
vector <int> g[LEN];
int pos[LEN];
int h[LEN];

int globalPos = 0;

void dfs(int v, int prev, int height) {
    for (int i = 1; i < 20; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];

    h[v] = height;

    for (int u : g[v]) {
        if (u == prev)
            continue;

        dfs(u, v, height + 1);
    }

    pos[v] = globalPos;
    globalPos++;
}

int lca(int v, int u) {
    if (h[v] < h[u])
        swap(v, u);

    int k = 19;
    while (h[v] > h[u]) {
        int x = up[v][k];
        if (h[x] < h[u]) {
            k--;
            continue;
        }

        v = x;
        k--;
        continue;
    }

    if (v == u)
        return v;

    k = 19;
    while (up[v][0] != up[u][0]) {
        int x = up[v][k];
        int y = up[u][k];

        if (x == y) {
            k--;
            continue;
        }

        v = x;
        u = y;
        k--;
    }

    return up[v][0];
}

bool cmp(int x, int y) {
    return pos[x] < pos[y];
}

int main() {
    scanf("%d", &n);

    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);

        if (x == -1) {
            up[i][0] = i;
            start = i;
        } else {
            x--;
            up[i][0] = x;

            g[i].pb(x);
            g[x].pb(i);
        }
    }

    dfs(start, -1, 1);

    scanf("%d", &m);
    int k;
    vector <int> vec;

    for (int i = 0; i < m; i++) {
        vec.clear();

        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            x--;
            vec.pb(x);
        }

        sort(vec.begin(), vec.end(), cmp);

        int ans = 0;
        ans = h[vec[0]];

        for (int j = 1; j < vec.size(); j++) {
            int u = vec[j - 1];
            int v = vec[j];
            int l = lca(v, u);

            if (l == v)
                continue;

            ans += (h[v] - h[l]);
        }

        printf("%d\n", ans);
    }


    return 0;
}