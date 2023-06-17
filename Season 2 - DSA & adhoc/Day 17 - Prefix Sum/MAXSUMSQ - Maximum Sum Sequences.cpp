#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<ll> arr(n+1), dp(n+1);
    ll mx_sum = -1e18;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];

        dp[i] = max(dp[i-1] + arr[i], arr[i]);
        mx_sum = max(mx_sum, dp[i]);
    }

    map<ll, ll> cnt;
    cnt[0] = 1;
    ll ps = 0, times = 0;

    for (int i = 1; i <= n; i++) {
        ps += arr[i];
        
        times += cnt[ps - mx_sum];
        cnt[ps]++;
    }

    cout << mx_sum << ' ' << times << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}