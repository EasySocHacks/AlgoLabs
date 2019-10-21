#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 200009;
 
struct Node {
    Node *par;
 
    Node() {}
};
 
struct edge {
    int v, u, w;
 
    edge(int v, int u, int w) : v(v), u(u), w(w) {}
};
 
int n, m;
 
Node* snm[LEN];
 
vector <edge> edges;
 
bool comp (edge a, edge b) {
    return a.w < b.w;
}
 
Node* getRoot(Node*T) {
    if (T == T->par)
        return T;
 
    Node *R = getRoot(T->par);
    T->par = R;
    return R;
}
 
Node* join(Node *T1, Node* T2) {
    T1->par = T2;
    return T2;
}
 
int main() {
    cin >> n >> m;
 
    for (int i = 0; i < n; i++) {
        snm[i] = new Node();
        snm[i]->par = snm[i];
    }
 
    int v, u, w;
 
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;
        v--;
        u--;
 
        edges.push_back(edge(v, u, w));
    }
 
    sort(edges.begin(), edges.end(), comp);
 
    long long ans = 0;
 
    for (int i = 0; i < m; i++) {
        v = edges[i].v;
        u = edges[i].u;
 
        if (getRoot(snm[v]) == getRoot(snm[u]))
            continue;
 
        ans += (long long) edges[i].w;
 
        join(getRoot(snm[v]), getRoot(snm[u]));
    }
 
    cout << ans;
 
    return 0;
}
