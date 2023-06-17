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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    Dinic dinic(n+7);
    
    for (int i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        dinic.add_edge(u, v, w);
    }
    
    cout << dinic.solve(1, n) << '\n';
    
    return 0;
}