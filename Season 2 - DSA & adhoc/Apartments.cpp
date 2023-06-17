#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;
    vector<int> person(n);
    for (int i = 0; i < n; i++) {
        cin >> person[i];
    }

    multiset<int> apartments;
    for(int i = 0, size; i < m; i++) {
        cin >> size;
        apartments.insert(size);
    }

    sort(person.begin(), person.end());

    int ans = 0;

    for (auto p : person) {
        auto it = apartments.lower_bound(p - k);

        if (it != apartments.end() && (*it) <= p + k) {
            apartments.erase(it);
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}