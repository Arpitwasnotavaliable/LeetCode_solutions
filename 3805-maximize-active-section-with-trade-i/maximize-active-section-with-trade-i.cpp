class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";
        int n = t.size();
        
        vector<pair<char,int>> blocks;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && t[j] == t[i]) j++;
            blocks.push_back({t[i], j - i});
            i = j;
        }
        
        int ones = 0;
        for (char c : s) if (c == '1') ones++;
        
        int maxGain = 0;
        for (int idx = 2; idx < (int)blocks.size() - 1; idx += 2) {
            int gain = blocks[idx - 1].second + blocks[idx + 1].second;
            maxGain = max(maxGain, gain);
        }
        
        return ones + maxGain;
    }
};