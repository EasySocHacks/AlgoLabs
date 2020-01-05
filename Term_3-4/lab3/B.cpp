#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 1e6 + 9;
 
string str;
int n;
 
int p[LEN];
 
int main() {
    cin >> str;
 
    for (int i = 1; i < str.size(); i++) {
        int tmp = p[i - 1];
 
        while (tmp > 0 && str[i] != str[tmp]) {
            tmp = p[tmp - 1];
        }
 
        if (str[tmp] == str[i]) {
            p[i] = tmp + 1;
        }
    }
 
    for (int i = 0; i < str.size(); i++)
        cout << p[i] << " ";
 
    return 0;
}