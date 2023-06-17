#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int INF = 1e9+17;

const int MAXN = 1010;
const int MAXW = 1e5+17;

int n, x;
int price[MAXN], pages[MAXN];
int tb[MAXN][MAXW];

int dp(int item, int peso) {
    if (peso > x) {
        return -INF;
    }
    
    if (item >= n) {
        return 0;
    }
    
    int& ans = tb[item][peso];
    
    if (ans != -1) {
        return ans;
    }
    
    int npega = dp(item+1, peso);
    int pega = 0;
    
    if (peso + price[item] <= x) {
        pega = dp(item+1, peso + price[item]) + pages[item];
    }
    
    return ans = max(pega, npega);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));
    
    cin >> n >> x;
    
    for (int i = 0; i < n; i++) { cin >> price[i]; }

    for (int i = 0; i < n; i++) { cin >> pages[i]; }
    
    cout << dp(0, 0) << '\n';

    return 0;
}