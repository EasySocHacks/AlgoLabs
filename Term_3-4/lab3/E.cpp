#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll P = 31;
 
struct h {
    ll h1, h2;
 
    h(ll h1, ll h2) : h1(h1), h2(h2) {}
};
 
h operator + (h a, h b) {
    return h((((a.h1 + MOD1) % MOD1) + ((b.h1 + MOD1) % MOD1)) % MOD1, (((a.h2 + MOD2) % MOD2) + ((b.h2 + MOD2) % MOD2)) % MOD2);
}
 
h operator - (h a) {
    return h(-a.h1, -a.h2);
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
 
string str;
 
vector <h> vec;
vector <h> ps;
 
 
int main() {
    cin >> str;
 
    ps.push_back(h(1, 1));
    for (int i = 0; i < str.size() + 10; i++) {
        ps.push_back(ps.back() * h(P, P));
    }
 
    vec.push_back(h(0, 0));
 
    for (int i = 0; i < str.size(); i++) {
        vec.push_back(vec[i] + (ps[i + 1] * h(str[i] - 'a' + 1, str[i] - 'a' + 1)));
    }
 
    for (int i = 1; i < str.size(); i++) {
        h h1 = vec[i];
        h h2 = vec[str.size()] - vec[i];
        h h3 = vec[str.size()];
 
        h1 = h1 * ps[str.size()];
        h3 = h3 * ps[i];
 
        if (h2 + h1 == h3) {
            cout << i;
            return 0;
        }
    }
 
    cout << str.size();
 
    return 0;
}