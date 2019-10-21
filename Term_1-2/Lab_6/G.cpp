#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;
#define pb push_back

const int LEN = 3e5 + 9;

int n, m;
vector <int> g[LEN];
int heavy[LEN];
int sz[LEN];
int h[LEN];
int up[LEN][25];
int deep[LEN];

struct node;

struct ST {
    vector <ll> arr;
    vector <ll> mem;
    int sz = 0;
    int pos = 0;
    node *start;

    ST() {}

    ST(int len, node *s) {
        start = s;
        arr.resize(4 * len);
        mem.resize(4 * len);

        sz = 1;
        while (sz <= len)
            sz *= 2;
    }

    inline int addNode() {
        pos++;

        return pos - 1;
    }

    void push(int v) {
        arr[v] += mem[v];

        if (v < sz) {
            mem[v * 2] += mem[v];
            mem[v * 2 + 1] += mem[v];
        }

        mem[v] = 0;
    }

    void add(int v, int l, int r, int a, int b, ll x) {
        push(v);

        if (r < a || l > b)
            return;

        if (a <= l && r <= b) {
            mem[v] += x;
            push(v);
            return;
        }

        int m = (l + r) / 2;
        add(v * 2, l, m, a, b, x);
        add(v * 2 + 1, m + 1, r, a, b, x);
    }

    ll get(int v, int l, int r, int x) {
        push(v);

        if (r < x || l > x)
            return 0;

        if (l == x && r == x)
            return arr[v];

        int m = (l + r) / 2;
        return get(v * 2, l, m, x) + get(v * 2 + 1, m + 1, r, x);
    }
};

struct node {
    ST *T = nullptr;
    int pos;
    int number;

    node() {}
    node(int p, int num) {
        pos = p;
        number = num;
    }
};

node* nodeLink[LEN];

int calc(int v, int prev, int height) {


    h[v] = height;

    if (prev == -1)
        up[v][0] = v;
    else
        up[v][0] = prev;

    for (int i = 1; i < 25; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];

    deep[v] = 1;

    int treeSz = 1;
    for (int u : g[v]) {
        if (u == prev)
            continue;

        treeSz += calc(u, v, height + 1);

        deep[v] = max(deep[v], deep[u] + 1);
    }

    for (int u : g[v]) {
        if (u == prev)
            continue;

        if (sz[u] * 2 >= treeSz - 1) {
            heavy[v] = u;

            break;
        }
    }

    sz[v] = treeSz;
    return treeSz;
}

void dfs(int v, int prev, ST *T) {

    bool flag = false;
    if (T == nullptr) {
        T = new ST(deep[v], nullptr);

        flag = true;
    }

    nodeLink[v] = new node(T->addNode(), v);
    nodeLink[v]->T = T;

    if (flag)
        T->start = nodeLink[v];

    for (int u : g[v]) {
        if (u == prev)
            continue;

        if (u == heavy[v]) {
            dfs(u, v, T);
        } else {
            dfs(u, v, nullptr);
        }
    }
}

int lca(int v, int u) {
    if (h[v] < h[u])
        swap(v, u);

    int k = 24;
    while (h[v] > h[u]) {
        int x = up[v][k];

        if (h[x] < h[u]) {
            k--;
            continue;
        }

        v = x;
        k--;
    }

    if (v == u)
        return v;

    k = 24;
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

void add(node *v, node *u, ll x) {
    while (true) {
        if (v->T == u->T) {
            v->T->add(1, 1, v->T->sz, u->pos + 1, v->pos + 1, x);

            break;
        } else {
            v->T->add(1, 1, v->T->sz, 1, v->pos + 1, x);

            v = nodeLink[up[v->T->start->number][0]];
        }
    }
}

inline ll get(node *v) {
    return v->T->get(1, 1, v->T->sz, v->pos + 1);
}

int main() {
    fill(heavy, heavy + LEN, -1);

    scanf("%d", &n);
    int v, u;

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &v, &u);
        v--;
        u--;

        g[v].pb(u);
        g[u].pb(v);
    }

    calc(0, -1, 1);
    dfs(0, -1, nullptr);

    string query;
    scanf("%d", &m);

    ll x;

    for (int i = 0; i < m; i++) {
        cin >> query;

        if (query == "+") {
            scanf("%d%d%lld", &v, &u, &x);
            v--;
            u--;

            int l = lca(v, u);
            add(nodeLink[v], nodeLink[l], x);
            add(nodeLink[u], nodeLink[l], x);
            add(nodeLink[l], nodeLink[l], -x);
        }

        if (query == "?") {
            scanf("%d", &v);
            v--;

            printf("%lld\n", get(nodeLink[v]));
        }
    }

    return 0;
}