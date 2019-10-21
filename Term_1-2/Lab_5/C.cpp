#include <iostream>
#include <algorithm>
using namespace std;

const int LEN = 300009;

struct Node {
    Node *L, *R, *P;
    int x, y;
    int ind;

    Node(int _x, int _y, int _ind) {
        L = nullptr;
        R = nullptr;
        P = nullptr;
        x = _x;
        y = _y;
        ind = _ind;
    }
};

int n;
pair <pair<int, int>, int>  coords[LEN];
pair <pair<int, int>, int> anss[LEN];

Node *T;
Node *N = nullptr;

Node* X = nullptr;
Node* insertNode(Node*TT) {
    if (TT == nullptr) {//cout << T->x << " " << T->y << " ||| " << x->x << " " << x->y << "\n";
        X->L = N;
        if (N != nullptr)
            N->P = X;
        return X;
    }

    N = TT;

    if (TT->y > X->y) {
        return insertNode(TT->P);
    }

    //cout << TT->x << " " << TT->y << " " << " ~~ " << x->x << " " << x->y << "\n";

    X->L = TT->R;
    if (TT->R != nullptr) TT->R->P = X;
    TT->R = X;
    X->P = TT;
    return X;
}

int getX(Node *T) {
    if (T == nullptr)
        return 0;

    return T->ind;
}

void getAns(Node *T) {
    if (T == nullptr)
        return;

    anss[T->ind - 1] = {{getX(T->P), getX(T->L)}, getX(T->R)};

    getAns(T->L);
    getAns(T->R);
}

Node* getPar(Node *T) {
    if (T->P == nullptr)
        return T;
    return getPar(T->P);
}

int main() {
    scanf("%d", &n);
    int x, y;

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        coords[i] = {{x, y}, i + 1};
    }

    sort(coords, coords + n);

    T = new Node(coords[0].first.first, coords[0].first.second, coords[0].second);


    for (int i = 1; i < n; i++) {
        X = new Node(coords[i].first.first, coords[i].first.second, coords[i].second);
        T = insertNode(T);
    }

    printf("YES\n");
    getAns(getPar(T));

    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", anss[i].first.first, anss[i].first.second, anss[i].second);
    }

    return 0;
}
