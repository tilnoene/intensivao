#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int n;
vector<int> arr;
vector<vector<vector<int>>> tb;

int dp(int i, int vez, int quantos) { // posicao que eu tô, vez de quem, quantos eu matei
    if (i >= n) {
        return 0;
    }
    
    int& ans = tb[i][vez][quantos];
    
    if (ans != -1) {
        return ans;
    }
    
    ans = dp(i+1, !vez, 0); // troca de pessoa
    
    if (quantos < 1) { // n troca de pessoa
        ans = min(ans, dp(i+1, vez, quantos+1));
    }
    
    ans += (vez == 1 && arr[i] == 1);
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        cin >> n;
        arr.resize(n);
        tb.assign(n, vector<vector<int>>(2, vector<int>(2, -1)));

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        cout << dp(0, 1, 0) << '\n';
    }

    return 0;
}
