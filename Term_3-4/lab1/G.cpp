#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 2 * 1009;
 
bool used[LEN];
 
int n, m;
map <string, int> name_num;
map <int, string> num_name;
int color[LEN];
 
vector <int> topsort;
vector <int> g[LEN];
vector <int> rg[LEN];
set <int> newG[LEN];
bool newAns[LEN];
bool ans[LEN];
bool marked[LEN];
 
void dfs(int v) {
    used[v] = true;
 
    for (int u : g[v]) {
        if (used[u])
            continue;
 
        dfs(u);
    }
 
    topsort.push_back(v);
}
 
void dfs2(int v, int c) {
    color[v] = c;
 
    for (int u : rg[v]) {
        if (color[u] != 0) {
            if (color[u] != c) {
                newG[color[u]].insert(c);
            }
 
            continue;
        }
 
        dfs2(u, c);
    }
}
 
void dfs3(int v) {
    used[v] = true;
 
    for (int u : newG[v]) {
        if (used[u])
            continue;
 
        dfs3(u);
    }
 
    topsort.push_back(v);
}
 
void makeAns(int c, bool b) {
    for (int i = 0; i < n / 2; i++) {
        if (color[i] != c)
            continue;
 
 
    }
}
 
int main() {
    cin >> n >> m;
    string name;
 
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> name;
 
        name_num["+" + name] = cnt;
        name_num["-" + name] = cnt + 1;
 
        num_name[cnt] = name;
        num_name[cnt + 1] = name;
 
        cnt += 2;
    }
 
    string str;
    string name1, name2;
 
    for (int i = 0; i < m; i++) {
        cin >> name1 >> str >> name2;
 
        g[name_num[name1]].push_back(name_num[name2]);
        rg[name_num[name2]].push_back(name_num[name1]);
 
        if (name1[0] == '+')
            name1[0] = '-';
        else
            name1[0] = '+';
 
        if (name2[0] == '+')
            name2[0] = '-';
        else
            name2[0] = '+';
 
            swap(name1, name2);
 
        g[name_num[name1]].push_back(name_num[name2]);
        rg[name_num[name2]].push_back(name_num[name1]);
    }
 
    n *= 2;
 
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
 
        dfs(i);
    }
 
    reverse(topsort.begin(), topsort.end());
 
    fill(used, used + LEN, false);
 
    int c = 1;
    for (int i = 0; i < n; i++) {
        if (color[topsort[i]] != 0)
            continue;
 
        dfs2(topsort[i], c);
        c++;
    }
 
    topsort.clear();
 
    for (int i = 1; i < c; i++) {
        if (used[i])
            continue;
 
        dfs3(i);
    }
 
    //reverse(topsort.begin(), topsort.end());
 
    for (int i = 0; i < n; i += 2) {
        if (color[i] == color[i + 1]) {
            cout << -1;
            exit(0);
        }
    }
 
    for (int k = 1; k < c; k++) {
        int i = topsort[k - 1];
 
        if (marked[i]) {
            continue;
        }
 
        marked[i] = true;
 
        for (int j = 0; j < n; j++) {
            if (color[j] != i) {
                continue;
            }
 
 
 
            if (j % 2 == 0) {
                marked[color[j + 1]] = true;
 
                ans[j] = true;
                ans[j + 1] = false;
            } else {
                marked[color[j - 1]] = true;
 
                ans[j] = true;
                ans[j - 1] = false;
            }
        }
    }
 
    vector <string> anss;
 
    for (int i = 0; i < n; i += 2) {
        if (ans[i]) {
            anss.push_back(num_name[i]);
        }
    }
 
    cout << anss.size() << "\n";
    for (int i = 0; i < anss.size(); i++) {
        cout << anss[i] << "\n";
    }
 
    return 0;
}
