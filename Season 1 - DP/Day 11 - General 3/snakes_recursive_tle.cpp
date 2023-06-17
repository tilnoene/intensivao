#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior
// ATENÇÃO: solução não passa na memória pois tem 3 estados N = 400

using namespace std;

const int MAX = 400+1;
const int INF = 1e9+17;

int n, k, arr[MAX];
unordered_map<int, int> tb[MAX][MAX]; // cobra i, k trocas, posição equivalente ao tamanho da rede

int dp(int i, int trocas, int pos_rede) {
    if (i >= n) {
        return 0;
    }

    if (arr[pos_rede] < arr[i]) {
        return INF;
    }

    int& ans = tb[i][trocas][pos_rede];

    if (ans != 0) {
        return ans;
    }

    int ntroca = dp(i+1, trocas, pos_rede);
    int troca = INF;

    if (trocas < k) {
        for (int j = 0; j < n; j++) {
            troca = min(troca, dp(i+1, trocas+1, j));
        }
    }
    
    return ans = min(troca, ntroca) + (arr[pos_rede] - arr[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    // memset(tb, -1, sizeof(tb));

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int ans = INF;

    for (int i = 0; i < n; i++) {
        ans = min(ans, dp(0, 0, i));
    }

    cout << ans << '\n';

    return 0;
}
