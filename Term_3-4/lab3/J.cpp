#include <bits/stdc++.h>
using namespace std;
 
const int LEN = 4e5 + 9;
 
string str;
vector <pair<char, int>> vec;
int block[LEN];
int newBlock[LEN];
int lcp[LEN];
 
map <int, int> mp;
 
int k;
 
bool cmp(pair <char, int> a, pair <char, int> b) {
    if (block[a.second] == block[b.second]) {
        return block[(a.second + (1 << (k - 1))) % str.size()] < block[(b.second + (1 << (k - 1))) % str.size()];
    }
 
    return block[a.second] < block[b.second];
}
 
int main() {
    cin >> str;
    str += char ('a' - 1);
 
    for (int i = 0; i < str.size(); i++) {
        vec.push_back({str[i], i});
    }
 
    sort(vec.begin(), vec.end());
 
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i - 1].first == vec[i].first) {
            block[vec[i].second] = block[vec[i - 1].second];
        } else {
            block[vec[i].second] = block[vec[i - 1].second] + 1;
        }
    }
 
    for (k = 1; (1 << (k - 1)) <= str.size(); k++) {
        sort(vec.begin(), vec.end(), cmp);
 
        newBlock[vec[0].second] = 0;
        for (int i = 1; i < vec.size(); i++) {
            if (block[vec[i].second] == block[vec[i - 1].second]) {
                if (block[(vec[i].second + (1 << (k - 1))) % str.size()] == block[(vec[i - 1].second + (1 << (k - 1))) % str.size()]) {
                    newBlock[vec[i].second] = newBlock[vec[i - 1].second];
                } else {
                    newBlock[vec[i].second] = newBlock[vec[i - 1].second] + 1;
                }
            } else {
                newBlock[vec[i].second] = newBlock[vec[i - 1].second] + 1;
            }
        }
 
        swap(newBlock, block);
    }
 
    for (int i = 1; i < str.size(); i++) {
        cout << vec[i].second + 1 << " ";
 
        mp[vec[i].second] = i;
    }
 
    cout << "\n";
 
    int cur = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != str[i + vec[mp[0] - 1].second])
            break;
 
        cur++;
    }
 
    lcp[mp[0] - 1] = cur;
 
    for (int i = 1; i < str.size() - 1; i++) {
        int ans = max(0, lcp[mp[i - 1] - 1] - 1);
 
        while (str[ans + vec[mp[i] - 1].second] == str[ans + vec[mp[i]].second]) {
            ans++;
        }
 
        lcp[mp[i] - 1] = ans;
    }
 
    for (int i = 1; i < str.size() - 1; i++) {
        cout << lcp[i] << " ";
    }
 
 
    return 0;
}