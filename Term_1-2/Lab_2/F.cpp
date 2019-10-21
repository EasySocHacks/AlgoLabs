#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

int n;
vector <int> vec;
vector <int> sortVec;

vector <int> st;
int pos = 0;

string ans = "";

int main() {
    cin >> n;

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;

        vec.pb(x);
        sortVec.pb(x);
    }

    sort(sortVec.begin(), sortVec.end());

    for (int i = 0; i < n; i++) {
        st.pb(vec[i]);
        ans += "push\n";

        while (!st.empty()) {
            if (st.back() != sortVec[pos])
                break;

            pos++;
            st.pop_back();

            ans += "pop\n";
        }
    }

    if (!st.empty()) {
        cout << "impossible";
        return 0;
    }

    cout << ans;

    return 0;
}
