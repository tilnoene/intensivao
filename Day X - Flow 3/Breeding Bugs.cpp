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

const int MAX = 2e7+17;

vector<int> is_prime(MAX, true);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i * i < MAX; i++) {
        if (is_prime[i]) {
            for (int j = i + i; j < MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int n; cin >> n;
    int orin = n;
    vector<int> arr;
    bool has_one = false;
    int source = n + 1, target = n + 2;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x == 1)  {
            if (!has_one) arr.push_back(x);
            has_one = true;
        } else {
            arr.push_back(x);
        }
    }

    n = arr.size();
    
    vector<vector<int>> adj(n + 17, vector<int>());
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (is_prime[arr[i] + arr[j]]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    
    queue<int> q;
    vector<bool> used(n);
    vector<int> color(n);
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            q.push(i);
            used[i] = true;
            color[i] = 0;
            
            while (!q.empty()) {
                auto v = q.front();
                q.pop();
                
                for (auto e : adj[v]) {
                    if (!used[e]) {
                        q.push(e);
                        color[e] = !color[v];
                        used[e] = true;
                    }
                }
            }
        }
    }

    Dinic dinic(orin + orin + 17);
    
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dinic.add_edge(source, i, 1);
            
            for (auto e : adj[i]) {
                dinic.add_edge(i, e, 1);
            }
        } else {
            dinic.add_edge(i, target, 1);
        }
    }
    
    cout << n - dinic.solve(source, target) << '\n';
    
    return 0;
}