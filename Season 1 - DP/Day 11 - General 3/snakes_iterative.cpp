#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    int n, k; cin >> n >> k;
    vector<int> snakes(n + 1);
    int space_used = 0;

    for (int i = 1; i <= n; i++) {
        cin >> snakes[i];
        space_used += snakes[i];
    }
    
    vector<vector<int>> dp(n + 1, vector<int>(k+1, 0)); // dp[i][j] = minimum sum of all net sikes for the first i snakes after j resizings
    int largest_group = 0;
    
    for (int group = 1; group <= n; group++) {
        largest_group = max(largest_group, snakes[group]);

        dp[group][0] = largest_group * group; // caso base: com zero resizings, ela vai pegar todo o intervalo com uma net do tamanho do maior greupo

        for (int resizing = 1; resizing <= k; resizing++) {
            dp[group][resizing] = INT32_MAX;
            int net_size = snakes[group];

            /*
                tenta melhorar a resposta do meu grupo terminando em "group" começando em algum outro
                grupo após "c" trocando para uma net do tamanho que consiga capturar todos os grupos
                (uma net do tamanho do maior grupo garante isso).
            */

            for (int c = group-1; c >= 0; c--) {
                dp[group][resizing] = min(dp[group][resizing], dp[c][resizing-1] + net_size * (group - c));

                net_size = max(net_size, snakes[c]);
            }
        }
    }

    cout << dp[n][k] - space_used << '\n';

    return 0;
}