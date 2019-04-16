#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 500009;

int n;
int a[LEN];
ll tree[4 * LEN];
int sz = 1;

void setTree(int v, int x) {
    v += sz;
    tree[v] = x;

    v /= 2;
    while (v != 0) {
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
        v /= 2;
    }
}

ll getSumm(int v, int l, int r, int a, int b) {
    if (r < a || l > b)
        return 0;

    if (a <= l && r <= b)
        return tree[v];

    int m = (l + r) / 2;
    return getSumm(v * 2, l, m, a, b) + getSumm(v * 2 + 1, m + 1, r, a, b);
}

int main() {
    while (sz < LEN) sz *= 2;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
        tree[sz + i] = a[i];

    for (int i = sz - 1; i >= 1; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    string query;
    int x, y;

    while (cin >> query) {
        if (query == "set") {
            cin >> x >> y;
            setTree(x - 1, y);
        }

        if (query == "sum") {
            cin >> x >> y;

            cout << getSumm(1, 1, sz, x, y) << "\n";
        }
    }

    return 0;
}
