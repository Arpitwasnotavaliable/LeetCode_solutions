class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int V = 200;
        const int N = V + 1;

        vector<long long> dp(N * N, 0), ndp(N * N, 0);
        dp[0] = 1;

        vector<int> gcdTable(N);

        for (int val : nums) {
            gcdTable[0] = val;
            for (int g = 1; g <= V; g++) gcdTable[g] = __gcd(g, val);

            ndp = dp;

            for (int g1 = 0; g1 <= V; g1++) {
                const long long* row = &dp[g1 * N];
                int ng1 = gcdTable[g1];
                long long* ndpRow1 = &ndp[ng1 * N];
                for (int g2 = 0; g2 <= V; g2++) {
                    long long ways = row[g2];
                    if (!ways) continue;

                    ndpRow1[g2] += ways;
                    if (ndpRow1[g2] >= MOD) ndpRow1[g2] -= MOD;

                    int ng2 = gcdTable[g2];
                    long long& cell = ndp[g1 * N + ng2];
                    cell += ways;
                    if (cell >= MOD) cell -= MOD;
                }
            }

            swap(dp, ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= V; g++) {
            ans = (ans + dp[g * N + g]) % MOD;
        }
        return (int)ans;
    }
};