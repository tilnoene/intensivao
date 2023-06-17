#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 20;
const int MOD = 1e9+7;

int n, m;
vector<int> adj[MAX];
int tb[MAX][(1 << MAX)];

int solve(int x, int visited) {
    int& ans = tb[x][visited];

    if (ans != -1) return ans;

    if (visited == (1 << n)-1) {
        return (x == n-1);
    }

    ans = 0;

    for (auto e : adj[x]) {
        if (visited & (1 << e)) continue;
        
        ans = (ans + solve(e, visited | (1 << e))) % MOD;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
    }

    memset(tb, -1, sizeof(tb));
    
    cout << solve(0, 0b1) << '\n';

    return 0;
}