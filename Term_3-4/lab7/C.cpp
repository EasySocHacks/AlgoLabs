#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int operationsToCheckPrime = 10;

int n;

ll modProduce(ll a, ll b, ll mod) {
    ll ans = 0;

    while (b > 0) {
        if (b % 2 != 0) {
            ans = (ans + a) % mod;
        }

        a = (a + a) % mod;
        b /= 2;
    }

    return ans;
}

ll binPow(ll x, ll power, ll mod) {
    ll ans = 1;

    while (power > 0) {
        if (power % 2 == 1) {
            ans = modProduce(ans, x, mod);
        }

        x = modProduce(x, x, mod);

        power /= 2;
    }

    return ans;
}

bool solve(ll n) {
    if (n == 1)
        return false;
    if (n == 2)
        return true;

    ll x = (abs(((ll)rand() << 32) | rand()) % (n - 2)) + 2;

    int maxPower = 0;
    long long mod = n;

    n--;


    while (n % 2 == 0) {
        maxPower++;
        n /= 2;
    }

    ll ret = binPow(x, n, mod);

    if (ret == 1 || ret == mod - 1)
        return true;

    for (int i = 1; i < maxPower; i++) {
        ret = modProduce(ret, ret, mod);

        if (ret == 1) {
            return false;
        }

        if (ret == mod - 1) {
            return true;
        }
    }

    return false;
}

int main() {
    srand(time(0));

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    ll x;

    for (int i = 0; i < n; i++) {
        cin >> x;

        bool ok = false;

        for (int j = 0; j < operationsToCheckPrime; j++) {
            bool ans = solve(x);

            if (!ans) {
                cout << "NO\n";

                ok = true;

                break;
            }
        }

        if (!ok) {
            cout << "YES\n";
        }
    }

    return 0;
}
