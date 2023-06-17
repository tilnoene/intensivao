#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAXT = 5e6+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    int t, a, b; cin >> t >> a >> b;
    vector<array<bool, 2>> dp(t+1); // is_possible to achieve the fullness of i
    
    dp[0][0] = true; // começa vazio
    dp[0][1] = true;

    int ans = 0;

    for (int i = 1; i <= t; i++) {
        // não bebendo água
        if (i-a >= 0) dp[i][0] |= dp[i-a][0];
        if (i-b >= 0) dp[i][0] |= dp[i-b][0];
        
        dp[i/2][1] |= dp[i][0];
    }

    for (int i = 1; i <= t; i++) {
        // bebendo água
        if (i-a >= 0) dp[i][1] |= dp[i-a][1];
        if (i-b >= 0) dp[i][1] |= dp[i-b][1];
    }
    
    for (int i = 1; i <= t; i++) {
        if (dp[i][0] || dp[i][1]) ans = i;
    }
    
    cout << ans << '\n';
    
    return 0;
}