#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

struct TrieXOR {
    int n, alph_sz, nxt;
    vector<vector<int>> trie;
    vector<int> finish, paths;

    TrieXOR() {}

    TrieXOR(int n, int alph_sz = 2) : n(n), alph_sz(alph_sz) {
        nxt = 1;
        trie.assign(n, vector<int>(alph_sz));
        finish.assign(n * alph_sz, 0);
        paths.assign(n * alph_sz, 0);
    }

    void add(int x) {
        int curr = 0;

        for (int i = 31; i >= 0; i--) {
            int b = ((x&(1 << i)) > 0);

            if (trie[curr][b] == 0)
                trie[curr][b] = nxt++;

            paths[curr]++;
            curr = trie[curr][b];
        }

        paths[curr]++;
        finish[curr]++;
    }

    void rem(int x) {
        int curr = 0;

        for (int i = 31; i >= 0; i--) {
            int b = ((x&(1 << i)) > 0);

            paths[curr]--;
            curr = trie[curr][b];
        }

        paths[curr]--;
        finish[curr]--;
    }

    int search(int x) {
        int curr = 0;

        for (int i = 31; i >= 0; i--) {
            int b = ((x&(1 << i)) > 0);

            if (trie[curr][b] == 0) return false;

            curr = trie[curr][b];
        }

        return (finish[curr] > 0);
    }

    int max_xor(int x) { // maximum xor with x and any number of trie
        int curr = 0, ans = 0;

        for (int i = 31; i >= 0; i--) {
            int b = ((x&(1 << i)) > 0);
            
            int bz = trie[curr][0];
            int bo = trie[curr][1];

            if (bz > 0 && paths[bz] > 0 && bo > 0 && paths[bo] > 0) {
                // optimal, escolhe qualquer um
                curr = trie[curr][b ^ 1];
                ans += (1 << i);
            } else if (bz > 0 && paths[bz] > 0) {
                // zero
                curr = trie[curr][0];
                if (b) ans += (1 << i);
            } else if (bo > 0 && paths[bo] > 0) {
                // one
                curr = trie[curr][1];
                if (!b) ans += (1 << i);
            } else {
                break;
            }

        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    TrieXOR trie(32 * 1e5+17);
    
    trie.add(0);

    int q; cin >> q;
    while (q--) {
        char op; cin >> op;
        int x; cin >> x;

        if (op == '+') trie.add(x);
        else if (op == '-') trie.rem(x);
        else {
            cout << trie.max_xor(x) << '\n';
        }
    }
    
    return 0;
}