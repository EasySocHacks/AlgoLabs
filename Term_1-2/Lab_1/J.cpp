#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-18;

double vp, vf, a;

double getTime(double x) {
    if (1.0 - a <= EPS) {
        return x / max(vp, vf) + sqrt(a * a + (1 - x) * (1 - x)) / vf;
    }

    if (a <= EPS) {
        return sqrt(1.0 + x * x) / vp + (1 - x) / max(vp, vf);
    }

    return sqrt((1 - a) * (1 - a) + x  * x) / vp +
                sqrt(a * a + (1 - x) * (1 - x)) / vf;
}

int main() {
    cin >> vp >> vf >> a;

    double l = 0.0, r = 1.0;
    double m1, m2;

    for (int i = 0; i < 1000; i++) {
        m1 = l + (r - l) / 3.0;
        m2 = r - (r - l) / 3.0;

        if (getTime(m1) - getTime(m2) > -EPS)
            l = m1;
        else
            r = m2;
    }

    cout.precision(20);
    cout << l;

    return 0;
}
