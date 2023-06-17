class Solution {
public:
    int n;
    vector<int> tb;

    int dp(int i, vector<int>& arr) {
        if (i == n-1) return arr[n-1];

        int& mem = tb[i];
        if (mem != -1) return mem;

        mem = max({
            arr[i],
            arr[i] + dp(i+1, arr),
        });

        return mem;
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