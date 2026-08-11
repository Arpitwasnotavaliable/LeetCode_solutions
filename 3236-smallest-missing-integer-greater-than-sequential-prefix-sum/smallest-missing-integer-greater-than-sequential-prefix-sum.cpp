class Solution {
public:
    int missingInteger(vector<int>& nums) {
        // Find the sum of the longest sequential prefix
        int sum = nums[0];
        int i = 1;
        
        while (i < nums.size() && nums[i] == nums[i - 1] + 1) {
            sum += nums[i];
            i++;
        }

        // Store all numbers in the array
        unordered_set<int> s(nums.begin(), nums.end());

        // Find the smallest missing integer >= sum
        while (s.count(sum)) {
            sum++;
        }

        return sum;
    }
};