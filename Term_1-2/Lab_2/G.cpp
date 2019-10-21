#include <iostream>
using namespace std;

const int LEN = 300001;

struct node {
    int x = 0, minX = 0, maxX = 0;
    int cnt = 1;
    node *par = nullptr;
    int r = 1;

    node() {}

    node(int x) {
        this->x = x;
        minX = x;
        maxX = x;
    }
};

void update(node *v) {
    if (v == nullptr) return;
    if (v->par == nullptr) return;

    node *u = v->par;

    u->minX = min(u->minX, v->minX);
    u->maxX = max(u->maxX, v->maxX);
    u->cnt += v->cnt;
}

node *getNode(node *v) {
    if (v->par != v) {
        v->par = getNode(v->par);
    }

    return v->par;
}

void join(node *v, node *u) {
    if (v == u)
        return;

    if (v->r >= u->r) {
        u->par = v;

        if (v->r == u->r)
            v->r++;

        update(u);
    } else {
        v->par = u;

        update(v);
    }
}

int n;
node *vertex[LEN];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        vertex[i] = new node(i + 1);
        vertex[i]->par = vertex[i];
    }

    string type;
    int x, y;

    while (cin >> type) {
        if (type == "union") {
            cin >> x >> y;

            x--;
            y--;

            join(getNode(vertex[x]), getNode(vertex[y]));
        }

        if (type == "get") {
            cin >> x;

            x--;

            node *v = getNode(vertex[x]);

            cout << v->minX << " " << v->maxX << " " << v->cnt << "\n";
        }
    }

    return 0;
}
