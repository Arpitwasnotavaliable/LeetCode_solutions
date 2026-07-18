class Solution {
public:
    int findGCD(vector<int>& nums) {
        int a = *min_element(nums.begin(), nums.end());
        int b = *max_element(nums.begin(), nums.end());
        return gcd(a, b); // C++17 <numeric>, or use __gcd(a, b)
    }
};