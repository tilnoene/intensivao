#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int INF = 1e9+17;
const int MAX = 1e6+17;

int n, x, coin[110], tb[MAX];

int dp(int i) {
    if (i == 0) {
        return 0;
    }
    
    if (i < 0) {
        return INF;
    }

    int& ans = tb[i];

    if (ans != -1) {
        return ans;
    }
    
    ans = INF;

    for (int j = 0; j < n; j++) {
        ans = min(ans, dp(i - coin[j]) + 1);
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

    int ans = dp(x);

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
