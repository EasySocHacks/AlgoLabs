#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

typedef long long ll;

const int CONSTANT = 300;

struct Node {
    Node *L, *R, *P;
    int sz;
    int y;
    int existsLetters;
    char letter;
    int letterCnt;

    Node(char _letter, int _letterCnt) {
        L = nullptr;
        R = nullptr;
        sz = _letterCnt;
        y = (rand() << 16) | rand();

        letter = _letter;
        letterCnt = _letterCnt;
        existsLetters = (1 << (letter - 'a'));
    }
};

int getSize(Node* T) {
    if (T == nullptr)
        return 0;

    return T->sz;
}

int existsLetters(Node* T) {
    if (T == nullptr)
        return 0;

    return T->existsLetters;
}

void update(Node* T) {
    if (T == nullptr)
        return;

    T->sz = getSize(T->L) + getSize(T->R) + T->letterCnt;
    T->existsLetters = (existsLetters(T->L) | existsLetters(T->R) | (1 << (T->letter - 'a')));
}

int bitCnt(int x) {
    int cnt = 0;
    for (int i = 0; i < 31; i++) {
        if ((x & (1 << i)) != 0)
            cnt++;
    }

    return cnt;
}

Node* merge(Node* T1, Node* T2) {
    if (T1 == nullptr)
        return T2;
    if (T2 == nullptr)
        return T1;

    if (T1->y > T2->y) {
        T1->R = merge(T1->R, T2);
        update(T1->R);
        update(T1);
        return T1;
    } else {
        T2->L = merge(T1, T2->L);
        update(T2->L);
        update(T2);
        return T2;
    }
}

pair<Node*, Node*> split(Node* T, int x) {
    if (T == nullptr)
        return {nullptr, nullptr};

    int Lsz = getSize(T->L) + 1;
    int Rsz = getSize(T->L) + T->letterCnt;

    if (x >= Lsz && x < Rsz) {
        Node* f = new Node(T->letter, x - getSize(T->L));
        Node* s = new Node(T->letter, T->letterCnt - (x - getSize(T->L)));

        f->L = merge(T->L, f->L);
        update(f->L);
        update(f);

        s->R = merge(s->R, T->R);
        update(s->R);
        update(s);

        return {f, s};
    }

    if (x < Lsz) {
        pair <Node*, Node*> ret = split(T->L, x);

        T->L = ret.second;
        update(T->L);
        update(T);

        return {ret.first, T};
    } else {
        pair <Node*, Node*> ret = split(T->R, x - Rsz);

        T->R = ret.first;
        update(T->R);
        update(T);

        return {T, ret.second};
    }
}

Node* insertNode(Node* T, Node* t, int x) {
    pair <Node*, Node*> ret = split(T, x - 1);
    return merge(ret.first, merge(t, ret.second));
}

Node* deleteNode(Node *T, int x) {
    pair<Node*, Node*> ret1 = split(T, x - 1);
    pair<Node*, Node*> ret2 = split(ret1.second, 1);

    return merge(ret1.first, ret2.second);
}

Node *T = nullptr;
int n;
Node* arr [60009];
int pos = 0;

void fillArr(Node* T) {
    if (T == nullptr)
        return;

    fillArr(T->L);

    if (pos == 0) {
        arr[pos++] = T;
    } else {
        if (arr[pos - 1]->letter == T->letter) {
            arr[pos - 1]->letterCnt += T->letterCnt;
        } else {
            arr[pos++] = T;
        }
    }

    fillArr(T->R);
}

Node* X = nullptr;
Node* N = nullptr;
Node* insNode(Node*TT) {
    if (TT == nullptr) {
        X->L = N;
        if (N != nullptr)
            N->P = X;
        return X;
    }

    N = TT;

    if (TT->y < X->y) {
        return insNode(TT->P);
    }

    X->L = TT->R;
    if (TT->R != nullptr) TT->R->P = X;
    TT->R = X;
    X->P = TT;
    return X;
}

void upp(Node* T) {
    if (T == nullptr)
        return;

    upp(T->L);
    upp(T->R);

    update(T);
}

Node* getPar(Node *T) {
    if (T->P == nullptr)
        return T;
    return getPar(T->P);
}

void rebuild() {
    pos = 0;
    arr[0] = nullptr;
    fillArr(T);

    for (int i = 0; i < pos; i++) {
        arr[i]->L = nullptr;
        arr[i]->R = nullptr;
        arr[i]->P = nullptr;
        arr[i]->sz = arr[i]->letterCnt;
        arr[i]->existsLetters = (1 << (arr[i]->letter - 'a'));
        arr[i]->y = (rand() << 16) | rand();
    }

    T = arr[0];
    for (int i = 1; i < pos; i++) {
        X = arr[i];
        T = insNode(T);
    }

    T = getPar(T);

    upp(T);
}

int main() {
    srand(time(0));

    scanf("%d", &n);
    string q;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt++;

        if (cnt == CONSTANT) {
            cnt = 0;
            rebuild();
        }

        cin >> q;

        if (q == "+") {
            int index, number;
            string letter;

            scanf("%d%d", &index, &number);
            cin >> letter;

            T = insertNode(T, new Node(letter[0], number), index);
        }

        if (q == "-") {
            int index, number;

            scanf("%d%d", &index, &number);

            pair <Node*, Node*> p1 = split(T, index - 1);
            pair <Node*, Node*> p2 = split(p1.second, number);

            T = merge(p1.first, p2.second);
        }

        if (q == "?") {
            int index1, index2;

            scanf("%d%d", &index1, &index2);

            pair <Node*, Node*> p1 = split(T, index1 - 1);
            pair <Node*, Node*> p2 = split(p1.second, index2 - index1 + 1);

            printf("%d\n", bitCnt(existsLetters(p2.first)));

            T = merge(p1.first, merge(p2.first, p2.second));
        }
    }

    return 0;
}
