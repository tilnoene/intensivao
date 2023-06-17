#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using pii = pair<int, int>;

const int MAX = 310;
const int BITS = 20;
const int INF = 2e6+17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    char arr[MAX][MAX];

    pii start, goal;
    vector<pii> candies;

    int h, w, t; cin >> h >> w >> t;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> arr[i][j];

            if (arr[i][j] == 'S') start = {i, j};
            if (arr[i][j] == 'G') goal = {i, j};
            if (arr[i][j] == 'o') candies.push_back({i, j});
        }
    }

    candies.insert(candies.begin(), start);
    candies.push_back(goal);
    
    int n = candies.size();

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    auto bfs = [&](pii from, pii to) -> int {
        int used[MAX][MAX] = {};
        int d[MAX][MAX] = {};
        
        queue<pair<int, int>> q;

        q.push({from.first, from.second});
        d[from.first][from.second] = 0;
        used[from.first][from.second] = true;

        while (!q.empty()) {
            auto [ff, ss] = q.front();
            q.pop();

            if (ff == to.first && ss == to.second) return d[to.first][to.second];

            for (int i = 0; i < 4; i++) {
                int it = ff + dx[i];
                int jt = ss + dy[i];

                if (it >= 0 && it < h && jt >= 0 && jt < w && !used[it][jt] && arr[it][jt] != '#') {
                    used[it][jt] = true;
                    d[it][jt] = d[ff][ss] + 1;
                    q.push({it, jt});
                }
            }
        }
        
        return INF;
    };
    
    if (bfs(start, goal) > t) {
        cout << "-1\n";
        return 0;
    }

    int dist[MAX][MAX] = {};

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = bfs(candies[i], candies[j]);
        }
    }

    int dp[(1 << BITS)][BITS]; // termina com i

    for (int i = 0; i < (1 << BITS); i++) {
        for (int j = 0; j < BITS; j++) {
            dp[i][j] = INF;
        }
    }

    dp[1][0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & (1 << 0))) continue; // não começou no start
        if (mask & (1 << (n-1))) continue; // já passou no goal

        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j))) continue; // nem está no conjunto
            if (dp[mask][j] > t) continue;
            
            for (int k = 0; k < n; k++) {
                if (mask & (1 << k)) continue;
                if (dp[mask][j] + dist[j][k] > t) continue;

                dp[(mask | (1 << k))][k] = min(dp[(mask | (1 << k))][k], dp[mask][j] + dist[j][k]);
            }
        }
    }
    
    int ans = 0;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask][n-1] < t) {
            ans = max(ans, __builtin_popcount(mask) - 2);
        }
    }

    cout << ans << '\n';    

    return 0;
}