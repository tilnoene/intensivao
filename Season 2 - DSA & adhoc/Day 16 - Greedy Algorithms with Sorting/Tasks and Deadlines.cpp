#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int, int>> arr(n);

    for (int i = 0; i < n; i++) {
    	cin >> arr[i].first >> arr[i].second;
    }

    sort(arr.begin(), arr.end());

    long long ans = 0, curr_time = 0;

    for (int i = 0; i < n; i++) {
        curr_time += arr[i].first;
    	ans += arr[i].second - curr_time;
    }

    cout << ans << '\n';

    return 0;
}