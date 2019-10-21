#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

const int LEN = 2009;
const int INF = 1e9 + 10;

int n;
int arr[LEN];

int dp[LEN];
int pos[LEN];
int par[LEN];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    for (int i = 0; i < LEN; i++)
        dp[i] = INF;

    for (int i = 0; i < n; i++) {
        if (arr[i] < dp[0]) {
            dp[0] = arr[i];
            pos[0] = i;
            par[i] = -1;
            continue;
        }

        for (int j = 0; j < LEN - 1; j++) {
            if (dp[j] < arr[i] && dp[j + 1] > arr[i]) {
                dp[j + 1] = arr[i];
                pos[j + 1] = i;
                par[i] = pos[j];
                break;
            }
        }
    }

    int p = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (dp[i] == INF)
            continue;

        p = pos[i];
        break;
    }

    vector <int> ans;

    while (p != -1) {
        ans.pb(arr[p]);

        p = par[p];
    }

    cout << ans.size() << "\n";
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << " ";

    return 0;
}
