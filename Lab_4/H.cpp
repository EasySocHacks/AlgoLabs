#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 1e5 + 9;
const ll INF = 1e17;

struct Query {
    int x, y, c;

    Query() {
        x = 0;
        y = 0;
        c = 0;
    }

    Query(int X, int Y, int C) {
        x = X;
        y = Y;
        c = C;
    }
};

bool operator < (Query a, Query b) {
    return a.c < b.c;
}

int n, m;
ll tree[4 * LEN];
ll mem[4 * LEN];
Query qs[LEN];
int sz = 1;

void push(int v) {
    if (mem[v] == INF)
        return;

    if (v < sz) {
        mem[v * 2] = mem[v];
        mem[v * 2 + 1] = mem[v];
    }

    tree[v] = mem[v];
    mem[v] = INF;
}

void setTree(int v, int l, int r, int a, int b, int c) { //cout << v << " : " << l << " " << r << " | " << a << " " << b << " | " << c << "\n";
    push(v);

    if (r < a || l > b)
        return;

    if (a <= l && r <= b) {
        mem[v] = c;
        push(v);
        return;
    }

    int m = (l + r) / 2;
    setTree(v * 2, l, m, a, b, c);
    setTree(v * 2 + 1, m + 1, r, a, b, c);

    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

ll getMin(int v, int l, int r, int a, int b) {
    push(v);

    if (r < a || l > b)
        return INF;

    if (a <= l && r <= b) {
        return tree[v];
    }

    int m = (l + r) / 2;
    return min(getMin(v * 2, l, m, a, b), getMin(v * 2 + 1, m + 1, r, a, b));
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);

    while (sz <= LEN)
        sz *= 2;
    cin >> n >> m;

    for (int i = 0; i < 4 * LEN; i++) {
        tree[i] = INF;
        mem[i] = INF;
    }

    int a, b, q;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> q;

        qs[i] = Query(a, b, q);
    }

    sort(qs, qs + m);

    for (int i = 0; i < m; i++) {//cout << qs[i].x << " | " << qs[i].y << " | " << qs[i].c << "\n";
        setTree(1, 1, sz, qs[i].x, qs[i].y, qs[i].c);
    }

    for (int i = 1; i < 4 * LEN; i++)
        push(i);

    //cout << tree[sz] << " " << tree[sz + 1] << " " << tree[sz + 2] << "\n";

    for (int i = 0; i < m; i++) {
        if (getMin(1, 1, sz, qs[i].x, qs[i].y) != qs[i].c) {
            cout << "inconsistent";
            return 0;
        }
    }

    cout << "consistent\n";
    for (int i = 0; i < n; i++) {
        if (tree[i + sz] == INF)
            cout << ((1 << 31) - 1) << " ";
        else cout << tree[i + sz] << " ";
    }

    return 0;
}
