#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 3e18;
const int LEN = 1e5;

int n;
ll a[LEN];
ll tree[4 * LEN];
ll memAdd[4 * LEN];
ll memSet[4 * LEN];
int sz = 1;

void push(int v) {
    if (memSet[v] != INF) {
        tree[v] = memSet[v];

        if (v >= sz) {
            memSet[v] = INF;
        } else {
            memSet[v * 2] = memSet[v];
            memSet[v * 2 + 1] = memSet[v];

            memAdd[v * 2] = 0;
            memAdd[v * 2 + 1] = 0;

            memSet[v] = INF;
        }
    }

    if (memAdd[v] != 0) {
        tree[v] += memAdd[v];

        if (v >= sz) {
            memAdd[v] = 0;
        } else {
            memAdd[v * 2] += memAdd[v];
            memAdd[v * 2 + 1] += memAdd[v];

            memAdd[v] = 0;
        }
    }
}

void setTree(int v, int l, int r, int a, int b, ll x) {
    push(v);

    if (r < a || l > b)
        return;

    if (a <= l && r <= b) {
        memSet[v] = x;
        push(v);
        return;
    }

    int m = (l + r) / 2;
    setTree(v * 2, l, m, a, b, x);
    setTree(v * 2 + 1, m + 1, r, a, b, x);

    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

void addTree(int v, int l, int r, int a, int b, ll x) {
    push(v);

    if (r < a || l > b)
        return;

    if (a <= l && r <= b) {
        memAdd[v] += x;
        push(v);
        return;
    }

    int m = (l + r) / 2;
    addTree(v * 2, l, m, a, b, x);
    addTree(v * 2 + 1, m + 1, r, a, b, x);

    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

ll getMin(int v, int l, int r, int a, int b) {
    if (r < a || l > b)
        return INF;

    push(v);

    if (a <= l && r <= b) {
        return tree[v];
    }

    int m = (l + r) / 2;
    return min(getMin(v * 2, l, m, a, b), getMin(v * 2 + 1, m + 1, r, a, b));
}

int main() {
    for (int i = 0; i < 4 * LEN; i++) {
        memAdd[i] = 0;
        memSet[i] = INF;
    }

    while (sz < LEN) sz *= 2;

    for (int i = 0; i < 4 * LEN; i++)
        tree[i] = INF;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
        tree[sz + i] = a[i];

    for (int i = sz - 1; i >= 1; i--) {
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }

    string query;
    int x, y, z;

    while (cin >> query) {
        if (query == "set") {
            cin >> x >> y >> z;
            setTree(1, 1, sz, x, y, z);
        }

        if (query == "add") {
            cin >> x >> y >> z;
            addTree(1, 1, sz, x, y , z);
        }

        if (query == "min") {
            cin >> x >> y;
            cout << getMin(1, 1, sz, x, y) << "\n";
        }
    }

    return 0;
}
