#include <iostream>
#include <sstream>
using namespace std;

const int LEN = 300;

int st[LEN];
int length = 0;

int main() {

    string x;
    while (cin >> x) {
        if (x == "+" || x == "-" || x == "*") {
            int b = st[length - 1];
            int a = st[length - 2];

            if (x == "+") {
                st[length - 2] = a + b;
            }

            if (x == "-") {
                st[length - 2] = a - b;
            }

            if (x == "*") {
                st[length - 2] = a * b;
            }

            length--;
        } else {
            stringstream ss;
            ss << x;

            ss >> st[length++];
        }
    }

    cout << st[0];

    return 0;
}
