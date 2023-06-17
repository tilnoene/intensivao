#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 1010;
const int MAXT = 1010;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("time.in", "r", stdin); freopen("time.out", "w", stdout);

    int n, m, c, earn[MAX];
    vector<int> adj[MAX];
    int dp[MAX][MAXT]; // nó, tempo

    memset(dp, -1, sizeof(dp));

    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        cin >> earn[i];
    }

    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
    }

    int ans = 0;
    
    dp[0][0] = 0;

    for (int tempo = 0; tempo < MAXT-1; tempo++) {
        for (int node = 0; node < n; node++) {
            if (dp[tempo][node] != -1) {
                for (auto e : adj[node]) {
                    dp[tempo+1][e] = max(dp[tempo+1][e], dp[tempo][node] + earn[node]);
                }
            }
        }
        
        ans = max(ans, dp[tempo][0] - c * tempo * tempo);
    }

    cout << ans << '\n';

    return 0;
}
