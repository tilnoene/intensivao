#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> dp;
    
    for (int i = 0; i < n; i++) {
        int it = lower_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
        
        if (it == dp.size()) {
            dp.push_back(arr[i]);
        } else {
            dp[it] = arr[i];
        }
    }

    cout << dp.size() << '\n';
    
    return 0;
}