#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 1010;
const ll INF = 1e18+17;

struct point {
    int x, y;
};

ll dist(point a, point b) {
    ll x = (a.x - b.x);
    ll y = (a.y - b.y);

    return (x * x) + (y * y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    
    int h, g; cin >> h >> g;
    vector<point> hs(h+1), gs(g+1);

    for (int i = 1; i <= h; i++) { cin >> hs[i].x >> hs[i].y; }

    for (int i = 1; i <= g; i++) { cin >> gs[i].x >> gs[i].y; }

    vector<vector<vector<ll>>> dp(h+1, vector<vector<ll>>(g+1, vector<ll>(2, INF)));
    // (0: ith Holstein, 1: ith Guernsey)

    dp[1][0][0] = 0; // começando da Holstein 1
    
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= g; j++) {
            if (i > 1) {
                dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][0] + dist(hs[i], hs[i-1]));
            }

            if (j > 1) {
                dp[i][j][1] = min(dp[i][j][1], dp[i][j-1][1] + dist(gs[j], gs[j-1]));
            }

            if (i > 0 && j > 0) {
                dp[i][j][0] = min(
                    dp[i][j][0],
                    dp[i-1][j][1] + dist(hs[i], gs[j])
                );

                dp[i][j][1] = min(
                    dp[i][j][1],
                    dp[i][j-1][0] + dist(hs[i], gs[j])
                );
            }
        }
    }

    cout << dp[h][g][0] << '\n';

    return 0;
}
