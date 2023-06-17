#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX_D = 10;
const int MAX_SUM = MAX_D * 10;

int tb[MAX_D][MAX_SUM][MAX_SUM][2];

int dp(string& number, int k, int pos, int sum, int rem, bool under) {
    if (pos >= number.size()) {
        return (sum % k == 0 && rem == 0);
    }

    int& mem = tb[pos][sum][rem][under];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = (under || d < limit);
        
        if ((rem*10 + d) % k >= MAX_SUM) continue;
        
        mem += dp(number, k, pos+1, sum + d, (rem * 10 + d) % k, is_under);
    }

    return mem;
}

int solve(int ubound, int k) {
    // if (k >= MAX_SUM) return 0; // só isso funciona
    memset(tb, -1, sizeof(tb));
    string number = to_string(ubound);
    return dp(number, k, 0, 0, 0, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        int a, b, k; cin >> a >> b >> k;

        cout << "Case " << i << ": " << solve(b, k) - solve(a-1, k) << '\n';
    }
    
    return 0;
}