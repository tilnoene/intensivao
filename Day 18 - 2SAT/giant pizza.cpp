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
    if (x > m) return x - m;
    else return x + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char op1, op2;
        int a, b;

        cin >> op1 >> a >> op2 >> b;

        if (op1 == '-') a = inv(a);
        if (op2 == '-') b = inv(b);

        // a v b <-> (!a => b) v (!b => a)
        adj[inv(a)].push_back(b);
        adj[inv(b)].push_back(a);
        
        adjt[b].push_back(inv(a));
        adjt[a].push_back(inv(b));
    }
    
    for (int i = 1; i <= m; i++) {
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
    
    for (int i = 1; i <= m; i++) {
        if (component[i] == component[inv(i)]) {
            ans = false;
        }
    }
    
    if (!ans) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        if (component[i] < component[inv(i)]) { // significa que era x e virou !x, então era falso
            cout << "- ";
        } else { // se não era !x e virou x, então eh verdadeiro
            cout << "+ ";
        }
    }
    cout << '\n';

    return 0;
}