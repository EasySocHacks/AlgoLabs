#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *L, *R;
    int sz;
    int x, y;

    Node(int _x) {
        L = nullptr;
        R = nullptr;
        sz = 1;
        x = _x;
        y = (rand() << 16) | rand();
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

    if (T->x > x) {
        pair <Node*, Node*> ret = split(T->L, x);

        T->L = ret.second;
        update(T);

        return {ret.first, T};
    } else {
        pair <Node*, Node*> ret = split(T->R, x);

        T->R = ret.first;
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
        update(T1);
        return T1;
    } else {
        T2->L = merge(T1, T2->L);
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

string firstNode(Node *T) {
    if (T == nullptr)
        return "none";

    if (T->L != nullptr)
        return firstNode(T->L);

    stringstream ss;
    ss << T->x;
    string ans;
    ss >> ans;
    return ans;
}

string lastNode(Node *T) {
    if (T == nullptr)
        return "none";

    if (T->R != nullptr)
        return lastNode(T->R);

    stringstream ss;
    ss << T->x;
    string ans;
    ss >> ans;
    return ans;
}

Node *T = nullptr;

int main() {
    srand(time(0));

    string query;
    int x;
    while (cin >> query) {
        cin >> x;

        if (query == "insert") {
            if (!exists(T, x)) {
                T = insertNode(T, new Node(x), x);
            }
        }

        if (query == "delete") {
            if (exists(T, x)) {
                T = deleteNode(T, x);
            }
        }

        if (query == "exists") {
            cout << (exists(T, x) ? "true" : "false") << "\n";
        }

        if (query == "next") {
            pair<Node*, Node*> ret = split(T, x);
            cout << firstNode(ret.second) << "\n";

            T = merge(ret.first, ret.second);
        }

        if (query == "prev") {
            pair<Node*, Node*> ret = split(T, x - 1);
            cout << lastNode(ret.first) << "\n";

            T = merge(ret.first, ret.second);
        }
    }

    return 0;
}
