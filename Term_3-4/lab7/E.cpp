#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, e, c;

ll binPow(ll a, ll b, ll mod) {
    if (b == 0) {
        return 1 % mod;
    }

    if (b % 2 == 0) {
        ll ret = binPow(a, b / 2, mod);

        return (ret * ret) % mod;
    } else {
        return (binPow(a, b - 1, mod) * (a % mod)) % mod;
    }
}

ll gcd (ll a, ll b) {
	while (b) {
		a %= b;
		swap (a, b);
	}
	return a;
}

ll getPhi (ll n) {
	ll res = n;
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			res -= res / i;
		}
	if (n > 1)
		res -= res / n;
	return res;
}

int main() {
    cin >> n >> e >> c;

    ll p, q;

    for (int i = 2; i < 100000; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;

            break;
        }
    }

    ll fi = (p - 1) * (q - 1);

    ll cnt = getPhi(fi);

    ll d = binPow(e, cnt - 1, fi);

    ll m = binPow(c, d, n);

    cout << m;

    return 0;
}
