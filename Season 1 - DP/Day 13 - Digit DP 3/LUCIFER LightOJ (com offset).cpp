#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int OFFSET = 100;

int tb[10][10][110 + OFFSET][2][2];

bool is_prime(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;

    for (long long i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    
    return true;
}

int dp(string& number, int pos, int sz, int diff, bool under, bool started) {
    if (pos >= number.size()) {
        int new_diff = diff - OFFSET;
        
        if (sz % 2 == 0) return is_prime(new_diff);
        else return is_prime(-new_diff);
    }

    int& mem = tb[pos][sz][diff][under][started];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = under || d < limit;
        bool is_started = started || d != 0;

        if (!is_started) {
            mem += dp(number, pos+1, sz, diff, is_under, is_started);
        } else {
            int new_diff = diff;

            if (sz % 2 == 0) new_diff += d;
            else new_diff -= d;

            mem += dp(number, pos+1, sz+1, new_diff, is_under, is_started);
        }
    }

    return mem;
}

int solve(int ubound) {
    memset(tb, -1, sizeof(tb));
    string number = to_string(ubound);
    return dp(number, 0, 0, OFFSET, false, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;

        cout << solve(b) - solve(a-1) << '\n';
    }
    
    return 0;
}