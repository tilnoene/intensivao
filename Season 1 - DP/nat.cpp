#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ff first
#define ss second

using namespace std;

const int MAX = 307;
const int INF = 1e9+17;

// estados - atual e quais doces
// na dp - mínimo de passos

// curr
// 0 - start
// 1 a n - candies
// n + 1 - goal

int h, w, t; 
char grid[MAX][MAX];
int dp[21][1 << 21];
int qnt = 0;
vector<pii> all;
int dist[21][21];

int bfs(int curr, int next) {
    auto [curr_i, curr_j] = all[curr];
    auto [next_i, next_j] = all[next];
    
    queue<pii> q;
    q.push(mp(curr_i, curr_j));
    
    map<pii, bool> visited;
    map<pii, int> d;
    visited[mp(curr_i, curr_j)] = true;
    
    while (!q.empty()) {
        auto[i, j] = q.front();
        q.pop();
        
        if (i == next_i && j == next_j) return d[mp(next_i, next_j)];
        
        vector<pair<int, int>> go = {
            {i + 1, j},
            {i - 1, j},
            {i, j + 1},
            {i, j - 1}
        };
        for (auto [it, jt] : go) {
            if (grid[it][jt] != '#' && !visited[mp(it, jt)]) {
                q.push(mp(it, jt));
                visited[mp(it, jt)] = true;
                d[mp(it, jt)] = d[mp(i, j)] + 1;
            }
        }
    }
    
    return INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> h >> w >> t;
    
    for (int i = 0; i <= h + 1; i++) {
        for (int j = 0; j <= w + 1; j++) {
            grid[i][j] = '#';
        }
    }
    
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                all.pb(mp(i, j));
                qnt++;
            }
        }
    }
    
    // all = {(i, j),  (i, j)    , (i, j)}
    
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (grid[i][j] == 'o') {
                all.pb(mp(i, j));
                qnt++;
            }
        }
    }
    
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (grid[i][j] == 'G') {
                all.pb(mp(i, j));
                qnt++;
            }
        }
    }
    
    for (int i = 0; i < qnt; i++) {
        for (int j = i + 1; j < qnt; j++) {
            dist[i][j] = bfs(i, j);
            dist[j][i] = dist[i][j];
        }
    }
    
    if (dist[0][qnt - 1] >= t) {
        cout << "-1\n";
        return 0;
    }
    
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < (1 << 18); j++) {
            dp[i][j] = INF;
        }
    }
    
    dp[0][1] = 0;
    
    for (int mask = 0; mask < (1 << qnt); mask++) {
        if (!(mask & (1 << 0))) continue;
        for (int curr = 0; curr < qnt; curr++) {
            if (!(mask & (1 << curr))) continue;
            for (int next = 0; next < qnt; next++) {
                // if não peguei
                if (!(mask & (1 << next))) {
                    if (dp[curr][mask] + dist[curr][next] <= t) dp[next][mask | (1 << next)] =
                    min(dp[next][mask | (1 << next)], dp[curr][mask] + dist[curr][next]);
                }
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < (1 << qnt); i++) {
        if (dp[qnt - 1][i] <= t) ans = max(ans, __builtin_popcount(i) - 2);
    }
    
    cout << ans << '\n';

    return 0;
}