#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 1e5+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<array<int, 3>> arr(n+1);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    ll dp[MAX][3] = {}; // item, item anterior
    
    for (int i = 1; i <= n; i++) {
        for (int item = 0; item < 3; item++) {
            for (int pega = 0; pega < 3; pega++) {
                if (pega == item) continue;

                dp[i][item] = max(dp[i][item], dp[i][pega] + arr[i][pega]);
            }
        }
    }

    cout << max({dp[n][0], dp[n][1], dp[n][2]}) << '\n';

    return 0;
}