class Solution {
public:
    int n, m;
    vector<vector<int>> tb;

    int dp(int i, int j, string& a, string& b) {
        if (i >= n || j >= m) {
            return 0;
        }

        int& ans = tb[i][j];

        if (ans != -1) {
            return ans;
        }

        ans = max(dp(i+1, j, a, b), dp(i, j+1, a, b));

        if (a[i] == b[j]) {
            ans = max(ans, dp(i+1, j+1, a, b) + 1);
        }

        return ans;
    }

    int longestCommonSubsequence(string text1, string text2) {
        n = text1.size();
        m = text2.size();

        tb.assign(n, vector<int>(m, -1));

        return dp(0, 0, text1, text2);
    }
};