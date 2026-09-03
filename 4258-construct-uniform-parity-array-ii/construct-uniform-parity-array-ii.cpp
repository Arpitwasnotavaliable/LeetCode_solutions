class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        long long minOdd = LLONG_MAX, minEven = LLONG_MAX;
        bool hasOdd = false, hasEven = false;
        
        for (int x : nums1) {
            if (x % 2 == 0) {
                hasEven = true;
                minEven = min(minEven, (long long)x);
            } else {
                hasOdd = true;
                minOdd = min(minOdd, (long long)x);
            }
        }
        
        bool targetEven = !hasOdd;                                  // no odd numbers at all
        bool targetOdd  = !hasEven || (hasOdd && minOdd < minEven);  // no evens, or smallest odd beats smallest even
        
        return targetEven || targetOdd;
    }
};