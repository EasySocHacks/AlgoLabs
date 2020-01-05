#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll P = 31;
const int K = 19;
const int LEN = 1e4 + 9;
const int ST = 1e4 + 5;
 
struct h {
    ll h1, h2;
 
    h(ll h1, ll h2) : h1(h1), h2(h2) {}
};
 
h operator + (h a, h b) {
    return h((((a.h1 + MOD1) % MOD1) + ((b.h1 + MOD1) % MOD1)) % MOD1, (((a.h2 + MOD2) % MOD2) + ((b.h2 + MOD2) % MOD2)) % MOD2);
}
 
h operator - (h a) {
    return h((-a.h1 + MOD1) % MOD1, (-a.h2 + MOD2) % MOD2);
}
 
h operator - (h a, h b) {
    return a + (-b);
}
 
h operator * (h a, h b) {
    return h(((a.h1 % MOD1) * (b.h1 % MOD1)) % MOD1, ((a.h2 % MOD2) * (b.h2 % MOD2)) % MOD2);
}
 
h operator * (h a, ll b) {
    return h(((a.h1 % MOD1) * (b % MOD1)) % MOD1, ((a.h2 % MOD2) * (b % MOD2)) % MOD2);
}
 
bool operator == (h a, h b) {
    return (a.h1 == b.h1 && a.h2 == b.h2);
}
 
bool operator < (h a, h b) {
    if (a.h1 == b.h1) {
        return a.h2 < b.h2;
    }
 
    return a.h1 < b.h1;
}
 
int n;
 
string s[K];
vector <h> ps;
vector <h> vec[K];
 
int main() {
    cin >> n;
 
    if (n == 1) {
        string str;
        cin >> str;
        cout << str;
        return 0;
    }
 
    ps.push_back(h(1, 1));
    for (int i = 0; i < LEN; i++) {
        ps.push_back(ps.back() * h(P, P));
    }
 
    int r = LEN;
 
    for (int k = 0; k < n; k++) {
        vec[k].push_back(h(0, 0));
        string str;
 
        cin >> str;
        s[k] = str;
 
        r = min(r, (int)str.size());
 
        for (int i = 0; i < str.size(); i++) {
            vec[k].push_back(vec[k].back() + ps[i + 1] * h(str[i] - 'a' + 1, str[i] - 'a' + 1));
        }
    }
 
    r++;
    int l = 0;
    int m;
 
    h foundH(0, 0);
 
    while (r - l > 1) {
        map <h, int> mp;
        mp.clear();
        m = (l + r) / 2;
 
        for (int k = 0; k < n; k++) {
            set <h> st;
            st.clear();
 
            for (int i = 0; i < s[k].size(); i++) {
                if (i + m - 1 >= s[k].size())
                    break;
 
                h h1 = vec[k][i + m] + (-vec[k][i]);
                h1 = h1 * ps[ST - i];
 
                st.insert(h1);
            }
 
            for (h x : st) {
                if (mp.count(x) == 0)
                    mp[x] = 1;
                else
                    mp[x]++;
            }
        }
 
        bool ok = false;
 
        for (auto x : mp) {
            if (x.second == n) {
                foundH = x.first;
                ok = true;
                break;
            }
        }
 
        if (ok) {
            l = m;
        } else {
            r = m;
        }
    }
 
    if (l == 0)
        return 0;
 
    for (int i = 0; i < s[0].size(); i++) {
        if (i + l - 1 >= s[0].size())
            break;
 
        h h1 = vec[0][i + l] + (-vec[0][i]);
        h1 = h1 * ps[ST - i];
 
        if (h1 == foundH) {
            for (int j = 0; j < l; j++)
                cout << s[0][i + j];
 
            return 0;
        }
    }
 
    return 0;
}