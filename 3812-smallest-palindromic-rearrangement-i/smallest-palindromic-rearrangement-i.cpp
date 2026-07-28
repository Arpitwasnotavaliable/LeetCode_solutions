class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        
        string half = "";
        char mid = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) mid = 'a' + i;
            half += string(cnt[i] / 2, 'a' + i);
        }
        
        string result = half;
        if (mid != 0) result += mid;
        result += string(half.rbegin(), half.rend());
        
        return result;
    }
};