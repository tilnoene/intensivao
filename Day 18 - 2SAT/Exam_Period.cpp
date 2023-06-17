#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAX = 2e5+17; // 2x arestas, onde ~a = a+m

int n, m;
vector<int> adj[MAX], adjt[MAX]; // grafo original, gravo transposto
vector<int> topological;
bool used[MAX], usedt[MAX];
int component[MAX];

void dfs(int x) {
    used[x] = true;

    for (auto e : adj[x]) {
        if (!used[e]) {
            dfs(e);
        }
    }

    topological.push_back(x);
}

void dfst(int x, int comp) {
    usedt[x] = true;
    component[x] = comp;

    for (auto e : adjt[x]) {
        if (!usedt[e]) {
            dfst(e, comp);
        }
    }
}

int inv(int x) {
    if (x >= n) return x - n;
    else return x + n;
}

void add_impl(int a, int b) {
    adj[inv(a)].push_back(b);
    adj[inv(b)].push_back(a);

    adjt[b].push_back(inv(a));
    adjt[a].push_back(inv(b));
}

void add_or(int a, int b) {
    // a v b <-> (!a => b) v (!b => a)
    add_impl(a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        string sinal;

        cin >> a >> b >> sinal >> c;
        
        sinal += to_string(c);

        if (sinal == "<1" || sinal == "=0" || sinal == "<=0") {
            // (!a or !b) and (a or !b) and (!a or b)
            add_or(inv(a), inv(b));
            add_or(a, inv(b));
            add_or(inv(a), b);
        } else if (sinal == "=1") {
            // (a or b) and (!a or !b)
            add_or(a, b);
            add_or(inv(a), inv(b));
        } else if (sinal == ">1" || sinal == "=2" || sinal == ">=2") {
            // (a or b) and (!a or b) and (!b or a)
            add_or(a, b);
            add_or(inv(a), b);
            add_or(a, inv(b));
        } else if (sinal == "<2" || sinal == "<=1" || sinal == "!=2") {
            // (!a or !b)
            add_or(inv(a), inv(b));
        } else if (sinal == ">0" || sinal == ">=1" || sinal == "!=0") {
            // (a or b)
            add_or(a, b);
        } else if (sinal == "!=1") {
            // (!a or b) and (a or !b)
            add_or(inv(a), b);
            add_or(a, inv(b));
        } else if (sinal == "<0" || sinal == ">2") {
            cout << "No\n";
            return 0;
        } else {
            // pode ignorar?
        }
    }
    
    for (int i = 0; i <= n; i++) {
        if (!used[i]) dfs(i);
        if (!used[inv(i)]) dfs(inv(i));
    }
    
    int curr = 1;
    for (int i = topological.size()-1; i >= 0; i--) {
        if (!usedt[topological[i]]) {
            dfst(topological[i], curr);
            curr++;
        }
    }

    bool ans = true;
    
    for (int i = 0; i <= n; i++) {
        if (component[i] == component[inv(i)]) {
            ans = false;
        }
    }
    
    cout << (ans ? "Yes" : "No") << '\n';

    return 0;
}