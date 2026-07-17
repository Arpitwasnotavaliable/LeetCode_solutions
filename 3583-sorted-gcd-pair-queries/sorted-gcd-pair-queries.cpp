class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxVal = 0;
        for (int x : nums) maxVal = max(maxVal, x);

        vector<int> freq(maxVal + 1, 0);
        for (int x : nums) freq[x]++;

        // cnt[v] = number of elements divisible by v
        vector<int> cnt(maxVal + 1, 0);
        for (int v = 1; v <= maxVal; v++) {
            long long c = 0;
            for (int m = v; m <= maxVal; m += v) c += freq[m];
            cnt[v] = (int)c;
        }

        // atLeast[v] = C(cnt[v], 2)
        vector<long long> exact(maxVal + 1, 0);
        for (int v = 1; v <= maxVal; v++) {
            long long c = cnt[v];
            exact[v] = c * (c - 1) / 2;
        }

        // subtract multiples, from high to low, to get exact gcd counts
        for (int v = maxVal; v >= 1; v--) {
            for (int m = 2 * v; m <= maxVal; m += v) {
                exact[v] -= exact[m];
            }
        }

        // prefix sums (cumulative count of pairs with gcd <= v)
        vector<long long> prefix(maxVal + 1, 0);
        for (int v = 1; v <= maxVal; v++) {
            prefix[v] = prefix[v - 1] + exact[v];
        }

        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            // find smallest v with prefix[v] > q
            int lo = 1, hi = maxVal, res = maxVal;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (prefix[mid] > q) {
                    res = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
};