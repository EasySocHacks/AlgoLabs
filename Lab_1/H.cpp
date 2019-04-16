#include <iostream>

using namespace std;

long long w, h, n;

int main() {
    cin >> w >> h >> n;

    long long l = 0, r = n * max(w, h);
    long long m;
    while (r - l > 1) {
        m = (l + r) / 2;

        if ((m / w) * (m / h) >= n)
            r = m;
        else
            l = m;
    }

    cout << r;

    return 0;
}
