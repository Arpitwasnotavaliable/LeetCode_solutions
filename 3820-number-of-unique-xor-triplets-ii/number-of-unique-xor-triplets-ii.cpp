class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // distinct values
        vector<int> V(nums.begin(), nums.end());
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());
        
        const int LIMIT = 2048; // since nums[i] <= 1500, XOR results < 2048
        
        vector<bool> seen2(LIMIT, false);
        for (int a : V) {
            for (int b : V) {
                seen2[a ^ b] = true;
            }
        }
        
        vector<int> list2;
        for (int x = 0; x < LIMIT; x++) {
            if (seen2[x]) list2.push_back(x);
        }
        
        vector<bool> seen3(LIMIT, false);
        for (int s : list2) {
            for (int c : V) {
                seen3[s ^ c] = true;
            }
        }
        
        int count = 0;
        for (int x = 0; x < LIMIT; x++) {
            if (seen3[x]) count++;
        }
        
        return count;
    }
};