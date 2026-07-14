class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int maxVal = 200;
        
        vector<vector<long long>> dp(maxVal + 1, vector<long long>(maxVal + 1, 0));
        dp[0][0] = 1;
        
        for (int val : nums) {
            vector<vector<long long>> ndp = dp; 
            for (int g1 = 0; g1 <= maxVal; g1++) {
                for (int g2 = 0; g2 <= maxVal; g2++) {
                    long long ways = dp[g1][g2];
                    if (ways == 0) continue;
                    
                    
                    int ng1 = (g1 == 0) ? val : __gcd(g1, val);
                    ndp[ng1][g2] = (ndp[ng1][g2] + ways) % MOD;
                    
                   
                    int ng2 = (g2 == 0) ? val : __gcd(g2, val);
                    ndp[g1][ng2] = (ndp[g1][ng2] + ways) % MOD;
                }
            }
            dp = move(ndp);
        }
        
        long long ans = 0;
        for (int g = 1; g <= maxVal; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }
        return (int)ans;
    }
};