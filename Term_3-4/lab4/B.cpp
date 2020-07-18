#include <bits/stdc++.h>
using namespace std;

const int LEN = 509;

int n;

struct dot {
    int x, y;

    dot() {
        x = 0;
        y = 0;
    }

    dot(int x, int y) : x(x), y(y) {}
};

int dist(dot a, dot b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int getTime(string str) {
    int h = (str[0] - '0') * 10 + (str[1] - '0');
    int m = (str[3] - '0') * 10 + (str[4] - '0');

    return h * 60 + m;
}

int times[2 * LEN];
dot coords[2 * LEN];

bool used[2 * LEN];

vector <int> g[2 * LEN];
int rg[2 * LEN];

int col = 1;
int color[LEN];

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

int gg[2 * LEN];

int getAns(int v) {
    used[v] = true;

    if (gg[v] == -1) {
        color[v] = col;
        col++;
        return color[v];
    }

    if (used[gg[v]]) {
        color[v] = color[gg[v]];
        return color[v];
    }

    color[v] = getAns(gg[v]);

    return color[v];
}

int main() {
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);

    cin >> n;

    int a, b, c, d;
    string str;

    for (int i = 0; i < n; i++) {
        cin >> str >> a >> b >> c >> d;

        times[i] = getTime(str);

        coords[i] = dot(a, b);
        coords[i + n] = dot(c, d);

        times[i + n] = times[i] + dist(coords[i], coords[i + n]);
    }

    for (int i = 0; i < n; i++) {
        g[i].push_back(i + n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (times[j] > times[i + n] + dist(coords[j], coords[i + n])) {
                g[i + n].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        rg[i] = -1;
        rg[i + n] = i;
    }

    for (int i = 0; i < 2 * n; i++) {
        if (dfs(i))
            fill(used, used + 2 * LEN, false);
    }

    fill(gg, gg + 2 * LEN, -1);

    for (int i = 0; i < 2 * n; i++) {
        if (rg[i] != -1) {
            gg[rg[i]] = i;
        }
    }

    fill(used, used + 2 * LEN, false);

    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;

        getAns(i);
    }

    cout << (col - 1);

    return 0;
}
