class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // prefix[i] = sum of stoneValue[0 ... i-1]
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        // dp[l][r] = maximum score obtainable from subarray [l, r]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;

                for (int k = l; k < r; k++) {
                    long long leftSum = prefix[k + 1] - prefix[l];
                    long long rightSum = prefix[r + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {
                        // Bob throws away right part.
                        // Alice keeps left part.
                        dp[l][r] = max(dp[l][r],
                                       (int)(leftSum + dp[l][k]));
                    }
                    else if (leftSum > rightSum) {
                        // Bob throws away left part.
                        // Alice keeps right part.
                        dp[l][r] = max(dp[l][r],
                                       (int)(rightSum + dp[k + 1][r]));
                    }
                    else {
                        // Equal: Alice can choose either part.
                        dp[l][r] = max(dp[l][r],
                                       (int)(leftSum + dp[l][k]));
                        dp[l][r] = max(dp[l][r],
                                       (int)(rightSum + dp[k + 1][r]));
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};