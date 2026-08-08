class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        // next[i][c] = smallest index >= i where word1 has character c (n if none)
        vector<array<int,26>> nxt(n + 1);
        nxt[n].fill(n);
        for (int i = n - 1; i >= 0; i--) {
            nxt[i] = nxt[i + 1];
            nxt[i][word1[i] - 'a'] = i;
        }

        // suf[i] = longest suffix of word2 that is an exact subsequence of word1[i:]
        vector<int> suf(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = suf[i + 1];
            if (suf[i] < m && word1[i] == word2[m - 1 - suf[i]]) suf[i]++;
        }

        vector<int> ans;
        ans.reserve(m);
        int i = 0, k = 0;
        bool used = false;

        while (k < m) {
            if (i >= n) return {}; // ran out of word1

            if (word1[i] == word2[k]) {
                // Exact match at the smallest possible index — always take it.
                ans.push_back(i);
                i++; k++;
            } else {
                int remain = m - 1 - k; // chars still needed exactly after this one
                if (!used && suf[i + 1] >= remain) {
                    // Use our one mismatch here — gives smallest possible index.
                    ans.push_back(i);
                    used = true;
                    i++; k++;
                } else {
                    // Can't use mismatch (either already used or infeasible) — 
                    // search forward for an exact match instead.
                    int nx = nxt[i][word2[k] - 'a'];
                    if (nx == n) return {};
                    ans.push_back(nx);
                    i = nx + 1; k++;
                }
            }
        }

        return ans;
    }
};