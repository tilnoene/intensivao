#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 20;
const int MOD = 1e9+7;

int n, m;
int adj[MAX][MAX];
int dp[MAX][(1 << MAX)];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u][v]++;
    }

    dp[0][(1 << 0)] = 1;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask % 2 == 0) continue;
        
        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) { // estou no nó u dessa máscara
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    
                    for (int k = 0; k < adj[u][v]; k++) { // pode ter mais de uma aresta entre dois nós ;-;
                        dp[v][mask | (1 << v)] = (dp[v][mask | (1 << v)] + dp[u][mask]) % MOD;
                    }
                }
            }
        }
    }

    cout << dp[n-1][(1 << n)-1] << '\n';

    return 0;
}