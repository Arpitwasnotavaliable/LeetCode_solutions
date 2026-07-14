class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0, hi = arr.size() - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (arr[mid] < arr[mid + 1]) {
                // still climbing, peak is to the right
                lo = mid + 1;
            } else {
                // descending (or at peak), peak is at mid or to the left
                hi = mid;
            }
        }

        return lo;
    }
};