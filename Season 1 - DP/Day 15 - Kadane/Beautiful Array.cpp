#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 3e5+17;

ll n, x, arr[MAX], tb[MAX][3];

ll dp(int pos, int status) {
    if (pos >= n) return 0;

    ll& mem = tb[pos][status];
    if (mem != -1) return mem;
    mem = 0;

    if (status == 0) { // não comecei a multiplicar
        mem = max({
            arr[pos], // pegar só o elemento
            arr[pos] + dp(pos+1, 0), // não começa a multiplicar
            arr[pos] * x + dp(pos+1, 1) // começa a multiplicar
        });
    } else if (status == 1) { // estou multiplicando
        mem = max({
            arr[pos] * x, // pegar só o elemento
            arr[pos] * x + dp(pos+1, 1), // continuo multiplicando
            arr[pos] + dp(pos+1, 2) // parei de multiplicar
        });
    } else { // já finalizei a multiplicacao (kadane padrão)
        mem = max({
            0LL,
            arr[pos], // pegar só o elemento
            arr[pos] + dp(pos+1, 2) // ele + próxima sequência
        });
    }

    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    memset(tb, -1, sizeof(tb));
    
    dp(0, 0); // começa sem multiplicar
    dp(0, 1); // começa multiplicando
    
    ll ans = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            ans = max(ans, tb[i][j]);
        }
    }
    
    cout << ans << '\n';
    
    return 0;
}