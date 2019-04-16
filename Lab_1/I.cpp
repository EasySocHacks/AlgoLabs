#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

const double EPS = 1e-9;

double c;

int main() {
    cin >> c;

    double l = 1.0, r = 1e9;
    double m;

    for (int i = 0; i < 100; i++) {
        m = (l + r) / 2.0;

        if (m * m + sqrt(m) - c <= EPS)
            l = m;
        else
            r = m;
    }

    printf("%.20f", l);

    return 0;
}
