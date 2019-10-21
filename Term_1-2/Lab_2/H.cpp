#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

const int LEN = 200009;

struct node {
    node *par = nullptr;
    int r = 1;
    int hangTime = -1;
    vector <pair<int, int> > adds;
    vector <int> prefSumm;
    node() {
        adds.resize(0);
        prefSumm.resize(0);
    }

    int binSearch(int t) {
        int l = -1, r = adds.size(), m;

        while (r - l > 1) {
            m = (l + r) / 2;

            if (adds[m].first < t)
                l = m;
            else
                r = m;
        }

        if (r == adds.size())
            return 0;

        return prefSumm.back() - prefSumm[r] + adds[r].second;
    }
};

pair<node*, int> getNode(node *v) {
    if (v->par == v) {
        return {v, 0};
    }

    node *u = v->par;
    int ret = u->binSearch(v->hangTime);

    pair<node*, int> p = getNode(u);

    return {p.first, p.second + ret};

}

void join(node *v, node *u, int t) {
    if (v == u)
        return;

    if (v->r >= u->r) {
        u->par = v;

        if (v->r == u->r)
            v->r++;

        u->hangTime = t;
    } else {
        v->par = u;

        v->hangTime = t;
    }
}

int n, m;
node *vertex[LEN];

int main() {
    cin >> n >> m;

    for (int i = 0; i < LEN; i++) {
        vertex[i] = new node();
        vertex[i]->par = vertex[i];
    }

    string type;
    int x, y;

    for (int i = 0; i < m; i++) {
        cin >> type;

        if (type == "join") {
            cin >> x >> y;

            join(getNode(vertex[x]).first, getNode(vertex[y]).first, i);
        }

        if (type == "add") {
            cin >> x >> y;

            node *v = getNode(vertex[x]).first;

            v->adds.pb({i, y});
            v->prefSumm.pb(y + (v->prefSumm.empty() ? 0 : v->prefSumm.back()));
        }

        if (type == "get") {
            cin >> x;

            cout << getNode(vertex[x]).second + vertex[x]->binSearch(-1) << "\n";
        }
    }

    return 0;
}
