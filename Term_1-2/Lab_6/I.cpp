#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef long long ll;
#define pb push_back

const int LEN = 1e5 + 9;

struct node {
    node *L, *R, *P;
    int sz;
    int y;

    node() {
        P = nullptr;
        L = nullptr;
        R = nullptr;
        sz = 1;
        y = ((rand() << 16) | rand());
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

    if (x <= pos) {
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

int n, m;
map <int, node*> edgeLink[LEN];

int main() {
    cin >> n >> m;
    string query;
    int v, u;

    for (int i = 0; i < m; i++) {
        cin >> query;

        if (query == "link") {
            cin >> v >> u;
            v--;
            u--;

            node *edge = new node();
            node *r_edge = new node();

            node *A = nullptr, *B = nullptr, *C = nullptr, *D = nullptr;

            if (edgeLink[v].size() == 0) {
                A = nullptr;
                D = nullptr;
            } else {
                node* splitEdge = edgeLink[v].begin()->second;
                pair <node*, node*> p = split(getParent(splitEdge), getPos(splitEdge));

                A = p.first;
                D = p.second;
            }

            if (edgeLink[u].size() == 0) {
                C = nullptr;
                B = nullptr;
            } else {
                node *splitEdge = edgeLink[u].begin()->second;
                pair <node*, node*> p = split(getParent(splitEdge), getPos(splitEdge));

                C = p.first;
                B = p.second;
            }

            node *M1 = merge(A, edge);
            node *M2 = merge(M1, B);
            node *M3 = merge(M2, C);
            node *M4 = merge(M3, r_edge);
            node *M5 = merge(M4, D);

            edgeLink[v][u] = edge;
            edgeLink[u][v] = r_edge;
        }

        if (query == "cut") {
            cin >> v >> u;
            v--;
            u--;

            node *edge = edgeLink[v][u];
            node *r_edge = edgeLink[u][v];




            if (getPos(edge) > getPos(r_edge))
                swap(edge, r_edge);

            edgeLink[v].erase(u);
            edgeLink[u].erase(v);

            pair <node*, node*> p1 = split(getParent(edge), getPos(edge));
            pair <node*, node*> p2 = split(p1.second, 2);
            pair <node*, node*> p3 = split(p2.second, getPos(r_edge));
            pair <node*, node*> p4 = split(p3.second, 2);

            merge(p1.first, p4.second);
        }

        if (query == "size") {
            cin >> v;
            v--;

            if (edgeLink[v].size() == 0) {
                cout << "1\n";
            } else {
                node *edge = (*edgeLink[v].begin()).second;

                int x = getParent(edge)->sz;
                cout << (x / 2 + 1) << "\n";
            }
        }
    }

    return 0;
}