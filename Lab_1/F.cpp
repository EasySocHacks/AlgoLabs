#include <iostream>

using namespace std;

const int LEN = 100009;

int n, k;

int arr[LEN];
int request;

int upper(int x) {
    int l = -1, r = n;
    int m;

    while (r - l > 1) {
        m = (l + r) / 2;

        if (arr[m] >= x)
            r = m;
        else
            l = m;
    }

    return r;
}

int lower(int x) {
    int l = -1, r = n;
    int m;

    while (r - l > 1) {
        m = (l + r) / 2;

        if (arr[m] <= x)
            l = m;
        else
            r = m;
    }

    return l;
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int l, r, m;
    for (int i = 0; i < k; i++) {
        cin >> request;

        int up = upper(request);
        int low = lower(request);

        if (up == n) {
            cout << arr[low] << "\n";
        } else if (low == -1) {
            cout << arr[up] << "\n";
        } else {
            if (abs(arr[low] - request) > abs(arr[up] - request)) {
                cout << arr[up] << "\n";
            } else {
                cout << arr[low] << "\n";
            }
        }
    }

    return 0;
}
