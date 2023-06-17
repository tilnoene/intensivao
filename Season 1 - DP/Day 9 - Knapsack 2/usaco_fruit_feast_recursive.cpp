#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

const int MAXT = 5e6+17;
const int INF = 1e9+17;

int t, a, b;
int tb[MAXT][2]; // consigo fullness de i?

bool dp(int cap, bool water) {
	if (cap > t) return false;

	int& mem = tb[cap][water];
	if (mem != -1) return mem;

	mem = true;

	if (!water) {
		dp(cap+a, false);
		dp(cap+b, false);
		dp(cap/2, true);
	} else {
		dp(cap+a, true);
		dp(cap+b, true);
	}

	return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(tb, -1, sizeof(tb));

    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    
    cin >> t >> a >> b;

    dp(t, false);
    
    int ans = 0;

    for (int i = 0; i <= t; i++) {
        if (tb[i][0] == true || tb[i][1] == true) ans = i;
    }
    
    cout << ans << '\n';
    
    return 0;
}