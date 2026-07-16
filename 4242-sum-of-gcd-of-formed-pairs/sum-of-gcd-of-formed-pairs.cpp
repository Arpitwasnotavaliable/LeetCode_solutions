// class Solution {
// public:
//     long long gcdSum(vector<int>& nums) {
//         int n = nums.size();
//         vector<long long> prefixGcd(n);
//         long long mx = 0;
//         for (int i = 0; i < n; i++) {
//             mx = max(mx, (long long)nums[i]);
//             prefixGcd[i] = __gcd((long long)nums[i], mx);
//         }
//         sort(prefixGcd.begin(), prefixGcd.end());
//         long long sum = 0;
//         int l = 0, r = n - 1;
//         while (l < r) {
//             sum += __gcd(prefixGcd[l], prefixGcd[r]);
//             l++;
//             r--;
//         }
//         return sum;
//     }
// };


class Solution {
public:
    static inline int mygcd(int a, int b) {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);
        int mx = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > mx) mx = nums[i];
            prefixGcd[i] = mygcd(nums[i], mx);
        }
        sort(prefixGcd.begin(), prefixGcd.end());
        long long sum = 0;
        int l = 0, r = n - 1;
        while (l < r) {
            sum += mygcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }
        return sum;
    }
};



