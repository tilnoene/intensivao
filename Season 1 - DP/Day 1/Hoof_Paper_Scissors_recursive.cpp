#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAXN = 1e5+17;
const int MAXK = 20+2;

int n, k, arr[MAXN], tb[MAXN][3][MAXK]; // jogo, gesto_atual, qnt trocas feitas

int win(int p, int op) { // 0 = pedra, 1 = papel, 2 = tesoura
    return ((p == 0 && op == 2) || (p == 1 && op == 0) || (p == 2 && op == 1));
}

int dp(int i, int gesto, int trocas) {
    if (i >= n) {
        return 0;
    }

    int& ans = tb[i][gesto][trocas];

    if (ans != -1) {
        return ans;
    }

    ans = dp(i+1, gesto, trocas);

    if (trocas < k) {
        for (int it = 0; it < 3; it++) {
            if (it != gesto) {
                ans = max(ans, dp(i+1, it, trocas+1));
            }
        }
    }
    
    return ans += win(gesto, arr[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("hps.in", "r", stdin); freopen("hps.out", "w", stdout);
    
    memset(tb, -1, sizeof(tb));
    
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
    
    cout << max({
        dp(0, 0, 0),
        dp(0, 1, 0),
        dp(0, 2, 0)
    }) << '\n';

    return 0;
}
