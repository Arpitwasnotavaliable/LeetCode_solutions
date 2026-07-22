class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int totalOnes = 0;
        for (char c : s) if (c == '1') totalOnes++;

        vector<int> starts, ends, zlen;
        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                starts.push_back(i);
                ends.push_back(j - 1);
                zlen.push_back(j - i);
                i = j;
            } else i++;
        }

        int Z = starts.size();
        vector<int> adj;
        if (Z >= 2) {
            adj.resize(Z - 1);
            for (int k = 0; k < Z - 1; k++) adj[k] = zlen[k] + zlen[k + 1];
        }

        int m = adj.size();
        vector<vector<int>> sparse;
        if (m > 0) {
            int LOG = 1;
            while ((1 << LOG) <= m) LOG++;
            sparse.assign(LOG + 1, vector<int>(m));
            sparse[0] = adj;
            for (int k = 1; (1 << k) <= m; k++)
                for (int idx = 0; idx + (1 << k) <= m; idx++)
                    sparse[k][idx] = max(sparse[k-1][idx], sparse[k-1][idx + (1 << (k-1))]);
        }

        auto rangeMax = [&](int l, int r) -> int {
            if (l > r) return 0;
            int len = r - l + 1;
            int k = 31 - __builtin_clz(len);
            return max(sparse[k][l], sparse[k][r - (1 << k) + 1]);
        };

        vector<int> result;
        result.reserve(queries.size());

        for (auto& q : queries) {
            int l = q[0], r = q[1];
            int maxGain = 0;

            if (Z >= 2) {
                int idxFirst = lower_bound(ends.begin(), ends.end(), l) - ends.begin();
                if (idxFirst < Z && starts[idxFirst] <= r) {
                    int idxLast = upper_bound(starts.begin(), starts.end(), r) - starts.begin() - 1;
                    if (idxLast > idxFirst) {
                        int lenFirst = min(ends[idxFirst], r) - max(starts[idxFirst], l) + 1;
                        int lenLast = min(ends[idxLast], r) - max(starts[idxLast], l) + 1;
                        if (idxLast == idxFirst + 1) {
                            maxGain = lenFirst + lenLast;
                        } else {
                            int fullNext = zlen[idxFirst + 1];
                            int fullPrev = zlen[idxLast - 1];
                            int pairA = lenFirst + fullNext;
                            int pairB = fullPrev + lenLast;
                            int mid = 0;
                            if (idxLast - 2 >= idxFirst + 1)
                                mid = rangeMax(idxFirst + 1, idxLast - 2);
                            maxGain = max({pairA, pairB, mid});
                        }
                    }
                }
            }

            result.push_back(totalOnes + maxGain);
        }

        return result;
    }
};