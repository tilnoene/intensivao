#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 110;
const int MAX_VAL = 1e5+17;

int n, coins[MAX], tb[MAX][MAX_VAL];

int dp(int item, int peso) {
    if (item >= n) return false;
    if (peso == coins[item]) return true;

    int& ans = tb[item][peso];

    if (ans != -1) return ans;

    return ans = dp(item + 1, peso) | dp(item+1, peso + coins[item]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    memset(tb, -1, sizeof(tb));
    dp(0, 0);

    vector<int> ans;
    
    for (int i = 1; i < MAX_VAL; i++) {
        bool possible = false;
        
        for (int j = 0; j < n; j++) {
            possible |= (tb[j][i] == 1);
        }
        
        if (possible) {
            ans.push_back(i);
        }
    }
    
    cout << ans.size() << '\n';
    for (auto e : ans) {
        cout << e << ' ';
    }
    
    return 0;
}