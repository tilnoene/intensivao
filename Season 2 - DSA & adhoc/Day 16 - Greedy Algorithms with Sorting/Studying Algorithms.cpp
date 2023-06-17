#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    int cnt = 0;
    
    for (int i = 0; i < n; i++) {
        if (x - arr[i] >= 0) {
            x -= arr[i];
            cnt++;
        }
    }

    cout << cnt << '\n';

    return 0;
}