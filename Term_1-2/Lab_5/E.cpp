#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef long long ll;

const int MOD = 1000000000;

struct Node {
    Node *L, *R;
    int sz;
    int x, y;
    ll sum = 0;

    Node(int _x) {
        L = nullptr;
        R = nullptr;
        sz = 1;
        x = _x;
        y = (rand() << 16) | rand();
        sum = 0;
    }
};

int getSize(Node* T) {
    if (T == nullptr)
        return 0;

    return T->sz;
}

ll getSum(Node* T) {
    if (T == nullptr)
        return 0;

    return T->sum;
}

void update(Node* T) {
    if (T == nullptr)
        return;

    T->sz = getSize(T->L) + getSize(T->R) + 1;
    T->sum = getSum(T->L) + getSum(T->R) + T->x;
}

pair<Node*, Node*> split(Node* T, int x) {
    if (T == nullptr)
        return {nullptr, nullptr};

    if (T->x > x) {
        pair <Node*, Node*> ret = split(T->L, x);

        T->L = ret.second;
        update(T);
        update(ret.first);

        return {ret.first, T};
    } else {
        pair <Node*, Node*> ret = split(T->R, x);

        T->R = ret.first;
        update(T);
        update(ret.second);

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
    pair<Node*, Node*> ret2 = split(ret1.second, x);

    return merge(ret1.first, ret2.second);
}

bool exists(Node* T, int x) {
    if (T == nullptr)
        return false;

    if (T->x == x) {
        return true;
    }

    if (x < T->x) {
        return exists(T->L, x);
    } else {
        return exists(T->R, x);
    }
}

Node *T = nullptr;

signed main() {
    int n;
    cin >> n;
    srand(time(0));

    string query;
    int x, y;
    ll add = 0;
    bool isLastQ = false;
    for (int i = 0; i < n; i++) {
        cin >> query;
        if (query == "+") {
            cin >> x;

            int pos = x;
            if (true) pos = (pos + add) % MOD;

            if (!exists(T, pos)) {
                T = insertNode(T, new Node(pos), pos);
            }
            add = 0;
            isLastQ = false;
        }

        if (query == "?") {
            cin >> x >> y;

            pair<Node*, Node*> p1 = split(T, x - 1);
            pair<Node*, Node*> p2 = split(p1.second, y);

            if (p2.first == nullptr) {
                add = 0;
            } else
                add = p2.first->sum;

            isLastQ = true;

            T = merge(p1.first, merge(p2.first, p2.second));

            cout << add << "\n";
        }
    }

    return 0;
}
