class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int s=0,end=numbers.size()-1;
        
        while(s<end){
            int currsum=numbers[s]+numbers[end];
            if(currsum==target){
                return {s+1,end+1};
            }else{
                if(currsum>target){
                    end--;
                }else{
                    s++;
                }
            }
        }
        return {};
    }
    
};