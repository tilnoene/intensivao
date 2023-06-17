#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX_DIGITS = 20;
 
int n, m, k, d;
int dp[MAX_DIGITS][MAX_DIGITS][2]; // digito atual, quantas vezes o dígito d apareceu, eh maior

// [0, x]
int dfs(int x, int i = 0, int cnt = 0, int is_greater = 0) {
    if (i >= to_string(x).size()) return (cnt == k);
    int& ans = dp[i][cnt][is_greater];
    if (ans != -1) return ans;
    
    ans = (to_string(x)[i] == d);

    int limit = 9;
    if (!is_greater) limit = to_string(x)[i] - '0';

    // for (int digit = (i == 0 && d == 0); digit <= limit; digit++) {
    for (int digit = 0; digit <= limit; digit++) {
        if (is_greater) {
            ans += dfs(x, i+1, cnt + (digit == d), 1);
        } else {
            ans += dfs(x, i+1, cnt + (digit == d), digit < (to_string(x)[i] - '0'));
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Find the number of integers between n and m inclusive containing exactly k d digits
    cin >> n >> m >> k >> d;
    
    memset(dp, -1, sizeof(dp));
    int total = dfs(m);
    memset(dp, -1, sizeof(dp));

    cout << total - dfs(n - 1) << '\n';
    
    return 0;
}