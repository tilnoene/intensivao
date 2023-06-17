#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<pair<int, int>> arr(n); // { ending, starting }
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i].second >> arr[i].first;
    }

    sort(arr.begin(), arr.end());
    
    int movies = 0;
    multiset<int> members; // quando termina cada filme de cada membro

    for (int i = 0; i < n; i++) {
        auto it = members.lower_bound(-arr[i].second);

        if (it != members.end()) {
            members.erase(it);
            members.insert(-arr[i].first);
            movies++;
        } else if (members.size() < k) {
            members.insert(-arr[i].first);
            movies++;
        }
    }

    cout << movies << '\n';

    return 0;
}