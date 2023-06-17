#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const ll FLOW_INF = 1e18;

struct Edge {
    int from, to;
    ll cap, flow;
    Edge* residual; // a inversa da minha aresta

    Edge() {};

    Edge(int from, int to, ll cap) : from(from), to(to), cap(cap), flow(0) {};
    
    ll remaining_cap() {
        return cap - flow;
    }
    
    void augment(ll bottle_neck) {
        flow += bottle_neck;
        residual->flow -= bottle_neck;
    }

    bool is_residual() {
        return cap == 0;
    }
};

struct Dinic {
    int n;
    vector<vector<Edge*>> adj;
    vector<int> level, next;

    Dinic(int n): n(n) {
        adj.assign(n+1, vector<Edge*>());
        level.assign(n+1, -1);
        next.assign(n+1, 0);
    }
    
    void add_edge(int from, int to, ll cap) {
        auto e1 = new Edge(from, to, cap);
        auto e2 = new Edge(to, from, 0);

        e1->residual = e2;
        e2->residual = e1;

        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        
        q.push(s);
        level[s] = 1;
        
        while (q.size()) {
            int curr = q.front();
            q.pop();
            
            for (auto edge : adj[curr]) {
                if (edge->remaining_cap() > 0 && level[edge->to] == -1) {
                    level[edge->to] = level[curr] + 1;
                    q.push(edge->to);
                }
            }
        }
        
        return level[t] != -1;
    }
    
    ll dfs(int x, int t, ll flow) {
        if (x == t) return flow;
        
        for (int& cid = next[x]; cid < (int)adj[x].size(); cid++) {
            auto& edge = adj[x][cid];
            ll cap = edge->remaining_cap();

            if (cap > 0 && level[edge->to] == level[x] + 1) {
                ll sent = dfs(edge->to, t, min(flow, cap)); // bottle neck
                if (sent > 0) {
                    edge->augment(sent);
                    return sent;
                }
            }
        }
        
        return 0;
    }
    
    ll solve(int s, int t) {
        ll max_flow = 0;
        
        while (bfs(s, t)) {
            fill(next.begin(), next.end(), 0);
            
            while (ll sent = dfs(s, t, FLOW_INF)) {
                max_flow += sent;
            }
        }
        
        return max_flow;
    }

    vector<int> curr;
    vector<bool> vis;

    bool dfs2(int x, int& t) {
        vis[x] = true;
        bool arrived = false;

        if (x == t) {
            curr.push_back(x);
            return true;
        }

        for (auto edge : adj[x]) {
            if (edge->flow > 0 && !vis[edge->to]) {
                bool aux = dfs2(edge->to, t);

                if (aux) {
                    arrived = true;
                    edge->flow--;
                    break; // precisa?
                }
            }
        }

        if (arrived) curr.push_back(x);

        return arrived;
    }

    vector<vector<int>> get_paths(int s, int t) {
        vector<vector<int>> ans;

        while (true) {
            curr.clear();
            vis.assign(n+1, false);

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
    
    int n, m, k; cin >> n >> m >> k;
    Dinic dinic(n+m+7); // meninas com offset de n
    
    int source = n+m+1, target = n+m+2; // source and sink
    
    // liga source em todos os meninos
    for (int boy = 1; boy <= n; boy++) {
        dinic.add_edge(source, boy, 1);
    }

    // liga todas as meninas no sink (target)
    for (int girl = 1; girl <= m; girl++) {
        dinic.add_edge(girl + n, target, 1);
    }

    for (int i = 0; i < k; i++) {
        int boy, girl; cin >> boy >> girl;
        dinic.add_edge(boy, girl + n, 1);
    }
    
    int max_pairs = dinic.solve(source, target);
    auto ans = dinic.get_paths(source, target);

    cout << max_pairs << '\n';
    for (auto arr : ans) {
        cout << arr[1] << ' ' << arr[2] - n << '\n';
    }

    return 0;
}