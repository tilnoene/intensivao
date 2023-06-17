#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 1010;
const int MOD = 1e9+7;

int n, tb[MAX][MAX];
char grid[MAX][MAX];

int dp(int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }

    if (grid[i][j] == '*') {
        return 0;
    }

    if (i == 0 && j == 0) {
        return 1;
    }

    int& ans = tb[i][j];

    if (ans != -1) {
        return ans;
    }

    return ans = (dp(i-1, j) + dp(i, j-1)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));

    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cout << dp(n-1, n-1) << '\n';

    return 0;
}
