class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        vector<int> Ans(2 * n);

        for (int i = 0; i < n; i++) {
            Ans[i] = nums[i];
            Ans[i + n] = nums[i];
        }

        return Ans;
    }
};