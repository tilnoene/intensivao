#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 21;
const int MOD = 1e9+7;

bool compatible[MAX][MAX];
int dp[(1 << MAX)];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> compatible[i][j];
        }
    }
    
    dp[0] = 1;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        int man = __builtin_popcount(mask);
        
        for (int woman = 0; woman < n; woman++) {
            if ((mask & (1 << woman)) || (!compatible[man][woman])) continue;
            
            dp[mask | (1 << woman)] = (dp[mask | (1 << woman)] + dp[mask]) % MOD;
        }
    }
    
    cout << dp[(1 << n) - 1] << '\n';

    return 0;
}