#include <bits/stdc++.h>
using namespace std;

#define int long long

struct diof {
    int d, x, y;

    diof() {
        d = 0;
        x = 0;
        y = 0;
    }

    diof(int d, int x, int y) : d(d), x(x), y(y) {}
};

int a, b, n, m;

diof gcd(int a, int b) {
    if (b == 0)
        return diof(a, 1, 0);

    diof ret = gcd(b, a % b);
    int x = ret.x;
    int y = ret.y;

    return diof(ret.d, y, x - y * (a / b));
}

signed main() {
    cin >> a >> b >> n >> m;

    diof df = gcd(n, m);
    long long f = (df.x * (b - a)) / df.d;

    long long x = (long long)a + f * n;

    while (x < 0) {
        x += (long long)n * m;
    }

    long long lastX = x;

    while (x >= 0) {
        x -= (long long)n * m;

        if (x >= 0) {
            lastX = x;
        }
    }

    cout << lastX;

    return 0;
}
