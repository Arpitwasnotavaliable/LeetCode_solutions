#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // Store reserved seats for each affected row as a bitmask.
        unordered_map<int, int> reserved;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            // Only seats 2..9 matter.
            if (s >= 2 && s <= 9) {
                reserved[row] |= (1 << s);
            }
        }

        // Every completely empty row can accommodate 2 groups.
        long long ans = 2LL * (n - reserved.size());

        for (auto &[row, mask] : reserved) {
            bool left  = true; // seats 2,3,4,5
            bool right = true; // seats 6,7,8,9
            bool mid   = true; // seats 4,5,6,7

            for (int s = 2; s <= 5; s++) {
                if (mask & (1 << s)) {
                    left = false;
                    break;
                }
            }

            for (int s = 6; s <= 9; s++) {
                if (mask & (1 << s)) {
                    right = false;
                    break;
                }
            }

            for (int s = 4; s <= 7; s++) {
                if (mask & (1 << s)) {
                    mid = false;
                    break;
                }
            }

            if (left && right) {
                ans += 2;
            } else if (left || right || mid) {
                ans += 1;
            }
        }

        return (int)ans;
    }
};
