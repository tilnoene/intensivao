#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int, int>> arr(n);

    for (int i = 0; i < n; i++) {
    	cin >> arr[i].second >> arr[i].first;
    }

    sort(arr.begin(), arr.end());

    int ans = 1, last_ending = arr[0].first;

    for (int i = 1; i < n; i++) {
    	if (arr[i].second >= last_ending) {
    		ans++;
    		last_ending = arr[i].first;
    	}
    }

    cout << ans << '\n';

    return 0;
}