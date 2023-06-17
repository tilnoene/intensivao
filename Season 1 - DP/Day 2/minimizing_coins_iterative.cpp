#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int INF = 1e9+17;
const int MAX = 1e6+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<int> coin(n);

    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    vector<int> dp(MAX, INF);
    
    dp[0] = 0; // pegando nenhuma moeda

    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i - coin[j] >= 0) {
                dp[i] = min(dp[i], dp[i - coin[j]] + 1);
            }
        }
    }

    if (dp[x] == INF) {
        cout << "-1\n";
    } else {
        cout << dp[x] << '\n';
    }

    return 0;
}
