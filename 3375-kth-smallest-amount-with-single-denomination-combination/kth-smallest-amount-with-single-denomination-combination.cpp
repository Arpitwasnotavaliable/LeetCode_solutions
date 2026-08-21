class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto lcm = [](long long a, long long b) {
            return a / std::gcd(a, b) * b;
        };

        // Count distinct amounts <= x using inclusion-exclusion
        auto count = [&](long long x) {
            long long ans = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long L = 1;
                int bits = 0;
                bool tooLarge = false;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        L = lcm(L, (long long)coins[i]);

                        if (L > x) {
                            tooLarge = true;
                            break;
                        }
                    }
                }

                if (tooLarge) continue;

                long long ways = x / L;

                if (bits & 1)
                    ans += ways;
                else
                    ans -= ways;
            }

            return ans;
        };

        long long lo = 1;
        long long hi = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};
