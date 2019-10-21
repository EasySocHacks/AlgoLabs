#include <iostream>
using namespace std;

const int LEN = 1e5 + 9;

int n, m;
int sz = 1;

int tree[4 * LEN];

int getAns(int v, int l, int r, int a, int b) {
    if (r < a || l > b)
        return -1;

    if (a <= l && r <= b) {
        return tree[v];
    }

    int mid = (l + r) / 2;
    int x = getAns(v * 2, l, mid, a, b);
    int y = getAns(v * 2 + 1, mid + 1, r, a, b);

    if (x == -1)
        return y;
    return x;
}

void pushUp(int v) {
    if (v <= 0)
        return;
    if (v >= sz)
        return;

    if (tree[v * 2] == -1)
        tree[v] = tree[v * 2 + 1];
    else
        tree[v] = tree[v * 2];

    pushUp(v / 2);
}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);

    cin >> n >> m;

    while (sz <= LEN)
        sz *= 2;

    for (int i = 4 * LEN - 1; i >= 1; i--) {
        if (i >= sz) {
            tree[i] = i - sz;
        } else {
            if (tree[i * 2] != -1)
                tree[i] = tree[i * 2];
            else
                tree[i] = tree[i * 2 + 1];
        }
    }

    string query;
    int x;

    for (int i = 0; i < m; i++) {
        cin >> query >> x;

        if (query == "enter") {
            int pos = getAns(1, 1, sz, x, n);

            if (pos == -1) {
                pos = getAns(1, 1, sz, 1, x);
            }

            tree[sz + pos] = -1;
            pushUp((sz + pos) / 2);

            cout << (pos + 1) << "\n";
        }

        if (query == "exit") {
            tree[sz + x - 1] = x - 1;
            pushUp((sz + x - 1) / 2);
        }
    }

    return 0;
}
