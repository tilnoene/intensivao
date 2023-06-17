#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 1e5+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, h[MAX]; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int dp[MAX];
    
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        dp[i] = 1e9+17;
        
        for (int j = 1; j <= k; j++) {
            if (i - j < 0) break;

            dp[i] = min(dp[i], dp[i-j] + abs(h[i] - h[i-j]));
        }
    }
    
    cout << dp[n-1] << '\n';

    return 0;
}