#include <bits/stdc++.h>
using namespace std;

const int LEN = 2e6 + 9;
const int ADD = 5e5 + 9;

struct Node {
    int black_cnt;
    int black_len;
    int right_color;
    int left_color;

    Node() {
        black_cnt = 0;
        black_len = 0;
        right_color = 0;
        left_color = 0;
    }
};

int sz = 1;
int n;
Node tree[4 * LEN];
int mem[4 * LEN];
/*
    0 - NOTHING
    2 - PAINT WHITE
    1 - PAINT BLACK
*/

void push(int v, int s) {
    if (mem[v] == 1) {
        tree[v].black_cnt = 1;
        tree[v].black_len = s;
        tree[v].right_color = 1;
        tree[v].left_color = 1;

        if (v < sz) {
            mem[v * 2] = mem[v];
            mem[v * 2 + 1] = mem[v];
        }
    }

    if (mem[v] == 2) {
        tree[v].black_cnt = 0;
        tree[v].black_len = 0;
        tree[v].right_color = 0;
        tree[v].left_color = 0;

        if (v < sz) {
            mem[v * 2] = mem[v];
            mem[v * 2 + 1] = mem[v];
        }
    }

    mem[v] = 0;
}

void solve(int v) {

    tree[v].black_cnt = tree[v * 2].black_cnt + tree[v * 2 + 1].black_cnt;
    tree[v].black_len = tree[v * 2].black_len + tree[v * 2 + 1].black_len;

    tree[v].right_color = tree[v * 2 + 1].right_color;
    tree[v].left_color = tree[v * 2].left_color;

    if (tree[v * 2].right_color == 1 && tree[v * 2 + 1].left_color == 1) {
        tree[v].black_cnt--;
    }
}

void paint(int v, int l, int r, int a, int b, int c) {
    push(v, r - l + 1);

    if (r < a || l > b)
        return;

    if (a <= l && r <= b)  {
        mem[v] = c;
        push(v, r - l + 1);
        return;
    }

    int m = (l + r) / 2;
    paint(v * 2, l, m, a, b, c);
    paint(v * 2 + 1, m + 1, r, a, b, c);

    solve(v);
}

int main() {
    while (sz <= LEN)
        sz *= 2;

    cin >> n;

    string color;
    int l, r, c;
    for (int i = 0; i < n; i++) {
        cin >> color >> l >> r;
        c = (color == "W" ? 2 : 1);

        l += ADD;
        r = l + r - 1;
        paint(1, 1, sz, l, r, c);

        cout << tree[1].black_cnt << " " << tree[1].black_len << "\n";
    }

    return 0;
}
