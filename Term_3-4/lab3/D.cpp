#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 2e6 + 9;
 
string ps, ts;
vector <int> ans;
int p[LEN];
 
int main() {
    cin >> ps >> ts;
 
    string str = ps + "#" + ts;
 
    for (int i = 1; i < str.size(); i++) {
        int tmp = p[i - 1];
 
        while (tmp > 0 && str[i] != str[tmp]) {
            tmp = p[tmp - 1];
        }
 
        if (str[tmp] == str[i]) {
            p[i] = tmp + 1;
        }
    }
 
    for (int i = 1; i < str.size(); i++) {
        if (p[i] == ps.size()) {
            ans.push_back(i + 1);
        }
    }
 
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] - 2 * ps.size() << " ";
    }
 
    return 0;
}