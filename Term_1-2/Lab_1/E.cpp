#include <iostream>

using namespace std;

const int LEN = 500009;

int n, k;
int l, r;

int arr[LEN];

void mergeSort(int l, int r) {
    if (r <= l)
        return;

    int newArr[r - l + 1];

    mergeSort(l, (r + l) / 2);
    mergeSort((r + l) / 2 + 1, r);

    int first = l;
    int second = (r + l) / 2 + 1;

    while (first <= (r + l) / 2 || second <= r) {
        if (first <= (r + l) / 2 && second <= r) {
            if (arr[first] <= arr[second]) {
                newArr[first - l + second - ((r + l) / 2 + 1)] = arr[first];
                first++;
            } else {
                newArr[first - l + second - ((r + l) / 2 + 1)] = arr[second];
                second++;
            }
        } else if (first <= (r + l) / 2) {
            newArr[first - l + second - ((r + l) / 2 + 1)] = arr[first];
            first++;
        } else {
            newArr[first - l + second - ((r + l) / 2 + 1)] = arr[second];
            second++;
        }
    }

    for (int i = l; i <= r; i++) {
        arr[i] = newArr[i - l];
    }
}

int upper(int x) {
    int l = -1, r = n;
    int m;

    while (r - l > 1) {
        m = (l + r) / 2;

        if (arr[m] > x)
            r = m;
        else
            l = m;
    }

    return l;
}

int lower(int x) {
    int l = -1, r = n;
    int m;

    while (r - l > 1) {
        m = (l + r) / 2;

        if (arr[m] < x)
            l = m;
        else
            r = m;
    }

    return r;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    mergeSort(0, n - 1);

    cin >> k;

    for (int i = 0; i < k; i++) {
        cin >> l >> r;

        cout << upper(r) - lower(l) + 1 << " ";
    }

    return 0;
}
