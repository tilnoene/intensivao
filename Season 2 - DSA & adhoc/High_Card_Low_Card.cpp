#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int n; cin >> n;
    vector<int> elsie(n);
    vector<bool> used(2*n+1, false);

    for (int i = 0; i < n; i++) {
        cin >> elsie[i];
        used[elsie[i]] = true;
    }

    vector<int> elsie1, elsie2;
    for (int i = 0; i < n/2; i++) elsie1.push_back(elsie[i]);
    for (int i = n/2; i < n; i++) elsie2.push_back(elsie[i]);

    sort(elsie1.begin(), elsie1.end());
    sort(elsie2.begin(), elsie2.end());

    set<int> bessie;
    for (int i = 1; i <= 2*n; i++) {
        if (!used[i]) bessie.insert(i);
    }

    int ans = 0;

    // first rounds
    for (int i = n/2-1; i >= 0; i--) {
        auto it = bessie.lower_bound(elsie1[i]);
    
        if (it != bessie.end()) {
            bessie.erase(it);
            ans++;
        }
    }
    
    // last rounds
    for (int i = 0; i < n/2; i++) {
        auto it = bessie.upper_bound(elsie1[i]);

        if (it == bessie.begin()) continue;
        it = prev(it);

        if (it != bessie.end()) {
            bessie.erase(it);
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}