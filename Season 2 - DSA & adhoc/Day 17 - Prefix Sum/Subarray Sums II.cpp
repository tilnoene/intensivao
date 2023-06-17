#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<ll, ll> cnt; // quantas a cada prefix sum apareceu
    cnt[0] = 1;
    
    ll n, x; cin >> n >> x;
    ll ps = 0, ans = 0;
    
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        ps += v;
        
        ans += cnt[ps - x];
        
        cnt[ps]++;
    }
    
    cout << ans << '\n';
    
    return 0;
}