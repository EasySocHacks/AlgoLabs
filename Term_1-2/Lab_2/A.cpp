#include <iostream>
using namespace std;

const int LEN = 1e6 + 1;

int n;
int stX[LEN];
int stMin[LEN];
int length = 0;

int main() {
    scanf("%d", &n);

    int type, x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &x);

            stX[length] = x;
            stMin[length] = min(x, (length == 0 ? x : stMin[length - 1]));

            length++;
        }

        if (type == 2)
            length--;

        if (type == 3)
            printf("%d\n", stMin[length - 1]);
    }

    return 0;
}
