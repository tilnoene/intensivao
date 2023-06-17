#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    vector<int> ans(n);
    
    stack<pair<int, int>> st;
    
    for (int i = 0; i < n; i++) {
        while (st.size() && st.top().first >= arr[i]) {
            st.pop();
        }
        
        if (st.empty()) {
            ans[i] = 0;
        } else {
            ans[i] = st.top().second;
        }
        
        st.push({arr[i], i + 1});
    }
    
    for (auto e : ans) {
        cout << e << ' ';
    }
    cout << '\n';

    return 0;
}