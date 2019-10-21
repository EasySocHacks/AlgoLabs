#include <iostream>

using namespace std;

const int LEN = 100000;

int n;
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

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    mergeSort(0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
