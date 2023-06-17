#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, t; cin >> n >> t;
    vector<pair<ll, ll>> arr(n); // {initial_position, final_position}
    
    for (int i = 0; i < n; i++) {
        ll initial_position, speed; cin >> initial_position >> speed;

        // posição em que a vaca vai estar no tempo T
        ll final_position = initial_position + speed * t;
        
        arr[i] = {initial_position, final_position};
    }
    
    sort(arr.begin(), arr.end());
    
    for (auto [ff, ss] : arr) {
        cout << ff << ' ' << ss << '\n';
    }
    cout << '\n';
    
    vector<pair<int, int>> dp;
    
    for (int i = 0; i < n; i++) {
        int it = lower_bound(dp.begin(), dp.end(), arr[i], [](pii a, pii b) { return (a.first >= b.first && a.second >= b.second); }) - dp.begin();
        
        if (it == dp.size()) {
            dp.push_back(arr[i]);
        } else {
            dp[it] = arr[i];
        }
    }
    
    for (auto [ff, ss] : dp) {
        cout << ff << ' ' << ss << '\n';
    }
    
    cout << dp.size() << '\n';
    
    return 0;
}