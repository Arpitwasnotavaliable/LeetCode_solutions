class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2 * n);
        int p1=0,p2=n;
        
        for(int i=0;i<(2*n);i++){
            
            if(i%2==0){
                ans[i]=nums[p1];
                p1++;
            }
            else{
                ans[i]=nums[p2];
                p2++;
            }
           
        }
        return ans;
    }
};