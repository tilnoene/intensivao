#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int INF = 1e9+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> arr(n);
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(2)));

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        dp[n][0][0] = 0;
        dp[n][0][1] = 0;
        dp[n][1][0] = 0;
        dp[n][1][1] = 0;

        for (int i = n-1; i >= 0; i--) {
            for (int player = 0; player < 2; player++) {
                for (int quantos = 0; quantos < 2; quantos++) {
                    int troca = dp[i+1][!player][0];
                    int ntroca = INF;

                    if (quantos == 0) {
                        ntroca = dp[i+1][player][quantos+1];
                    }

                    dp[i][player][quantos] = min(troca, ntroca) + (player == 1 && arr[i] == 1);
                }
            }
        }

        cout << dp[0][1][0] << '\n';
    }

    return 0;
}
