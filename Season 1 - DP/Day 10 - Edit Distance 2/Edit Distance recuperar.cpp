#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 5010;

string a, b;
int tb[MAX][MAX];
tuple<int, int, string> p[MAX][MAX];

int dp(int i, int j) {
    if (i == a.size()) return b.size()-j;
    if (j == b.size()) return a.size()-i;
    
    int& mem = tb[i][j];
    if (tb[i][j] != -1) return mem;
    
    vector<int> pos = {
        dp(i+1, j) + 1,
        dp(i, j+1) + 1,
        dp(i+1, j+1) + (a[i] != b[j])
    };

    int mn = *min_element(pos.begin(), pos.end());

    if (pos[0] == mn) p[i][j] = {i+1, j, "-"};
    if (pos[1] == mn) p[i][j] = {i, j+1, "+"};
    if (pos[2] == mn) p[i][j] = {i+1, j+1, "m"};

    return mem = mn;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(tb, -1, sizeof(tb));
    
    cin >> a >> b;

    cout << dp(0, 0) << '\n';
    
    string op = "";

    auto prev = p[0][0];
    for (int i = 0; i < 2; i++) {
        auto [it, jt, ss] = prev;
        cout << it << ' ' << jt << ' '<< ss << '\n';
        prev = p[it][jt];
    }

    reverse(op.begin(), op.end());

    cout << op << '\n';

    return 0;
}