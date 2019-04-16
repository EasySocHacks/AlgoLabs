#include <iostream>
using namespace std;

typedef long long ll;

const int LEN1 = 1e7 + 9;
const int LEN2 = 2e7 + 9;
const int _2_30 = (1 << 30);
const int _2_16 = (1 << 16);

long long a[LEN1];
int b[LEN2];

int n, x, y;
int m, z, t;

int getMod(ll a, int b) {
    if (a < b) return a;

    return (a + b) % b;
}

int modSumm(int a, int b, int mod) {
    return getMod(a + b, mod);
}

int modMultiply(ll a, int b, int mod) {
    return getMod(a * b, mod);
}

long long getSumm(int pos) {
    if (pos == -1)
        return 0;

    return a[pos];
}

int main() {
    scanf("%d%d%d%d", &n, &x, &y, &a[0]);
    scanf("%d%d%d%d", &m, &z, &t, &b[0]);

    for (int i = 1; i < LEN1; i++) {
        a[i] = (modSumm(modMultiply(x, a[i - 1], _2_16), y, _2_16));
    }

    for (int i = 1; i < LEN1; i++) {
        a[i] += a[i - 1];
    }

    for (int i = 1; i < LEN2; i++) {
        b[i] = (modSumm(modMultiply(z, b[i - 1], _2_30), t, _2_30));
    }

    for (int i = 0; i < LEN2; i++) {
        b[i] = getMod(b[i], n);
    }

    long long ans = 0;

    int l, r;
    for (int i = 0; i < m; i++) {
        l = min(b[2 * i], b[2 * i + 1]);
        r = max(b[2 * i], b[2 * i + 1]);

        ans += getSumm(r) - getSumm(l - 1);
    }

    printf("%lld", ans);

    return 0;
}
