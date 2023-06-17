#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 1010;
const int MAXT = 1010;
const ll INF = 1e8+17;

int n, m, c, earn[MAX];
vector<int> adj[MAX];
ll tb[MAX][MAXT]; // nó, tempo

ll dp(int i, int tempo) {
    if (tempo >= MAXT) { // || (2LL * c * (tempo) + 1) > 1000
        if (i == 0) {
            return 0;
        }

        return -INF;
    }

    ll& ans = tb[i][tempo];

    if (ans != -1) {
        return ans;
    }
    
    if (i == 0) {
        ans = 0;
    } else {
        ans = -INF;
    }

    for (auto e : adj[i]) {
        ll add = earn[i] + 1LL * c * (tempo-1) * (tempo-1) - 1LL * c * tempo * tempo;
        ans = max(ans, add + dp(e, tempo+1));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("time.in", "r", stdin); freopen("time.out", "w", stdout);
    
    memset(tb, -1, sizeof(tb));

    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        cin >> earn[i];
    }

    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
    }

    cout << dp(0, 1) << '\n';

    return 0;
}
