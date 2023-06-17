#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAXN = 110;
const int MAXW = 1e5+17;
const ll INF = 1e18+17;

int n, w, weight[MAXN], value[MAXN];
ll dp[MAXN][MAXW]; //item, weight

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> w;
    
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= w; j++) {
            if (j - weight[i] >= 0) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - weight[i]] + value[i]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    cout << dp[n][w] << '\n';
    
    return 0;
}
