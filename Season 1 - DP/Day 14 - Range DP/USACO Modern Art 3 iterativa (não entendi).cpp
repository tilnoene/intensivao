#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 305;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, painting[MAX]; cin >> n;
    int dp[MAX][MAX]; // dp[a][b] é o mínimo de pinceladas para cobrir o range [a, b]
    
    for (int i = 1; i <= n; i++) { cin >> painting[i]; }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) dp[i][j] = 1; // intervalo de tamanho 1 precisa de uma pincelada no mínimo
            else dp[i][j] = MAX; // inf
        }
        
        if (i != n) dp[i][i+1] = 1 + (painting[i] != painting[i+1]);
    }

    for (int gap = 2; gap < n; gap++) {
        for (int left = 1; left + gap <= n; left++) {
            dp[left][left + gap] = dp[left + 1][left + gap - 1];
            
            if (painting[left] == painting[left + gap]) {
                dp[left][left + gap] += 1;
            } else {
                dp[left][left + gap] += 2;
            }
            
            for (int right = left + 1; right < n; right++) {
                dp[left][left + gap] = min(
                    dp[left][left + gap],
                    dp[left][right] + dp[left][left + gap] - 1
                );
            }
        }
    }

    cout << dp[1][n] << '\n'; // resposta no range [1, n]

    return 0;
}