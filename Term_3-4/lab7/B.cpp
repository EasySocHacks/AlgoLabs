#include <bits/stdc++.h>
using namespace std;

const int LEN = 1000009;

int n;
int last[LEN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fill(last, last + LEN, -1);

    cin >> n;

    for (int i = 2; i < LEN; i++) {
        if (last[i] != -1)
            continue;

        for (int j = i; j <  LEN; j += i)
            if (last[j] == -1)
                last[j] = i;
    }

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;

        vector <int> ans;
        while (x != 1) {
            ans.push_back(last[x]);
            x /= last[x];
        }

        sort(ans.begin(), ans.end());

        for (auto y : ans)
            cout << y << " ";
        cout << "\n";
    }

    return 0;
}
