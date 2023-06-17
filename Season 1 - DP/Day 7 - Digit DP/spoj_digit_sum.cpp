#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX_SZ = 20;
const int MAX_SUM = 170;

ll tb[MAX_SZ][MAX_SUM][2];

ll dp(ll x, int i, int sum, bool is_less) {
    if (i >= to_string(x).size()) return sum;
    
    ll& ans = tb[i][sum][is_less];
    if (ans != -1) return ans;

    ans = 0;

    int limit = (is_less ? 9 : (to_string(x)[i] - '0'));

    for (int d = 0; d <= limit; d++) {
        ans += dp(x, i+1, sum+d, (is_less ? true : (d < limit)));
    }

    return ans;
}

ll solve(ll x) {
    if (x <= 0) return 0;
    
    for (int i = 0; i < MAX_SZ; i++) {
        for (int j = 0; j < MAX_SUM; j++) {
            tb[i][j][0] = -1;
            tb[i][j][1] = -1;
        }
    }

    return dp(x, 0, 0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        ll a, b; cin >> a >> b;
        
        cout << solve(b) - solve(a-1) << '\n';
    }
    
    return 0;
}