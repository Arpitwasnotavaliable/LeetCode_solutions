class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxProd=nums[0];
        int minProd=nums[0];
        int n=nums.size();

        int ans=nums[0];

        for(int i=1;i<n;i++){

            int tempMax=maxProd;
            int tempMin=minProd;

            maxProd=max(nums[i],max(nums[i]*tempMax,nums[i]*tempMin));

            minProd=min(nums[i],min(nums[i]*tempMax,nums[i]*tempMin));

            ans=max(ans,maxProd);
        }
        return ans;
    }
};