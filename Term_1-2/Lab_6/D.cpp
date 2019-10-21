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

    node() {
        P = nullptr;
        L = nullptr;
        R = nullptr;
        sz = 1;
        y = ((rand() << 16) | rand());
        val = 0;
    }

    node(int _val) {
        P = nullptr;
        L = nullptr;
        R = nullptr;
        sz = 1;
        y = ((rand() << 16) | rand());
        val = _val;
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
}

pair<node*, node*> split(node *T, int x) {
    if (T == nullptr)
    return {nullptr, nullptr};

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

int nodeCouner = 1;
node* nodeLink[LEN];
int parent[LEN];
set <int> childrens[LEN];

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

int n;

int main() {
    nodeLink[0] = new node(0);
    parent[0] = -1;

    cin >> n;
    string query;
    int v, u;
    node *T;

    for (int i = 0; i < n; i++) {
        cin >> query;

        if (query == "+") {
            cin >> v;
            v--;

            T = new node(nodeCouner);
            nodeLink[nodeCouner] = T;

            parent[nodeCouner] = v;
            childrens[v].insert(nodeCouner);

            nodeCouner++;

        }

        if (query == "-") {
            cin >> v;
            v--;

            T = nodeLink[v];
            auto p1 = split(getParent(T), getPos(T));
            split(p1.second, 1);

            int p = parent[v];
            for (int u : childrens[v]) {
                parent[u] = p;
                childrens[p].insert(u);
            }
            childrens[v].clear();

            childrens[p].erase(v);
            nodeLink[v] = nullptr;
            parent[v] = -1;
        }

        if (query == "?") {
            cin >> v >> u;
            v--;
            u--;

            expose(u);
            expose(v);

            if (getParent(nodeLink[v]) == getParent(nodeLink[u])) {
                if (getPos(nodeLink[v]) < getPos(nodeLink[u])) {
                    cout << (v + 1) << "\n";
                } else {
                    cout << (u + 1) << "\n";
                }
            } else {
                cout << (parent[mostLeft(getParent(nodeLink[u]))->val] + 1) << "\n";
            }
        }
    }


    return 0;
}