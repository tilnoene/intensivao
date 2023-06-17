#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX = 1010;
const ll INF = 1e18+17;

ll tb[MAX][MAX];

struct point {
    int x, y;
};

ll dist(point a, point b) {
    ll x = (a.x - b.x);
    ll y = (a.y - b.y);

    return (x * x) + (y * y);
}

int n, m;
point psf[MAX], psb[MAX];

ll dp(int i, int j) {
    if (i == n && j == m) {
        return 0;
    }

    ll& ans = tb[i][j];

    if (ans != -1) {
        return ans;
    }

    ans = INF;

    if (i + 1 <= n) {
        ans = min(ans, dp(i+1, j) + dist(psf[i+1], psb[j]));
    }

    if (j + 1 <= m) {
        ans = min(ans, dp(i, j+1) + dist(psf[i], psb[j+1]));
    }
    
    if (i + 1 <= n && j + 1 <= m) {
        ans = min(ans, dp(i+1, j+1) + dist(psf[i+1], psb[j+1]));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
    
    memset(tb, -1, sizeof(tb));

    cin >> n >> m;
    cin >> psf[0].x >> psf[0].y;
    cin >> psb[0].x >> psb[0].y;
    
    string pathf, pathb; cin >> pathf >> pathb;
    
    for (int i = 1; i <= n; i++) {
        psf[i] = psf[i-1];

        if (pathf[i-1] == 'N') {
            psf[i].y++;
        } else if (pathf[i-1] == 'S') {
            psf[i].y--;
        } else if (pathf[i-1] == 'E') {
            psf[i].x++;
        } else { // W
            psf[i].x--;
        }
    }

    for (int i = 1; i <= m; i++) {
        psb[i] = psb[i-1];

        if (pathb[i-1] == 'N') {
            psb[i].y++;
        } else if (pathb[i-1] == 'S') {
            psb[i].y--;
        } else if (pathb[i-1] == 'E') {
            psb[i].x++;
        } else { // W
            psb[i].x--;
        }
    }

    cout << dp(0, 0) << '\n';

    return 0;
}
