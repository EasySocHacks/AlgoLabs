#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


struct Node {
    Node *L, *R;
    int x, y;
    int sz = 0;

    Node(int _x) {
        L = nullptr;
        R = nullptr;
        x = _x;
        y = (rand() << 16) | rand();
        sz = 1;
    }
};

int getSize(Node* T) {
    if (T == nullptr)
        return 0;

    return T->sz;
}

void update(Node* T) {
    if (T == nullptr)
        return;

    T->sz = getSize(T->L) + getSize(T->R) + 1;
}

pair<Node*, Node*> split(Node* T, int x) {
    if (T == nullptr)
        return {nullptr, nullptr};

    int sz = getSize(T->L) + 1;

    if (sz > x) {
        pair <Node*, Node*> ret = split(T->L, x);

        T->L = ret.second;
        update(T->L);
        update(T);

        return {ret.first, T};
    } else {
        pair <Node*, Node*> ret = split(T->R, x - sz);

        T->R = ret.first;
        update(T->R);
        update(T);

        return {T, ret.second};
    }
}

Node* merge(Node* T1, Node* T2) {
    if (T1 == nullptr)
        return T2;
    if (T2 == nullptr)
        return T1;

    if (T1->y > T2->y) {
        T1->R = merge(T1->R, T2);
        update(T1->R);
        update(T1);
        return T1;
    } else {
        T2->L = merge(T1, T2->L);
        update(T2->L);
        update(T2);
        return T2;
    }
}

Node* insertNode(Node* T, Node* t, int x) {
    pair <Node*, Node*> ret = split(T, x);
    return merge(ret.first, merge(t, ret.second));
}

Node* deleteNode(Node *T, int x) {
    pair<Node*, Node*> ret1 = split(T, x - 1);
    pair<Node*, Node*> ret2 = split(ret1.second, 1);

    return merge(ret1.first, ret2.second);
}

Node* kth(Node* T, int k) {
    int sz = getSize(T->L) + 1;

    if (sz == k)
        return T;

    if (sz > k) {
        return kth(T->L, k);
    } else {
        return kth(T->R, k - sz);
    }
}

int n, m;
Node *T = nullptr;

signed main() {
    srand(time(0));

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        T = insertNode(T, new Node(i + 1), i + 1);
    }

    int l, r;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;

        pair <Node*, Node*> p1 = split(T, l - 1);
        pair <Node*, Node*> p2 = split(p1.second, r - l + 1);

        T = merge(p2.first, merge(p1.first, p2.second));
    }

    for (int i = 0; i < n; i++)
        cout << kth(T, i + 1)->x << " ";

    return 0;
}
