#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    
    int n, k; cin >> n >> k;
    vector<int> skill(n);
    for (int i = 0; i < n; i++) { cin >> skill[i]; }

    vector<int> dp(n+1, 0); // dp[i] = maximum skill for cows up to i

    for (int cow = 0; cow < n; cow++) {
        int most_skilled = skill[cow];

        for (int j = cow; j >= max(0, cow-k+1); j--) {
            most_skilled = max(most_skilled, skill[j]);
            
            if (j == 0) {
                dp[cow] = max(dp[cow], (cow-j+1) * most_skilled);
            } else {
                dp[cow] = max(dp[cow], dp[j-1] + (cow-j+1) * most_skilled);
            }
        }
    }
    
    cout << dp[n-1] << '\n';

    return 0;
}