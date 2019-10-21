#include <bits/stdc++.h>
using namespace std;

#define int long long

const int LEN = 4e5 + 9;
const int ADD = 2e5 + 1;

struct seg {
    int y, x1, x2, segNum, type;

    seg() {
        y = 0;
        x1 = 0;
        x2 = 0;
        segNum = 0;
        type = 0;
    }

    seg(int y, int x1, int x2, int segNum, int type) {
        this->y = y;
        this->x1 = x1;
        this->x2 = x2;
        this->segNum = segNum; /* 0 - OPEN | 1 - CLOSE */
        this->type = type;
    }
};

struct Node {
    int maxx, pos;
    int mem;

    Node() {
        maxx = 0;
        pos = -1;
        mem = 0;
    }
};

bool cmp (seg a, seg b) {
    if (a.y == b.y) {
        return a.type < b.type;
    }

    return a.y < b.y;
}

Node operator + (Node a, Node b) {
    Node c;

    c.maxx = max(a.maxx, b.maxx);

    if (a.maxx > b.maxx) {
      c.pos = a.pos;
    } else {
        c.pos = b.pos;
    }

    return c;
}

int n;
seg border[(int)(1e5 + 9)];
Node tree[4 * LEN];
int sz = 1;

void push(int v) {
    tree[v].maxx += tree[v].mem;
    if (v < sz) {
        tree[v * 2].mem += tree[v].mem;
        tree[v * 2 + 1].mem += tree[v].mem;
    }

    tree[v].mem = 0;
}

void addTree(int v, int l, int r, int a, int b, int c) {
    push(v);

    if (r < a || l > b)
        return;

    if (a <= l && r <= b) {
        tree[v].mem += c;
        push(v);
        return;
    }

    int m = (l + r) / 2;
    addTree(v * 2, l, m, a, b, c);
    addTree(v * 2 + 1, m + 1, r, a, b, c);

    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}
/*
Node getAns(int v, int l, int r, int a, int b) {
    push(v);

    if (r < a || l > b)
        return Node();

    if (a <= l && r <= b) {
        return tree[v];
    }

    int m = (l + r) / 2;

    return getAns(v * 2, l, m, a, b) + getAns(v * 2 + 1, m + 1, r, a, b);
}
*/
signed main() {
    while (sz <= LEN)
        sz *= 2;

    for (int i = sz; i < 4 * LEN; i++) {
        tree[i].pos = i - sz + 1;
        tree[i].mem = 0;
        tree[i].maxx = 0;
    }

    for (int i = sz - 1; i >= 1; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];

    cin >> n;
    int x1, y1, x2, y2;

    for (int i = 0; i < 2 * n; i += 2) {
        cin >> x1 >> y1 >> x2 >> y2;

        x1 += ADD;
        y1 += ADD;
        x2 += ADD;
        y2 += ADD;

        border[i] = seg(y2, x1, x2, i, 1);
        border[i + 1] = seg(y1, x1, x2, i, 0);
    }

    sort(border, border + 2 * n, cmp);

    int maxx = -1;
    int posX = -1;
    int posY = -1;

    for (int i = 0; i < 2 * n; i++) {
        if (border[i].type == 0) {
            addTree(1, 1, sz, border[i].x1, border[i].x2, 1);
        } else {
            addTree(1, 1, sz, border[i].x1, border[i].x2, -1);
        }

        if (maxx < tree[1].maxx) {
            maxx = tree[1].maxx;
            posX = tree[1].pos - ADD;
            posY = border[i].y - ADD;
        }
    }

    cout << maxx << "\n" << posX << " " << posY;

    return 0;
}
