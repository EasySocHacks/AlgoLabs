#include <bits/stdc++.h>
using namespace std;

const int LEN = 130;

int n;
int fen[LEN][LEN][LEN];

void setFen(int x, int y, int z, int add) {
    for (int i = x; i < n; i = (i | (i + 1))) {
        for (int j = y; j < n; j = (j | (j + 1))) {
            for (int k = z; k < n; k = (k | (k + 1))) {
                fen[i][j][k] += add;
            }
        }
    }
}

int func(int x) {
    return (x & (x + 1)) - 1;
}

int getFenPref(int x, int y, int z) {
    int ans = 0;

    for (int i = x; i >= 0; i = func(i)) {
        for (int j = y; j >= 0; j = func(j)) {
            for (int k = z; k >= 0; k = func(k)) {
                ans += fen[i][j][k];
            }
        }
    }

    return ans;
}

int getFen(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1--;
    y1--;
    z1--;
    return getFenPref(x2, y2, z2) -
    1 * getFenPref(x2, y2, z1) - 1 * getFenPref(x2, y1, z2) - 1 * getFenPref(x1, y2, z2) +
    1 * getFenPref(x2, y1, z1) + 1 * getFenPref(x1, y2, z1) + 1 * getFenPref(x1, y1, z2) -
    1 * getFenPref(x1, y1, z1);
}

int main() {
    cin >> n;
    int t;

    while (true) {
        cin >> t;

        if (t == 3)
            break;

        if (t == 1) {
            int x, y, z, k;

            cin >> x >> y >> z >> k;
            setFen(x, y, z, k);
        }

        if (t == 2) {
            int x1, y1, z1, x2, y2, z2;

            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

            cout << getFen(x1, y1, z1, x2, y2, z2) << "\n";
        }
    }

    return 0;
}
