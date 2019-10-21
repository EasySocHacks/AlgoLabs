#include <iostream>
using namespace std;

const int LEN = 1e5 + 1;

int n;

int stColor[LEN];
int stSame[LEN];
int length = 0;

int ans = 0;

int main() {
    scanf("%d", &n);

    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);

        stColor[length] = x;
        stSame[length] = 1;

        if (length > 0 && stColor[length - 1] == stColor[length]) {
            stSame[length] += stSame[length - 1];
        }

        if (length > 0 && stColor[length] != stColor[length - 1] && stSame[length - 1] >= 3) {
            stColor[length - stSame[length - 1]] = stColor[length];
            stSame[length - stSame[length - 1]] = 1;

            ans += (stSame[length - 1]);
            length -= (stSame[length - 1]);

            if (length > 0 && stColor[length - 1] == stColor[length])
                stSame[length] += stSame[length - 1];
        }

        length++;
    }

    if (length > 0 && stSame[length - 1] >= 3)
        ans += stSame[length - 1];

    printf("%d", ans);

    return 0;
}
