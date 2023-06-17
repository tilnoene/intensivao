#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 1010;
const ll INF = 1e18+17;

int n, m;
ll tb[MAX][MAX][2];
pii h[MAX], g[MAX], p[MAX][MAX];

ll dist(pii a, pii b) {
    ll x = (a.first - b.first);
    ll y = (a.second - b.second);

    return (x * x) + (y * y);
}

ll dp(int i, int j, int vez) {
    if (i == n && j == m) {
        if (vez == 0) {
            return 0;
        } else {
            return INF;
        }
    }

    ll& ans = tb[i][j][vez];

    if (ans != -1) {
        return ans;
    }

    pii curr = (vez ? g[j] : h[i]);

    ans = INF;
    
    if (i + 1 <= n) {
        ans = min(ans, dp(i+1, j, 0) + dist(curr, h[i+1]));
    }
    
    if (j + 1 <= m) {
        ans = min(ans, dp(i, j+1, 1) + dist(curr, g[j+1]));
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    
    memset(tb, -1, sizeof(tb));
    memset(p, -1, sizeof(p));

    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        cin >> h[i].first >> h[i].second;
    }

    for (int i = 1; i <= m; i++) {
        cin >> g[i].first >> g[i].second;
    }
    
    cout << dp(1, 0, 0) << '\n';

    return 0;
}