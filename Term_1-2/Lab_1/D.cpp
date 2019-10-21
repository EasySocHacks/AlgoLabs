#include <iostream>

using namespace std;

const int LEN = 300001;
const int INF = 1e9;

int n;
int heapSize = 0;
int heap[LEN];

void pushUp(int v) {
    if (v <= 0)
        return;
    if (heap[v] <= heap[(v - 1) / 2])
        return;

    swap(heap[v], heap[(v - 1) / 2]);
    pushUp((v - 1) / 2);
}

void pushDown(int v) {
    if (heap[v * 2 + 1] > heap[v * 2 + 2]) {
        if (heap[v * 2 + 1] > heap[v]) {
            swap(heap[v * 2 + 1], heap[v]);

            pushDown(v * 2 + 1);
        }
    } else {
        if (heap[v * 2 + 2] > heap[v]) {
            swap(heap[v * 2 + 2], heap[v]);

            pushDown(v * 2 + 2);
        }
    }
}

void insertHeap(int x) {
    heap[heapSize++] = x;
    pushUp(heapSize - 1);
}

int extractHeap() {
    int ans = heap[0];
    heap[0] = heap[heapSize - 1];
    heap[heapSize - 1] = -INF;

    pushDown(0);

    heapSize--;

    return ans;
}

int main() {
    for (int i = 0; i < LEN; i++)
        heap[i] = -INF;

    cin >> n;

    int type, x;

    for (int i = 0; i < n; i++) {
        cin >> type;

        if (type == 0) {
            cin >> x;

            insertHeap(x);
        } else {
            cout << extractHeap() << "\n";
        }
    }

    return 0;
}
