#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 10009;
const double INF = 1e18;
 
struct point {
    double x, y;
 
    point(double x, double y) : x(x), y(y) {}
 
    double dist() {
        return sqrt(x * x + y * y);
    }
};
 
point operator - (point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}
 
int n;
vector <point> coord;
 
double ANS = 0.0;
pair<double, int> d[LEN];
 
int main() {
    cin >> n;
 
    int _x, _y;
 
    for (int i = 0; i < n; i++) {
        cin >> _x >> _y;
 
        coord.push_back(point(_x, _y));
    }
 
    d[0] = {-INF, 0};
 
    for (int i = 1; i < n; i++) {
        d[i] = {(coord[0] - coord[i]).dist(), 0};
    }
 
    for (int i = 0; i < n - 1; i++) {
        int ansf = -1;
        int anst = -1;
        double ans_d = INF;
 
        for (int j = 0; j < n; j++) {
            if (d[j].first < 0)
                continue;
 
            if (ans_d > d[j].first) {
                ans_d = d[j].first;
                anst = j;
                ansf = d[j].second;
            }
        }
 
        ANS += ans_d;
 
        d[ansf] = {-INF, 0};
        d[anst] = {-INF, 0};
 
        for (int j = 0; j < n; j++) {
            if (d[j].first < 0)
                continue;
 
            if (d[j].first > (coord[j] - coord[anst]).dist()) {
                d[j] = {(coord[j] - coord[anst]).dist(), anst};
            }
        }
    }
 
    cout.precision(20);
    cout << ANS;
 
    return 0;
}
