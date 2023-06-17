#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 21;
const int MOD = 1e9+7;

int n;
bool compatible[MAX][MAX];
int tb[(1 << MAX)];

int dp(int mask) { // mask = quais mulheres já deram match
    if (mask == (1 << n) - 1) return 1;
    if (tb[mask] != -1) return tb[mask];

    tb[mask] = 0;

    int man = __builtin_popcount(mask);

    for (int woman = 0; woman < n; woman++) {
        if (!(mask & (1 << woman)) && compatible[man][woman]) {
            tb[mask] += dp(mask | (1 << woman));
            tb[mask] %= MOD;
        }
    }

    return tb[mask];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> compatible[i][j];
        }
    }
    
    memset(tb, -1, sizeof(tb));

    cout << dp(0) << '\n';

    return 0;
}