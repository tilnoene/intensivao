#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n), b(n), pos(n+1);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
        
        pos[b[i]] = i;
    }
    
    vector<int> dp;
    
    for (int i = 0; i < n; i++) {
        int it = lower_bound(dp.begin(), dp.end(), a[i], [&](int a, int b) { return pos[a] < pos[b]; }) - dp.begin();
        
        if (it == dp.size()) {
            dp.push_back(a[i]);
        } else {
            dp[it] = a[i];
        }
    }
    
    cout << dp.size() << '\n';

    return 0;
}