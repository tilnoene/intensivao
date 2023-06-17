#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 1e5+17;

int n, m, dp[MAX];
vector<int> adj[MAX];
bool used[MAX];

void dfs(int x) {
    used[x] = true;
    
    for (auto e : adj[x]) {
        if (!used[e]) dfs(e);
        
        dp[x] = max(dp[x], dp[e] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        
        adj[u].push_back(v);
    }

    for (int node = 1; node <= n; node++) {
        if (!used[node]) {
            dfs(node);
        }
    }
    
    cout << *max_element(dp, dp+MAX) << '\n';

    return 0;
}