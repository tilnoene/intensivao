#include <bits/stdc++.h>
 
// n acho que eu seja bom, mas eu ja fui pior
 
using namespace std;
using ll = long long;
 
const int MAX = 510;
 
struct Flow {
    int n;
    ll adj[MAX][MAX];
    bool used[MAX];
    
    Flow(int n) : n(n) {
        memset(adj, 0, sizeof(adj));
    };
    
    void add_edge(int u, int v, ll c) {
        adj[u][v] += c;
    }
    
    ll dfs(int x, int t, ll amount) {
        used[x] = true;
        
        if (x == t) return amount;
        
        for (int i = 1; i <= n; i++) {
            if (adj[x][i] > 0 && !used[i]) {
                ll sent = dfs(i, t, min(amount, adj[x][i]));
                
                if (sent > 0) {
                    adj[x][i] -= sent;
                    adj[i][x] += sent;
                    
                    return sent;
                }
            }
        }
        
        return 0;
    }
    
    ll max_flow(int s, int t) { // source and sink
        ll total = 0;
        ll sent = -1;
        
        while (sent != 0) {
            memset(used, 0, sizeof(used));
            sent = dfs(s, t, INT_MAX);
            total += sent;
        }
        
        return total;
    }
 
    vector<bool> vis;
    vector<int> curr;
 
    bool dfs2(int x, int& t) {
        vis[x] = true;
        bool arrived = false;
 
        if (x == t) {
            curr.push_back(x);
            return true;
        }
 
        for (int i = 1; i <= n; i++) {
            if (adj[i][x] > 0 && !vis[i]) {
                auto aux = dfs2(i, t);
            
                if (aux) {
                    arrived = true;
                    adj[i][x]--;
                }
            }
        }        
 
        if (arrived) {
            curr.push_back(x);
        }
 
        return arrived;
    }
 
    vector<vector<int>> get_paths(int s, int t) {
        vector<vector<int>> ans;
 
        while (true) {
            vis.assign(n, false);
            curr.clear();
        
            if (!dfs2(s, t)) break;
            
            reverse(curr.begin(), curr.end());
            ans.push_back(curr);
        }
 
        return ans;
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    Flow flow(n+7);
    
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        flow.add_edge(u, v, 1);
    }
    
    ll max_flow = flow.max_flow(1, n);
    auto paths = flow.get_paths(1, n);
 
    cout << max_flow << '\n';
    
    for (auto arr : paths) {
        cout << arr.size() << '\n';
        for (auto e : arr) cout << e << ' ';
        cout << '\n';
    }
    
    return 0;
}