#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int tb[10][100][100][2][2][10];

int dp(string& number, int pos, int sum_even, int sum_odd, bool under, bool started, int sz) {
    if (pos >= number.size()) {
        if (sz % 2 == 0) {
            return sum_even - sum_odd == 1;
        } else {
            return sum_odd - sum_even == 1;
        }
    }

    int& mem = tb[pos][sum_even][sum_odd][under][started][sz];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = under || d < limit;
        bool is_started = started || d != 0;

        if (!is_started) {
            mem += dp(number, pos+1, sum_even, sum_odd, is_under, is_started, sz);
        } else {
            int new_sum_even = sum_even;
            int new_sum_odd = sum_odd;

            if (sz % 2 == 0) new_sum_even += d;
            else new_sum_odd += d;

            mem += dp(number, pos+1, new_sum_even, new_sum_odd, is_under, is_started, sz+1);
        }
    }

    return mem;
}

int solve(int ubound) {
    memset(tb, -1, sizeof(tb));
    string number = to_string(ubound);
    return dp(number, 0, 0, 0, false, false, 0);
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