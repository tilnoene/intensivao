#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 20;
const int MOD = 1e9+7;

int n, m;
vector<int> adj[MAX];
int dp[MAX][(1 << MAX)];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
    }

    dp[0][(1 << 0)] = 1;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask % 2 == 0) continue;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                // estou no nó i dessa máscara

                for (int u : adj[i]) {
                    if (mask & (1 << u)) continue;

                    dp[u][mask | (1 << u)] = (dp[u][mask | (1 << u)] + dp[i][mask]) % MOD;
                }
            }
        }
    }

    cout << dp[n-1][(1 << n)-1] << '\n';

    return 0;
}