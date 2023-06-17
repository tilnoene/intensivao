#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    map<char, int> conv;
    conv['H'] = 0;
    conv['P'] = 1;
    conv['S'] = 2;

    auto win = [&](int move) -> int {
        if (move == 0) return 2;
        if (move == 1) return 0;
        if (move == 2) return 1;
        return 0;
    };

    int n; cin >> n;
    vector<vector<int>> ps(n+1, vector<int>(3, 0));

    for (int i = 1; i <= n; i++) {
        char c; cin >> c;

        for (int j = 0; j < 3; j++)
            ps[i][j] = ps[i-1][j];

        ps[i][conv[c]]++;
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        // play j on first i moves and then play k on last n-i moves

        int left = 0, right = 0;
        for (int j = 0; j < 3; j++) {
            left = max(left, ps[i][win(j)]);
            right = max(right, ps[n][win(j)] - ps[i][win(j)]);
        }

        ans = max(ans, left + right);
    }

    cout << ans << '\n';
    
    return 0;
}