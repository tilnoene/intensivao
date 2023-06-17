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

    multiset<int> towers;
    
    for (int i = 0; i < n; i++) {
        auto it = towers.upper_bound(arr[i]);

        if (it == towers.end()) {
            towers.insert(arr[i]);
        } else {
            towers.insert(arr[i]);
            towers.erase(it);
        }
    }
    
    cout << towers.size() << '\n';
    
    return 0;
}