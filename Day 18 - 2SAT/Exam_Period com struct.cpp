#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

struct sat {
    int n, tot;
    vector<vector<int>> adj, adjt; // grafo original, grafo transposto
    vector<int> vis, comp, ans;
    stack<int> topo; // ordem topológica

    sat() {}
    sat(int n_) : n(n_), tot(n), adj(2*n), adjt(2*n) {}

    void dfs(int x) {
        vis[x] = true;

        for (auto e : adj[x]) {
            if (!vis[e]) dfs(e);
        }

        topo.push(x);
    }

    void dfst(int x, int& id) {
        vis[x] = true;
        comp[x] = id;

        for (auto e : adjt[x]) {
            if (!vis[e]) dfst(e, id);
        }
    }

    void add_impl(int a, int b) { // a -> b = (!a or b)
        a = (a >= 0 ? 2*a : -2*a-1);
        b = (b >= 0 ? 2*b : -2*b-1);

        adj[a].push_back(b);
        adj[b^1].push_back(a^1);

        adjt[b].push_back(a);
        adjt[a^1].push_back(b^1);
    }

    void add_or(int a, int b) { // a or b
        add_impl(~a, b);
    }

    void add_and(int a, int b) { // a and b
        add_or(a, b), add_or(~a, b), add_or(a, ~b);
    }

    void add_xor(int a, int b) { // a xor b = (a != b)
        add_or(a, b), add_or(~a, ~b);
    }

    void add_eq(int a, int b) { // a = b
        add_xor(~a, b);
    }

    void add_true(int a) { // a = T
        add_impl(~a, a);
    }

    void add_false(int a) { // a = F
        add_impl(a, ~a);
    }

    // magia - brunomaletta
    void at_most_one(vector<int> v) { // no max um verdadeiro
        adj.resize(2*(tot+v.size()));
        for (int i = 0; i < v.size(); i++) {
            add_impl(tot+i, ~v[i]);
            if (i) {
                add_impl(tot+i, tot+i-1);
                add_impl(v[i], tot+i-1);
            }
        }
        tot += v.size();
    }

    pair<bool, vector<int>> solve() {
        ans.assign(n, -1);
        comp.assign(2*tot, -1);
        vis.assign(2*tot, 0);
        int id = 1;

        for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i);
        
        vis.assign(2*tot, 0);
        while (topo.size()) {
            auto x = topo.top();
            topo.pop();

            if (!vis[x]) {
                dfst(x, id);
                id++;
            }
        }

        for (int i = 0; i < tot; i++) {
            if (comp[2*i] == comp[2*i+1]) return {false, {}};
            ans[i] = (comp[2*i] > comp[2*i+1]);
        }

        return {true, ans};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    sat st(n);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        string sinal;

        cin >> a >> b >> sinal >> c;
        
        sinal += to_string(c);

        if (sinal == "<1" || sinal == "=0" || sinal == "<=0") {
            st.add_and(~a, ~b);
        } else if (sinal == "=1") {
            st.add_xor(a, b);
        } else if (sinal == ">1" || sinal == "=2" || sinal == ">=2") {
            st.add_and(a, b);
        } else if (sinal == "<2" || sinal == "<=1" || sinal == "!=2") {
            st.add_or(~a, ~b);
        } else if (sinal == ">0" || sinal == ">=1" || sinal == "!=0") {
            st.add_or(a, b);
        } else if (sinal == "!=1") {
            st.add_xor(~a, b);
        } else if (sinal == "<0" || sinal == ">2") {
            cout << "No\n";
            return 0;
        }
    }

    auto [ans, arr] = st.solve();
    
    cout << (ans ? "Yes" : "No") << '\n';

    return 0;
}