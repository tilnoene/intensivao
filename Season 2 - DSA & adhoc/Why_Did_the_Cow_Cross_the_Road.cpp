#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);

    int c, n; cin >> c >> n;
    multiset<int> chickens;
    for (int i = 0, chicken; i < c; i++) {
        cin >> chicken;
        chickens.insert(chicken);
    }

    vector<pair<int, int>> cows(n); // {end, start}
    for (int i = 0; i < n; i++) {
        cin >> cows[i].second >> cows[i].first;
    }

    sort(cows.begin(), cows.end());
    
    int ans = 0;

    for (auto [fim, ini] : cows) {
        auto it = chickens.lower_bound(ini);

        if (it != chickens.end() && (*it) <= fim) {
            chickens.erase(it);
            ans++;
        }
    }

    cout << ans << '\n';
    
    return 0;
}