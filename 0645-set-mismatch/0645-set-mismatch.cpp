class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();

        vector<int> freq(n, 0);

        for(int i=0;i<n;i++){
            freq[nums[i]-1]++;
        }
        int dup = -1, missing = -1;

        for(int i=0;i<n;i++){
            if(freq[i]==2){
                dup=i+1;
            }else if(freq[i]==0){
                missing=i+1;
            }
        }
        return {dup,missing};
    }
};