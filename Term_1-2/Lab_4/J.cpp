#include <bits/stdc++.h>
using namespace std;

const int LEN = 1e6 + 9;

int n, m;
pair<int, int> tree[4 * LEN];
int mem[4 * LEN];
int sz = 1;

void push(int v)  {
    if (v >= sz) {
        tree[v].first = max(tree[v].first, mem[v]);
    } else {
        mem[v * 2] = max(mem[v * 2], mem[v]);
        mem[v * 2 + 1] = max(mem[v * 2 + 1], mem[v]);
    }

    if (tree[v].first < mem[v]) {
        tree[v].first = mem[v];
    }

    mem[v] = 0;
}

void update(int v) {
    if (v >= sz) {
        return;
    }

    if (tree[v].first > tree[v * 2].first && tree[v].first > tree[v * 2 + 1].first) {
        return;
    }

    if (tree[v * 2].first < tree[v * 2 + 1].first) {
        tree[v].first = tree[v * 2].first;
        tree[v].second = tree[v * 2].second;
    } else {
        tree[v].first = tree[v * 2 + 1].first;
        tree[v].second = tree[v * 2 + 1].second;
    }
}

void defend(int v, int l, int r, int a, int b, int c) {
    push(v);

    if (r < a || l > b) {
        return;
    }

    if (a <= l && r <= b) {
        mem[v] = max(mem[v], c);
        push(v);
        return;
    }

    int m = (l + r) / 2;
    defend(v * 2, l, m, a, b, c);
    defend(v * 2 + 1, m + 1, r, a, b, c);

    update(v);
}

pair<int, int> attack(int v, int l, int r, int a, int b) {
    push(v);

    if (r < a || l > b)
        return {1e9, -1};

    if (a <= l && r <= b)  {
        return tree[v];
    }

    int m = (l + r) / 2;
    pair <int, int> x = attack(v * 2, l, m, a, b);
    pair <int, int> y = attack(v * 2 + 1, m + 1, r, a, b);

    if (x.first < y.first)
        return x;
    else
        return y;
}

int main() {
    cin >> n >> m;
    while (sz <= LEN)
        sz *= 2;

    for (int i = sz; i < 4 * LEN; i++)
        tree[i].second = i - sz;
    for (int i = sz - 1; i >= 1; i--)
        update(i);

    string query;
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> query;

        if (query == "defend") {
            cin >> a >> b >> c;

            defend(1, 1, sz, a, b, c);
        }

        if (query == "attack") {
            cin >> a >> b;

            pair <int, int> ans = attack(1, 1, sz, a, b);

            cout << ans.first << " " << ans.second + 1 << "\n";
        }
    }

    return 0;
}
