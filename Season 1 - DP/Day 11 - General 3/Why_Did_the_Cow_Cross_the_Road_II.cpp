#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 1010;

int n, tb[MAX][MAX], cows[MAX], fields[MAX];

int dp(int cow, int field) {
    if (cow >= n || field >= n) return 0;

    int& mem = tb[cow][field];
    if (mem != -1) return mem;

    mem = max(dp(cow+1, field), dp(cow, field+1));

    if (abs(cows[cow] - fields[field]) <= 4) {
        mem = max(mem, dp(cow+1, field+1) + 1);
    }

    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    
    memset(tb, -1, sizeof(tb));

    cin >> n;
    for (int i = 0; i < n; i++) { cin >> cows[i]; }
    for (int i = 0; i < n; i++) { cin >> fields[i]; }
    
    cout << dp(0, 0) << '\n';

    return 0;
}