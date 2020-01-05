#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 1e6 + 9;
 
string str;
int z[LEN];
 
int main() {
    cin >> str;
 
    int l = -1, r = -1;
    for (int i = 1; i < str.size(); i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
 
        while (i + z[i] < str.size() && str[i + z[i]] == str[z[i]])
            z[i]++;
 
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
 
    for (int i = 1; i < str.size(); i++)
        cout << z[i] << " ";
 
    return 0;
}