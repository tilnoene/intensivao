#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 5010;

string a, b;
int tb[MAX][MAX];

int dp(int i, int j) {
    if (i == a.size()) return b.size()-j;
    if (j == b.size()) return a.size()-i;
    
    int& mem = tb[i][j];
    if (tb[i][j] != -1) return mem;
    
    return mem = min({
       dp(i+1, j) + 1,
       dp(i, j+1) + 1,
       dp(i+1, j+1) + (a[i] != b[j])
    });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));
    
    cin >> a >> b;
    cout << dp(0, 0) << '\n';
    
    return 0;
}