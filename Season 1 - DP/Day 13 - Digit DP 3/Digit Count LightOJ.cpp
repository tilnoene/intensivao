#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

ll tb[10][10];

ll dp(int& n, vector<int>& digits, int last_digit, int sz) {
    if (sz >= n) return 1;

    ll& mem = tb[last_digit][sz];
    if (mem != -1) return mem;
    
    mem = 0;

    for (int i = 0; i < digits.size(); i++) {
        if (abs(last_digit - digits[i]) <= 2) {
            mem += dp(n, digits, digits[i], sz+1);
        }
    }

    return mem;
}

ll solve() {
    int m, n; cin >> m >> n;
    vector<int> digits(m);
    for (int i = 0; i < m; i++) {
        cin >> digits[i];
    }

    ll ans = 0;

    for (int i = 0; i < m; i++) {
        memset(tb, -1, sizeof(tb));
        ans += dp(n, digits, digits[i], 1);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ": " << solve() << '\n';
    }
    
    return 0;
}