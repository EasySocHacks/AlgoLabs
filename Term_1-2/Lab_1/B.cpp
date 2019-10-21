#include <iostream>

using namespace std;

const int LEN = 200009;

int n = 0;
int arr[LEN];

int counter[101];

int main() {
    while (cin >> arr[n]) {
        counter[arr[n]]++;
        n++;
    }

    int m = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < counter[i]; j++) {
            arr[m++] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
