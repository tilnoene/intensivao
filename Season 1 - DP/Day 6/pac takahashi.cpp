#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using pii = pair<int, int>;

const int MAX = 310;
const int INF = 2e6+17;

pii mymax(pii a, pii b) {
    if (a.first == b.first) {
        if (a.second > b.second) {
            return b;
        } else {
            return a;
        }
    }

    if (a.first > b.first) {
        return a;
    } else {
        return b;
    }
}

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
    vector<vector<int>> dist(n, vector<int>(n, 0));

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    auto bfs = [&](pii from, pii to) -> int {
        vector<vector<bool>> used(h, vector<bool>(w, false));

        queue<tuple<int, int, int>> q;
        q.push({from.first, from.second, 0});
        used[from.first][from.second] = true;

        while (!q.empty()) {
            auto [ff, ss, d] = q.front();
            q.pop();

            if (ff == to.first && ss == to.second) return d;

            for (int i = 0; i < 4; i++) {
                int it = ff + dx[i];
                int jt = ss + dy[i];

                if (it >= 0 && it < h && jt >= 0 && jt < w && !used[it][jt] && arr[it][jt] != '#') {
                    used[it][jt] = true;
                    q.push({it, jt, d + 1});
                }
            }
        }
        
        return INF;
    };
    
    if (bfs(start, goal) > t) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = bfs(candies[i], candies[j]);
        }
    }

    vector<vector<pii>> dp((1 << n), vector<pii>(n, {0, INF})); // termina com i
    int ans = 0;

    dp[1][0] = {0, 0};

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & (1 << 0))) continue; // otimização "desnecessária"
        
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j))) continue; // nem está no conjunto
            auto [mx_candies, time_spent] = dp[mask][j];
            
            for (int k = 0; k < n; k++) {
                if (mask & (1 << k)) continue;
                if (time_spent + dist[j][k] > t) continue;

                dp[(mask | (1 << k))][k] = mymax(dp[(mask | (1 << k))][k], {mx_candies + (k > 0 && k < n-1), time_spent + dist[j][k]});
            }
        }

        ans = max(ans, dp[mask][n-1].first);
    }

    cout << ans << '\n';    

    return 0;
}