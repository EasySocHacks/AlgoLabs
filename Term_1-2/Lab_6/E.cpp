#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;
#define pb push_back

const int LEN = 2e5 + 9;

struct node {
    node *L, *R, *P;
    int sz;
    int y;
    int val;
    bool isUsed;
    int mem;

    node() {
        P = nullptr;
        L = nullptr;
        R = nullptr;
        sz = 1;
        y = ((rand() << 16) | rand());
        val = 0;
        isUsed = false;
        mem = -1;
    }

    node(int _val) {
        P = nullptr;
        L = nullptr;
        R = nullptr;
        sz = 1;
        y = ((rand() << 16) | rand());
        val = _val;
        isUsed = false;
        mem = -1;
    }
};

int getSize(node *T) {
    if (T == nullptr)
        return 0;

    return T->sz;
}

void update(node *T) {
    if (T == nullptr)
        return;

    T->sz = getSize(T->L) + getSize(T->R) + 1;

    if (T->mem != -1) {
        T->mem = -1;
        T->isUsed = true;

        if (T->L != nullptr) {
            T->L->mem = 1;
        }

        if (T->R != nullptr) {
            T->R-> mem = 1;
        }
    }
}

pair<node*, node*> split(node *T, int x) {
    if (T == nullptr)
    return {nullptr, nullptr};

    update(T);

    int pos = getSize(T->L) + 1;

    if (x < pos) {
        if (T->L != nullptr)
            T->L->P = nullptr;
        pair<node*, node*> p = split(T->L, x);
        T->L = p.second;

        if (p.second != nullptr)
            p.second->P = T;

        update(T->L);
        update(T);

        return {p.first, T};
    } else {
        if (T->R != nullptr)
            T->R->P = nullptr;
        pair<node*, node*> p = split(T->R, x - pos);
        T->R = p.first;

        if (p.first != nullptr)
            p.first->P = T;

        update(T->R);
        update(T);

        return {T, p.second};
    }
}

node* merge(node *T1, node *T2) {
    if (T1 == nullptr)
        return T2;
    if (T2 == nullptr)
        return T1;

    update(T1);
    update(T2);

    if (T1->y > T2->y) {
        if (T1->R != nullptr)
            T1->R->P = nullptr;

        T1->R = merge(T1->R, T2);

        if (T1->R != nullptr)
            T1->R->P = T1;

        update(T1->R);
        update(T1);

        return T1;
    } else {
        if (T2->L != nullptr)
            T2->L->P = nullptr;

        T2->L = merge(T1, T2->L);

        if (T2->L != nullptr)
            T2->L->P = T2;

        update(T2->L);
        update(T2);

        return T2;
    }
}



int getPos(node *X) {
    int ans = getSize(X->L) + 1;

    while (X->P != nullptr) {
        if (X->P->L == X) {
            X = X->P;
        } else {
            ans += getSize(X->P->L) + 1;
            X = X->P;
        }
    }

    return ans;
}

node* getParent(node *T) {
    if (T == nullptr)
        return nullptr;

    while (T->P != nullptr)
        T = T->P;

    return T;
}

node* mostLeft(node *T) {
    if (T == nullptr)
        return nullptr;

    T = getParent(T);

    while (T->L != nullptr)
        T = T->L;

    return T;
}

node* nodeLink[LEN];
int parent[LEN];
vector <int> g[LEN];

void expose(int v) {
    node *X = nullptr;
    node *Y = nullptr;

    while (v != 0) {
        X = nodeLink[v];
        X = mostLeft(X);

        if (X->val == 0)
            break;

        Y = nodeLink[parent[X->val]];

        split(getParent(Y), getPos(Y));
        merge(getParent(Y), getParent(X));

        v = mostLeft(Y)->val;
    }
}

void dfs(int v, int par) {
    if (par != -1) {
        parent[v] = par;
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (u == par)
            continue;

        dfs(u, v);
    }
}

int ans;
bool updated[LEN];

void updateTree(node *T) {
    if (T == nullptr)
        return;

    update(T);
    updated[T->val] = true;

    updateTree(T->L);
    updateTree(T->R);
}

void getAns(int v, int par) {
    if (!updated[v]) {
        node *T = nodeLink[v];
        updateTree(getParent(T));
    }

    if (par != -1) {
        node *T = nodeLink[v];

        if (T->isUsed)
            ans--;
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (u == par)
            continue;

        getAns(u, v);
    }
}

int n, m;

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        node *T = new node(i);
        nodeLink[i] = T;
    }

    int v, u;

    for (int i = 0; i < n - 1; i++) {
        cin >> v >> u;
        v--;
        u--;

        g[v].pb(u);
        g[u].pb(v);
    }

    dfs(0, -1);

    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;

        expose(v);
        expose(u);

        int lca;

        if (getParent(nodeLink[v]) == getParent(nodeLink[u])) {
            if (getPos(nodeLink[v]) < getPos(nodeLink[u])) {
                lca = v;

                node *T = getParent(nodeLink[lca]);
                pair <node*, node*> p1 = split(T, getPos(nodeLink[u]));
                pair <node*, node*> p2 = split(p1.first, getPos(nodeLink[v]));

                if (p2.second != nullptr) {
                    p2.second->mem = 1;
                    update(p2.second);
                }

                merge(p2.first, p2.second);
                merge(p1.first, p1.second);
            } else {
                lca = u;

                node *T = getParent(nodeLink[lca]);
                pair <node*, node*> p1 = split(T, getPos(nodeLink[v]));
                pair <node*, node*> p2 = split(p1.first, getPos(nodeLink[u]));

                if (p2.second != nullptr) {
                    p2.second->mem = 1;
                    update(p2.second);
                }

                merge(p2.first, p2.second);
                merge(p1.first, p1.second);
            }
        } else {
            lca = parent[mostLeft(getParent(nodeLink[v]))->val];

            node *T = getParent(nodeLink[v]);

            pair <node*, node*> p = split(T, getPos(nodeLink[v]));

            p.first->mem = 1;
            update(p.first);

            merge(p.first, p.second);

            T = getParent(nodeLink[u]);

            pair <node*, node*> p1 = split(T, getPos(nodeLink[u]));
            pair <node*, node*> p2 = split(p1.first, getPos(nodeLink[lca]));

            p2.second->mem = 1;
            update(p2.second);

            merge(p2.first, p2.second);
            merge(p1.first, p1.second);
        }
    }

    ans = n - 1;

    getAns(0, -1);

    cout << ans;

    return 0;
}