#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int tb[10][10][100][100][2][2];

bool is_prime(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;

    for (long long i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    
    return true;
}

int dp(string& number, int pos, int sz, int sum_even, int sum_odd, bool under, bool started) {
    if (pos >= number.size()) {
        if (sz % 2 == 0) return is_prime(sum_even - sum_odd);
        else return is_prime(sum_odd - sum_even);
    }

    int& mem = tb[pos][sz][sum_even][sum_odd][under][started];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = under || d < limit;
        bool is_started = started || d != 0;

        if (!is_started) {
            mem += dp(number, pos+1, sz, sum_even, sum_odd, is_under, is_started);
        } else {
            int new_sum_even = sum_even;
            int new_sum_odd = sum_odd;

            if (sz % 2 == 0) new_sum_even += d;
            else new_sum_odd += d;

            mem += dp(number, pos+1, sz+1, new_sum_even, new_sum_odd, is_under, is_started);
        }
    }

    return mem;
}

int solve(int ubound) {
    memset(tb, -1, sizeof(tb));
    string number = to_string(ubound);
    return dp(number, 0, 0, 0, 0, false, false);
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