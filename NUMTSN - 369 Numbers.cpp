#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX_SZ = 50 + 1;

ll tb[MAX_SZ][2][MAX_SZ][MAX_SZ][MAX_SZ];

ll dp(string& num, int pos, bool under, int cnt3, int cnt6, int cnt9) {
    if (pos >= (int)num.size()){
        return cnt3 == cnt6 && cnt6 == cnt9 && cnt3 >= 1;
    }

    ll& mem = tb[pos][under][cnt3][cnt6][cnt9];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = num[pos] - '0';

    for (int digit = 0; digit <= limit; digit++) {
        bool is_under = under | (digit < limit);

        mem += dp(num, pos+1, is_under, cnt3 + (digit == 3), cnt6 + (digit == 6), cnt9 + (digit == 9));
    }

    return mem;
}

ll solve(string ubound) {
    memset(tb, -1, sizeof(tb));
    return dp(ubound, 0, 0, 0, 0, 0);
}

string minus1(string num) {
    int it = (int)num.size()-1;
    while (num[it] == '0') it--;

    num[it] -= 1;
    for (int i = it+1; i < (int)num.size(); i++) {
        num[i] = '9';
    }
    
    return num;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        string a, b; cin >> a >> b;
        cout << solve(b) - solve(minus1(a)) << '\n';
    }
    
    return 0;
}