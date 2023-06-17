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

    multiset<pair<int, int>> sequences;

    for (int i = 0; i < n; i++) {
        auto it = sequences.lower_bound({-arr[i]+1, -1e9});
        
        if (it == sequences.end() || -((*it).first) != arr[i] - 1) {
            sequences.insert({-arr[i], -1});
        } else {
            sequences.insert({-arr[i], (*it).second - 1});
            sequences.erase(it);
        }
    }
    
    int last_element = -1, mx_size = -1;

    for (auto [element, size] : sequences) {
        element *= -1;
        size *= -1;
        
        if (size > mx_size) {
            mx_size = size;
            last_element = element;
        }
    }

    // recover sequence
    vector<int> ans;

    for (int i = n-1; i >= 0; i--) {
        if (arr[i] == last_element) {
            ans.push_back(i+1);
            last_element--;
        }
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto e : ans) {
        cout << e << ' ';
    }
    cout << '\n';
    
    return 0;
}