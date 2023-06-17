#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<int> arr(x);
    multiset<ll> ms;
    
    for (int i = 0; i < x; i++) {
        cin >> arr[i];
        ms.insert(arr[i]);
    }
    
    ll ans = 0;
    
    while (ms.size() > 1) {
        ll curr1 = *(ms.begin());
        ms.erase(ms.begin());
        
        ll curr2 = *(ms.begin());
        ms.erase(ms.begin());
        
        ms.insert(curr1 + curr2);
        ans += curr1 + curr2;
    }
    
    cout << ans << '\n';

    return 0;
}