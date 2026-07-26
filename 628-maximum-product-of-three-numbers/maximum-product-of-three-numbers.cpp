class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int first = INT_MIN, second = INT_MIN, third = INT_MIN;      // three largest
        int minFirst = INT_MAX, minSecond = INT_MAX;                 // two smallest

        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];

            // update three largest
            if (num > first) {
                third = second;
                second = first;
                first = num;
            } else if (num > second) {
                third = second;
                second = num;
            } else if (num > third) {
                third = num;
            }

            // update two smallest
            if (num < minFirst) {
                minSecond = minFirst;
                minFirst = num;
            } else if (num < minSecond) {
                minSecond = num;
            }
        }

        return max(first * second * third, first * minFirst * minSecond);
    }
};