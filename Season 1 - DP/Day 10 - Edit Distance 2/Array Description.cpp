#include <bits/stdc++.h>
 
// n acho que eu seja bom, mas eu ja fui pior
 
using namespace std;
 
const int MAX = 1e5+17;
const int MOD = 1e9+7;
 
int n, m, arr[MAX], tb[MAX][110];
 
int dp(int i, int last) {
    if (i == n) return 1;
 
    int& mem = tb[i][last];
    if (mem != -1) return mem;
 
    mem = 0;
 
    if (arr[i] != 0) {
        if (abs(last - arr[i]) <= 1) {
            mem = dp(i+1, arr[i]);
        }
    } else {
        if (i == 0) {
            for (int j = 1; j <= m; j++) {
                mem = (mem + dp(i+1, j)) % MOD;
            }
        } else {
            for (int j = max(1, last-1); j <= min(m, last+1); j++) {
                if (abs(j - last) <= 1) {
                    mem = (mem + dp(i+1, j)) % MOD;
                }
            }
        }
    }
 
    return mem;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
 
    memset(tb, -1, sizeof(tb));
 
    cout << dp(0, arr[0]) << '\n';
    
    return 0;
}