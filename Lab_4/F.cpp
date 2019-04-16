#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 1e5 + 9;
const int MOD = 16714589;
const int POW_LEN = 17;

int n, m, u, v;
int a[LEN];

int table[LEN][POW_LEN];

int getMod(ll a, int b) {
    if (a < b) return a;

    return a % b;
}

int modSumm(int a, int b, int mod) {
    return getMod(getMod(a, mod) + getMod(b, mod), mod);
}

int modProduce(ll a, int b, int mod) {
    return getMod(a * getMod(b, mod), mod);
}

int getAns() {
    int len = max(v - 1, u - 1) - min(v - 1, u - 1) + 1;

    int pw = 0;

    while ((1 << pw) <= len)
        pw++;
    pw--;

    return min(table[min(v - 1, u - 1)][pw], table[max(v - 1, u - 1) - (1 << pw) + 1][pw]);
}

int main() {
    cin >> n >> m >> a[0] >> u >> v;

    table[0][0] = a[0];
    for (int i = 1; i < n; i++) {
        a[i] = modSumm(modProduce(23, a[i - 1], MOD), 21563, MOD);

        table[i][0] = a[i];
    }

    for (int i = 1; i < POW_LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            if (j + (1 << i) - 1 >= LEN)
                continue;

            table[j][i] = min(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
        }
    }

    for (int i = 1; i < m; i++) {
        int ans = getAns();

        int x = modSumm(modProduce(17, u, n), 751, n);
        int y = modSumm(ans, 2 * i, n);
        u = modSumm(x, y, n) + 1;

        x = modSumm(modProduce(13, v, n), 593, n);
        y = modSumm(ans, 5 * i, n);
        v = modSumm(x, y, n) + 1;
    }

    cout << u << " " << v << " " << getAns();

    return 0;
}
