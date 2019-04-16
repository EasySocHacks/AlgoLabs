#include <cstdio>
using namespace std;

const int LEN = 2e5 + 9;
const int INF = 2e9 + 9;

struct Matrix {
    // a b
    // c d

    int a = INF, b = INF, c = INF, d = INF;

    Matrix(int _a, int _b, int _c, int _d) {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
    }

    Matrix() {
        a = INF;
        b = INF;
        c = INF;
        d = INF;
    }
};

bool operator == (Matrix a, int b) {
    return a.a == b && a.b == b && a.c == b && a.d == b;
}

int r, n, m;
Matrix tree[LEN * 4];
int sz = 1;

int getMod(long long a, int b) {
    if (a < b) {
        return a;
    }

    return a % b;
}

Matrix operator * (Matrix A, Matrix B) {
    if (A == INF)
        return B;
    if (B == INF)
        return A;

    int a = getMod(getMod((A.a * B.a), r) +  getMod((A.b * B.c), r), r);
    int b = getMod(getMod(A.a * B.b, r) + getMod(A.b * B.d, r), r);
    int c = getMod(getMod(A.c * B.a, r) + getMod(A.d * B.c, r), r);
    int d = getMod(getMod(A.c * B.b, r) + getMod(A.d * B.d, r), r);

    return Matrix(a, b, c, d);
}

Matrix multiply(int v, int l, int r, int a, int b) {
    if (r < a || l > b)
        return Matrix();

    if (a <= l && r <= b)
        return tree[v];

    int m = (l + r) / 2;
    return multiply(v * 2, l, m, a, b) * multiply(v * 2 + 1, m + 1, r, a, b);
}

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

    while (sz <= LEN) sz *= 2;

    scanf("%d%d%d", &r, &n, &m);

    int a, b, c, d;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);

        tree[sz + i] = Matrix(a, b, c, d);
    }

    for (int i = sz - 1; i >= 1; i--) {
        tree[i] = tree[i * 2] * tree[i * 2 + 1];
    }

    int l, r;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &l, &r);

        Matrix ans = multiply(1, 1, sz, l, r);

        printf("%d %d\n%d %d\n\n", ans.a, ans.b, ans.c, ans.d);
    }

    return 0;
}
