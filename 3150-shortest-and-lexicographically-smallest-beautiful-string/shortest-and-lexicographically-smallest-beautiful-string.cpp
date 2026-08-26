class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();

        int left = 0;
        int ones = 0;

        string ans = "";

        for (int right = 0; right < n; right++) {

            if (s[right] == '1') {
                ones++;
            }

            // We have exactly k ones
            if (ones == k) {

                // Remove unnecessary leading zeroes
                while (left <= right && s[left] == '0') {
                    left++;
                }

                string curr = s.substr(left, right - left + 1);

                // First valid answer
                if (ans == "") {
                    ans = curr;
                }
                // Shorter substring
                else if (curr.length() < ans.length()) {
                    ans = curr;
                }
                // Same length -> lexicographically smaller
                else if (curr.length() == ans.length() && curr < ans) {
                    ans = curr;
                }

                // Move left past the first 1
                if (s[left] == '1') {
                    ones--;
                    left++;
                }
            }
        }

        return ans;
    }
};