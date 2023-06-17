#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 310;

int n, painting[MAX], dp[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> painting[i];

    // dp[i][j] = min strokes to copy [a, b]

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) dp[i][j] = 1; // pra intervalos de tamanho 1 o caso base é 1 stroke
            else dp[i][j] = MAX; // inf
        }
        // TODO: tem um if aqui
        if (i != n) dp[i][i+1] = 1 + (painting[i] != painting[i+1]);
    }

    for (int size = 2; size < n; size++) {
        for (int left = 1; left + size <= n; left++) {
            // TODO: pq left+1?
            dp[left][left + size] = dp[left + 1][left + size - 1] + (painting[left] == painting[left + size] ? 1 : 2);

            for (int right = left + 1; right < n; right++) {
                dp[left][left + size] = min({
                    dp[left][left + size],
                    dp[left][right] + dp[right][left+size] - 1, // WTF?
                });
            }
        }
    }
    
    cout << dp[1][n] << '\n';

    return 0;
}