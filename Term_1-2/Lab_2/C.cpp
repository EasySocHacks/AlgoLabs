#include <iostream>
using namespace std;

const int LEN = 1e5 + 9;

int n;

int frontSt[LEN];
int frontSize = 0;

int backSt[LEN];
int backSize = 0;

int helpSt[LEN];
int helpSize = 0;

pair <int, int> person[LEN];

void frontEmpty() {
    if (backSize <= 0) return;
    if (backSize == 1) {
        frontSize = 1;
        backSize = 0;

        frontSt[0] = backSt[0];
        person[frontSt[0]] = {1, 0};
        return;
    }

    int sz = backSize;
    for (int i = 0; i < sz / 2; i++) {
        helpSt[helpSize++] = backSt[backSize - 1];
        backSize--;
    }

    for (int i = 0; i < backSize;) {
        frontSt[frontSize++] = backSt[backSize - 1];
        person[frontSt[frontSize - 1]] = {1, frontSize - 1};
        backSize--;
    }

    for (int i = 0; i < helpSize;) {
        backSt[backSize++] = helpSt[helpSize - 1];
        person[backSt[backSize - 1]] = {2, backSize - 1};
        helpSize--;
    }
}

void backEmpty() {
    if (frontSize <= 0) return;
    if (frontSize == 1) {
        backSize = 1;
        frontSize = 0;

        backSt[0] = frontSt[0];
        person[backSt[0]] = {2, 0};
        return;
    }

    int sz = frontSize;
    for (int i = 0; i < sz / 2; i++) {
        helpSt[helpSize++] = frontSt[frontSize - 1];
        frontSize--;
    }

    for (int i = 0; i < frontSize;) {
        backSt[backSize++] = frontSt[frontSize - 1];
        person[backSt[backSize - 1]] = {2, backSize - 1};
        frontSize--;
    }

    for (int i = 0; i < helpSize;) {
        frontSt[frontSize++] = helpSt[helpSize - 1];
        person[frontSt[frontSize - 1]] = {1, frontSize - 1};
        helpSize--;
    }
}

int main() {
    scanf("%d", &n);

    int type;
    int id, q;
    for (int i = 0; i < n; i++) {
        scanf("%d", &type);;

        if (type == 1) {
            scanf("%d", &id);

            backSt[backSize++] = id;
            person[id] = {2, backSize - 1};
        }
        if (type == 2) {
            if (frontSize == 0)
                frontEmpty();
            frontSize--;
        }
        if (type == 3) {
            if (backSize == 0)
                backEmpty();
            backSize--;
        }
        if (type == 4) {
            scanf("%d", &q);

            if (person[q].first == 1) {
                printf("%d\n", frontSize - person[q].second - 1);
            } else {
                printf("%d\n", frontSize + person[q].second);
            }
        }
        if (type == 5) {
            if (frontSize == 0)
                frontEmpty();

            printf("%d\n", frontSt[frontSize - 1]);
        }
    }

    return 0;
}
