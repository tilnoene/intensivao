#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        vector<int> dp(n), sizes(n);
        
        dp[0] = arr[0];
        sizes[0] = 1;

        for (int i = 1; i < n; i++) {
            if (dp[i-1] + arr[i] > arr[i]) {
                dp[i] = dp[i-1] + arr[i];
                sizes[i] = sizes[i-1];
            } else if (dp[i-1] + arr[i] < arr[i]) {
                dp[i] = arr[i];
                sizes[i] = 1;
            } else {
                dp[i] = arr[i];
                sizes[i] = sizes[i-1] + 1;
            }
        }
        
        int mx = *max_element(dp.begin(), dp.end()), times = 0;
        
        for (int i = 0; i < n; i++) {
            if (dp[i] == mx) {
                times += sizes[i];
            }
        }

        cout << mx << ' ' << times << '\n';
    }
    
    return 0;
}