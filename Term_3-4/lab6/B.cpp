#include <bits/stdc++.h>
using namespace std;

const int LEN = 309;
const int INF = 1e9;

int n;
int matrix[LEN][LEN];

bool used[LEN];
int matchR[LEN];
int matchL[LEN];
int lastMatchR[LEN];

int addI[LEN];
int addJ[LEN];
int bestI[LEN];

bool markL[LEN];
bool markR[LEN];

int ans = 0;

bool khun(int v) {
    if (used[v])
        return false;

    used[v] = true;
    for (int u = 0; u < n; u++) {
        if (matrix[v][u] != 0) {
            continue;
        }

        if (matchR[u] == -1 || khun(matchR[u])) {
            matchR[u] = v;
            matchL[v] = u;

            return true;
        }
    }

    return false;
}


void usePath(int v) {
    int u = lastMatchR[v];

    if (matchL[u] != -1) {
        int vv = matchL[u];

        usePath(vv);
    }

    matchL[u] = v;
    matchR[v] = u;
}

int M = 0;

int main() {
    for (int i = 0; i < LEN; i++) {
        bestI[i] = -1;
        lastMatchR[i] = -1;
    }

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        int minn = INF;

        for (int j = 0; j < n; j++) {
            minn = min(minn, matrix[i][j]);
        }

        addI[i] -= minn;
    }

    for (int j = 0; j < n; j++) {
        int minn = INF;

        for (int i = 0; i < n; i++) {
            minn = min(minn, matrix[i][j]);
        }

        addJ[j] -= minn;
    }

    fill(matchR, matchR + LEN, -1);
    fill(matchL, matchL + LEN, -1);
    for (int i = 0; i < n; i++) {
        fill(used, used + LEN, false);

        khun(i);
    }

    for (int i = 0; i < n; i++) {
        if (matchR[i] != -1) {
            M++;
        }
    }

    fill(markL, markL + LEN, false);
    fill(markR, markR + LEN, false);
    for (int i = 0; i < n; i++) {
        if (matchL[i] == -1) {
            markL[i] = true;

            for (int j = 0; j < n; j++) {
                if (bestI[j] == -1 || matrix[bestI[j]][j] > matrix[i][j]) {
                    bestI[j] = i;
                }
            }
        }
    }

    fill(addI, addI + LEN, 0);
    fill(addJ, addJ + LEN, 0);

    while (M < n) {
        int delta = INF;
        int deltaU = -1;
        int deltaV = -1;

        for (int i = 0; i < n; i++) {
            if (markR[i])
                continue;

            int u = i;
            int v = bestI[i];

            if (v != -1 && delta > matrix[v][u] + addI[v] + addJ[u]) {
                delta = matrix[v][u] + addI[v] + addJ[u];

                deltaV = v;
                deltaU = u;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!markL[i])
                continue;

            addI[i] -= delta;
        }

        for (int j = 0; j < n; j++) {
            if (!markR[j])
                continue;

            addJ[j] += delta;
        }

        markR[deltaU] = true;

        if (matchR[deltaU] == -1) {

            lastMatchR[deltaU] = deltaV;
            usePath(deltaU);

            M++;

            fill(markL, markL + LEN, false);
            fill(markR, markR + LEN, false);
            fill(lastMatchR, lastMatchR + LEN, -1);
            fill(bestI, bestI + LEN, -1);

            for (int i = 0; i < n; i++) {
                if (matchL[i] == -1) {
                    markL[i] = true;

                    for (int j = 0; j < n; j++) {
                        if (bestI[j] == -1 || matrix[bestI[j]][j] + addI[bestI[j]] + addJ[j] > matrix[i][j] + addI[i] + addJ[j]) {
                            bestI[j] = i;
                        }
                    }
                }
            }
        } else {
            markL[matchR[deltaU]] = true;

            lastMatchR[deltaU] = deltaV;

            for (int j = 0; j < n; j++) {
                if (markR[j])
                    continue;

                if (bestI[j] == -1 || matrix[bestI[j]][j] + addI[bestI[j]] + addJ[j] > matrix[matchR[deltaU]][j] + addI[matchR[deltaU]] + addJ[j]) {
                    bestI[j] = matchR[deltaU];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ans += matrix[i][matchL[i]];
    }

    cout << ans << "\n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << matchL[i] + 1 << "\n";
    }

    return 0;
}
