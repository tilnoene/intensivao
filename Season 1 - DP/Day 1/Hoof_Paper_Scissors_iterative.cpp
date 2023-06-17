#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAXN = 1e5+17;
const int MAXK = 20+2;

int n, k, arr[MAXN], dp[MAXN][3][MAXK]; // jogo, gesto_atual, qnt trocas feitas

int win(int p, int op) { // 0 = pedra, 1 = papel, 2 = tesoura
    return ((p == 0 && op == 2) || (p == 1 && op == 0) || (p == 2 && op == 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("hps.in", "r", stdin); freopen("hps.out", "w", stdout);
    
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        char gesto; cin >> gesto;

        if (gesto == 'H') {
            arr[i] = 0;
        } else if (gesto == 'P') {
            arr[i] = 1;
        } else {
            arr[i] = 2;
        }
    }

    for (int gesto = 0; gesto < 3; gesto++) {
        for (int trocas = 0; trocas < k; trocas++) {
            dp[n][gesto][trocas] = 0; // ganhou 0 vezes
        }
    }

    for (int i = n-1; i >= 0; i--) {
        for (int trocas = 0; trocas <= k; trocas++) {
            for (int gesto = 0; gesto < 3; gesto++) {
                int ntroca = dp[i+1][gesto][trocas];
                int troca = -1e9+7;

                if (trocas + 1 <= k) {
                    for (int it = 0; it < 3; it++) {
                        troca = max(troca, dp[i+1][it][trocas+1]);
                    }
                }

                dp[i][gesto][trocas] = max(troca, ntroca) + win(gesto, arr[i]);
            }
        }
    }
    
    cout << max({
        dp[0][0][0],
        dp[0][1][0],
        dp[0][2][0],
    }) << '\n';

    return 0;
}
