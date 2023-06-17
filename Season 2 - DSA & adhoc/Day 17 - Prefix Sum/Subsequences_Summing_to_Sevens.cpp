#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    vector<int> pos(8, -1);

    int n; cin >> n;
    ll ps = 0;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ps = (ps + x) % 7;

        if (ps == 0) ans = max(ans, i+1);

        if (pos[ps] == -1) {
            pos[ps] = i;
        } else {
            ans = max(ans, i - pos[ps]);
        }
    }

    cout << ans << '\n';
    
    return 0;
}