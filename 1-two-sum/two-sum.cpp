class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int start=0;
        while(start<nums.size()){

            for(int i=start+1;i<nums.size();i++){
                if(target==nums[start]+nums[i]){

                    return{start,i};

                }

                
            }
            start++;
        }
        return{};
    }
};