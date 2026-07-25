class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int temp=0;
        for(int i=m;i<(m+n);i++){
          
            nums1[i]=nums2[temp];
            temp++;
        }
        sort(nums1.begin(),nums1.end());





    }
};