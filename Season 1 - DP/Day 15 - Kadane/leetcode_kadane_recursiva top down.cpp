class Solution {
public:
    int n;
    vector<int> tb;

    int dp(int i, vector<int>& arr) {
        if (i == 0) return arr[0];

        if (tb[i] != -1) return tb[i];

        return tb[i] = max({
            arr[i],
            arr[i] + dp(i-1, arr),
        });
    }

    int maxSubArray(vector<int>& nums) {
        n = nums.size();
        tb.assign(n, -1);

        int ans = nums[0];

        for (int i = 0; i < n; i++) {
            ans = max(ans, dp(i, nums));
        }

        return ans;
    }
};