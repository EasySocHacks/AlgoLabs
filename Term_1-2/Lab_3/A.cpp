#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

const int LEN = 10009;
const int INF = 1e9;

int n, k;
int arr[LEN];
int dp[LEN];
int par[LEN];

vector <int> ans;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> k;

    for (int i = 1; i < n - 1; i++) {
        cin >> arr[i];
        dp[i] = -INF;
    }

    dp[n - 1] = -INF;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j <= k; j++) {
            if (i + j >= n)
                break;

            if (dp[i + j] < dp[i] + arr[i + j]) {
                dp[i + j] = dp[i] + arr[i + j];

                par[i + j] = i;
            }
        }
    }

    int pos = n - 1;

    while(pos != 0) {
        ans.pb(pos + 1);

        pos = par[pos];
    }

    ans.pb(1);

    cout << dp[n - 1] << "\n";
    cout << ans.size() - 1 << "\n";
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }

    return 0;
}
