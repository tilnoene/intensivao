#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MOD = 1e9+7;
const int MAX = 1e6+17;

int n, x, coin[110];
int tb[MAX];

int dp(int i) {
    if (i == 0) {
        return 1;
    }

    if (i < 0) {
        return 0;
    }

    int& ans = tb[i];

    if (ans != -1) {
        return ans;
    }

    ans = 0;

    for (int j = 0; j < n; j++) {
        ans = (ans + dp(i - coin[j])) % MOD;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));

    cin >> n >> x;
    
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }
    
    cout << dp(x) << '\n';

    return 0;
}
