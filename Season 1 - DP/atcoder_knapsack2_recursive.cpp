#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAXN = 110;
const int MAXV = 1e5+17;
const ll INF = 1e18+17;

int n, w, weight[MAXN], value[MAXN];
ll tb[MAXV];

ll dp(int i) {
    if (i >= MAXV) {
        return INF;
    }

    ll npega = dp(i+1);
    ll pega = INF;

    for (int j = 0; j < n; j++) {
        pega = min(pega, dp(i + value[j]) + weight[j]);
    }

    return min(pega, npega);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // NÃO CONSEGUI FAZER
    cin >> n >> w;
    
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    vector<ll> dp(MAXV, INT_MAX);
    dp[0] = 0;

    // qual o menor peso que preciso pra carregar o valor v

    for (int i = 0; i < n; i++) {
        for (int j = MAXV-1; j >= 0; j--) {
            dp[j + value[i]] = min(dp[j + value[i]], dp[j] + weight[i]);
        }
    }

    ll ans = INT_MIN;

    for (ll i = 0; i < MAXV; i++) {
        if (dp[i] <= w) {
            ans = max(ans, i);
        }
    }

    cout << ans << '\n';
    
    return 0;
}
