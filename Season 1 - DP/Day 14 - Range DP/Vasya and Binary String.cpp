#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 110;

ll n, points[MAX], tb[MAX][MAX][MAX];
string s;

ll dp(int left, int right, int consecutive_digits) {
    if (left > right) return 0;
    
    ll& mem = tb[left][right][consecutive_digits];
    if (mem != -1) return mem;
    
    mem = points[consecutive_digits] + dp(left+1, right, 1);
    for (int i = left+1; i <= right; i++) {
        if (s[left] == s[i]) {
            mem = max(mem, dp(left+1, i-1, 1) + dp(i, right, consecutive_digits+1));
        }
    }
    
    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;
    for (int i = 1; i <= n; i++) cin >> points[i];
    
    memset(tb, -1, sizeof(tb));
    
    cout << dp(0, n-1, 1) << '\n';

    return 0;
}