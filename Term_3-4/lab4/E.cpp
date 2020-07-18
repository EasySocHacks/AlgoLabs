#include <bits/stdc++.h>
using namespace std;

const int LEN = 109;

int n, v;

struct dot {
    long long x, y;

    dot() {
        x = 0;
        y = 0;
    }

    dot(int x, int y) : x(x), y(y) {}
};

struct struc {
    dot v;
    int time;

    struc() {
        v = dot();
        time = 0;
    }

    struc(dot v, int time) : v(v), time(time) {}
};

int getTime(string str) {
    int h = (str[0] - '0') * 10 + (str[1] - '0');
    int m = (str[3] - '0') * 10 + (str[4] - '0');

    return h * 60 + m;
}

bool cmp (struc a, struc b) {
    return a.time < b.time;
}

struc st[LEN];

vector <int> g[LEN];
int rg[LEN];
bool used[LEN];

int col = 1;
int color[LEN];
int gg[LEN];

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
    freopen("ufo.in", "r", stdin);
    freopen("ufo.out", "w", stdout);

    cin >> n >> v;

    string str;
    int x, y;

    for (int i = 0; i < n; i++) {
        cin >> str >> x >> y;

        st[i] = struc(dot(x, y), getTime(str));
    }

    sort(st, st + n, cmp);

    fill(rg, rg + LEN, -1);

    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            long long diff = abs(st[i].time - st[j].time);
            long long len = pow((st[i].v.x - st[j].v.x), 2) + pow((st[i].v.y - st[j].v.y), 2);

            if (len * (long long) 3600 <= diff * diff * (long long) v * (long long) v) {
                g[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dfs(i))
            fill(used, used + LEN, false);
    }

    fill(gg, gg + LEN, -1);

    for (int i = 0; i < n; i++) {
        if (rg[i] == -1)
            continue;
        gg[rg[i]] = i;
    }

    fill(used, used + LEN, false);

    for (int i = 0; i < n; i++) {
        if (!used[i])
            getAns(i);
    }

    cout << (col - 1);

    return 0;
}
