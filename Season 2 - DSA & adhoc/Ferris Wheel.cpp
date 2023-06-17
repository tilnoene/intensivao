#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<int> children(n);

    for (int i = 0; i < n; i++) {
        cin >> children[i];
    }

    sort(children.rbegin(), children.rend());

    int ans = 0;

    multiset<int> gondolas;
    
    for (int i = 0; i < n; i++) {
        auto it = gondolas.lower_bound(-(x - children[i]));

        if (it == gondolas.end()) {
            gondolas.insert(-children[i]);
            ans++;
        } else {
            gondolas.erase(it);
        }
    }

    cout << ans << '\n';

    return 0;
}