#include <bits/stdc++.h>
using namespace std;

const int LEN = 20000009;

int n;
bool isPrime[LEN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fill(isPrime, isPrime + LEN, true);

    cin >> n;

    for (int i = 2; i < LEN; i++) {
        if (!isPrime[i])
            continue;

        for (int j = 2 * i; j <  LEN; j += i)
            isPrime[j] = false;
    }

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;

        bool ans = isPrime[x];

        cout << (ans ? "YES\n" : "NO\n");
    }

    return 0;
}
