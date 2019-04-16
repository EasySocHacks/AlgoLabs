#include <iostream>
using namespace std;

const int LEN = 5e5 + 9;

struct deQueue {
    int frontSt[LEN];
    int frontSize = 0;

    int backSt[LEN];
    int backSize = 0;

    int helpSt[LEN];
    int helpSize = 0;

    deQueue() {}

    void frontEmpty() {
        if (backSize <= 0) return;
        if (backSize == 1) {
            frontSize = 1;
            backSize = 0;

            frontSt[0] = backSt[0];
            return;
        }

        int sz = backSize;
        for (int i = 0; i < sz / 2; i++) {
            helpSt[helpSize++] = backSt[backSize - 1];
            backSize--;
        }

        for (int i = 0; i < backSize;) {
            frontSt[frontSize++] = backSt[backSize - 1];
            backSize--;
        }

        for (int i = 0; i < helpSize;) {
            backSt[backSize++] = helpSt[helpSize - 1];
            helpSize--;
        }
    }

    void backEmpty() {
        if (frontSize <= 0) return;
        if (frontSize == 1) {
            backSize = 1;
            frontSize = 0;

            backSt[0] = frontSt[0];
            return;
        }

        int sz = frontSize;
        for (int i = 0; i < sz / 2; i++) {
            helpSt[helpSize++] = frontSt[frontSize - 1];
            frontSize--;
        }

        for (int i = 0; i < frontSize;) {
            backSt[backSize++] = frontSt[frontSize - 1];
            frontSize--;
        }

        for (int i = 0; i < helpSize;) {
            frontSt[frontSize++] = helpSt[helpSize - 1];
            helpSize--;
        }
    }

    void pushBack(int x) {
        backSt[backSize++] = x;
    }

    int popBack() {
        if (backSize == 0)
            backEmpty();

        backSize--;
        return backSt[backSize];
    }

    void pushFront(int x) {
        frontSt[frontSize++] = x;
    }

    int popFront() {
        if (frontSize == 0)
            frontEmpty();

        frontSize--;
        return frontSt[frontSize];
    }

    int size() {
        return frontSize + backSize;
    }
};

int n;

deQueue frontDQ, backDQ;

int main() {
    cin >> n;

    string type;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> type;

        if (type == "+") {
            cin >> x;
            backDQ.pushBack(x);

            if (backDQ.size() > frontDQ.size()) {
                frontDQ.pushBack(backDQ.popFront());
            }
        }

        if (type == "*") {
            cin >> x;

            if (frontDQ.size() == backDQ.size()) {
                frontDQ.pushBack(x);
            } else {
                backDQ.pushFront(x);
            }
        }

        if (type == "-") {
            cout << frontDQ.popFront() << "\n";

            if (backDQ.size() > frontDQ.size()) {
                frontDQ.pushBack(backDQ.popFront());
            }
        }
    }

    return 0;
}
