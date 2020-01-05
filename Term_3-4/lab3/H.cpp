#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
 
const int LEN = 1e6 + 9;
const unordered_map <int, int> TMP;
 
int n;
string str[LEN];
string t;
 
vector <unordered_map<int, int>> bor;
pair<int, char> par[LEN];
int link[LEN];
vector <int> rlink[LEN];
vector <int> mark[LEN];
int ok[LEN];
int ANS[LEN];
 
void addInBor(string str, int m) {
    int v = 0;
 
    for (int i = 0; i < str.size(); i++) {
        if (bor[v].count(str[i] - 'a') == 0) {
            bor.push_back(TMP);
            bor[v][str[i] - 'a'] = bor.size() - 1;
 
            par[bor.size() - 1] = {v, str[i]};
 
            v = bor.size() - 1;
        } else {
            v = bor[v][str[i] - 'a'];
        }
    }
 
    mark[v].push_back(m);
}
 
void dfs(int v) {
 
    for (int u : rlink[v]) {
        dfs(u);
    }
 
    for (int u : rlink[v]) {
        ok[v] += ok[u];
    }
}
 
void dfs3(int v) {
    if (ok[v] > 0) {
        for (auto x : mark[v]) {
            ANS[x] = ok[v];
        }
    }
 
    for (auto x : bor[v]) {
        dfs3(x.second);
    }
}
 
int main() {
    freopen("search5.in", "r", stdin);
    freopen("search5.out", "w", stdout);
 
    cin >> n;
 
    par[0] = {0, '#'};
    bor.push_back(TMP);
    link[0] = 0;
 
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        addInBor(str[i], i);
    }
 
    queue <int> q;
    q.push(0);
 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
 
        for (auto u : bor[v]) {
            q.push(u.second);
        }
 
        if (par[v].first == 0) {
            link[v] = 0;
            continue;
        }
 
        int u = link[par[v].first];
        while (u != 0 && bor[u].count(par[v].second - 'a') == 0)
            u = link[u];
 
        if (bor[u].count(par[v].second - 'a') == 0) {
            link[v] = 0;
        } else {
            link[v] = bor[u][par[v].second - 'a'];
        }
    }
 
    cin >> t;
 
    for (int i = 1; i < bor.size(); i++) {
        rlink[link[i]].push_back(i);
    }
 
    int v = 0;
    for (int i = 0; i < t.size(); i++) {
        while (v != 0 && bor[v].count(t[i] - 'a') == 0)
            v = link[v];
 
        if (bor[v].count(t[i] - 'a') == 0) {
            v = 0;
        } else {
            v = bor[v][t[i] - 'a'];
 
            ok[v]++;
        }
    }
 
    dfs(0);
 
    dfs3(0);
 
    for (int i = 0; i < n; i++) {
        cout << ANS[i] << "\n";
    }
 
    return 0;
}