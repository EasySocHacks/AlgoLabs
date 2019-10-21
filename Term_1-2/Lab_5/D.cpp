#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 300000;
const int INF = 1e9;

struct Node {
    Node *L, *R;
    int sz;
    int x, y;
    bool containsZero;

    Node(int _x) {
        L = nullptr;
        R = nullptr;
        sz = 1;
        x = _x;
        y = (rand() << 16) | rand();

        containsZero = (_x == 0);
    }
};

int getSize(Node* T) {
    if (T == nullptr)
        return 0;

    return T->sz;
}

bool containsZero(Node* T) {
    if (T == nullptr)
        return false;

    return T->containsZero;
}

void update(Node* T) {
    if (T == nullptr)
        return;

    T->sz = getSize(T->L) + getSize(T->R) + 1;
    T->containsZero = (containsZero(T->L) || (T->x == 0) || containsZero(T->R));
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
    pair <Node*, Node*> ret = split(T, x - 1);
    return merge(ret.first, merge(t, ret.second));
}

Node* deleteNode(Node *T, int x) {
    pair<Node*, Node*> ret1 = split(T, x - 1);
    pair<Node*, Node*> ret2 = split(ret1.second, x);

    return merge(ret1.first, ret2.second);
}

int firstZero (Node* T, int pos) {
    if (T == nullptr)
        return INF;

    if (containsZero(T->L)) {
        return firstZero(T->L, pos);
    } else if (T->x == 0) {
        return pos + 1 + getSize(T->L);
    } else {
        return firstZero(T->R, pos + getSize(T->L) + 1);
    }
}

Node *T = nullptr;

int n, m;

Node* nth(Node* T, int n) {
    int sz = getSize(T->L) + 1;

    if (sz > n) {
        return nth(T->L, n);
    }

    if (sz == n)
        return T;

    return nth(T->R, n - sz);
}

vector <int> ans;

void getAns() {
    int cnt = 0;

    for (int i = 1; cnt != n; i++) {
        Node* x = nth(T, i);

        ans.push_back(x->x);

        if (x->x != 0)
            cnt++;
    }
}

int main() {
    srand(time(0));

    cin >> n >> m;

    for (int i = 0; i < LEN; i++) {
        T = insertNode(T, new Node(0), i + 1);
    }

    int l;
    for (int i = 1; i <= n; i++) {
        cin >> l;

        pair <Node*, Node*> p1 = split(T, l - 1);
        int posZero = firstZero(p1.second, 0);
        pair <Node*, Node*> p2 = split(p1.second, posZero - 1);
        pair <Node*, Node*> p3 = split(p2.second, 1);

        T = merge(p1.first, merge(new Node(i), merge(p2.first, p3.second)));
    }
    getAns();

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
