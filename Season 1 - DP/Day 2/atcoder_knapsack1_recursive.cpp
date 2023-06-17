#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAXN = 110;
const int MAXW = 1e5+17;
const ll INF = 1e18+17;

int n, w, weight[MAXN], value[MAXN];
ll tb[MAXN][MAXW]; // item, weight

ll dp(int i, int peso) {
    if (i >= n) return 0;
    if (peso >= w) return 0;

    ll& ans = tb[i][peso];
    
    if (ans != -1) {
        return ans;
    }

    ll npega = dp(i+1, peso);
    ll pega = -INF;

    if (peso + weight[i] <= w) {
        pega = dp(i+1, peso + weight[i]) + value[i];
    }

    return ans = max(pega, npega);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));
    
    cin >> n >> w;
    
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }
    
    cout << dp(0, 0) << '\n';
    
    return 0;
}
