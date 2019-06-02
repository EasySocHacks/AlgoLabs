#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;
#define pb push_back

const int LEN = 1e5 + 9;

struct node {
    node *L, *R, *P, *PP = nullptr;
    int sz;
    int y;
    int val;
    int reversed = 0;

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

    if (T->reversed == 1) {
        swap(T->L, T->R);
        T->reversed = 0;

        if (T->L != nullptr)
            T->L->reversed ^= 1;
        if (T->R != nullptr)
            T->R->reversed ^= 1;
    }
}

void upd(node *T) {
    if (T == nullptr)
        return;

    upd(T->P);
    update(T);
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
    upd(X);

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
    update(T);

    while (T->L != nullptr) {
        T = T->L;
        update(T);
    }

    return T;
}

node* nodeLink[LEN];

void expose(node *X) {
    if (X == nullptr)
        return;

    X = mostLeft(X);

    while (X->PP != nullptr) {
        node *Y = X->PP;
        X->PP = nullptr;

        pair <node*, node*> p = split(getParent(Y), getPos(Y));
        if (p.second != nullptr)
            mostLeft(p.second)->PP = Y;

        Y = p.first;
        merge(getParent(Y), getParent(X));

        X = mostLeft(Y);
    }
}

int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        nodeLink[i] = new node(i);
    }

    int v, u;
    string query;
    for (int i = 0; i < m; i++) {
        cin >> query >> v >> u;

        v--;
        u--;

        if (query == "link") {
            node *X = nodeLink[v];
            node *Y = nodeLink[u];

            expose(X);

            pair <node*, node*> p = split(getParent(X), getPos(X));
            if (p.second != nullptr)
                mostLeft(p.second)->PP = X;

            X = p.first;

            X->reversed ^= 1;
            update(X);

            mostLeft(X)->PP = Y;
        }

        if (query == "cut") {
            node *X = nodeLink[v];
            node *Y = nodeLink[u];

            expose(X);
            expose(Y);

            pair <node*, node*> p1 = split(getParent(X), getPos(X));
            pair <node*, node*> p2 = split(p1.second, 1);

            if (p2.first == Y) {
                merge(p2.first, p2.second);
            } else {
                merge(p2.first, p2.second);
                merge(p1.first, p1.second);

                split(getParent(Y), getPos(Y));
            }
        }

        if (query == "connected") {
            node *X = nodeLink[v];
            node *Y = nodeLink[u];


            expose(X);
            node *P1 = mostLeft(X);

            expose(Y);
            node *P2 = mostLeft(Y);



            cout << (P1 == P2 ? 1 : 0) << "\n";
        }
    }

    return 0;
}