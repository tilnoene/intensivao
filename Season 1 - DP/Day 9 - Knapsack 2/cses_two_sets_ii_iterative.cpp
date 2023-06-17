#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 510;
const int MAX_SUM = MAX*MAX+17;
const int MOD = 1e9+7;

int dp(int i, int sum) {
    if (i == n) {
        int sum2 = (n * (n+1)) / 2 - sum;

        if (sum2 == sum) return 1;
        else return 0;
    }

    int& mem = tb[i][sum];
    if (mem != -1) return mem;

    mem = (dp(i+1, sum) + dp(i+1, sum+i)) % MOD;

    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int tb[MAX][MAX_SUM];
    
    for (int number = 1; number <= n; number++) {
        for (int sum = MAX_SUM-1; sum >= 0; sum--) {
            // formas de obter a soma
            tb[number][sum + number] += tb[number][sum];
        }
    }
    
    int total = (n * (n+1)) / 2;
    
    for (int sum = MAX_SUM-1; sum >= 0; sum--) {
        int sum2 = total - sum;

        if (sum == sum2) ans += tb[n][sum];
    }

    return 0;
}