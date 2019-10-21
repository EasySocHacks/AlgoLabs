#include <iostream>

using namespace std;

int n, x, y;

int main() {
    cin >> n >> x >> y;

    int l = min(x, y) - 1, r = 1e9;
    int m;

    while (r - l > 1) {
        m = (l + r) / 2;

        int canGetX = (m - min(x, y)) / x;
        int canGetY = (m - min(x, y)) / y;

        if (1 + canGetX + canGetY >= n)
            r = m;
        else
            l = m;
    }

    cout << r;

    return 0;
}
