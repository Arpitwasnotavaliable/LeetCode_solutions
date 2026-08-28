class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        // A palindrome can have at most one odd frequency.
        int odd = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Number of each character needed in the left half.
        vector<int> half(26);

        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;

        int m = n / 2;

        // Try constructing the left half to match target.
        string pref;

        for (int i = 0; i < m; i++) {
            int c = target[i] - 'a';

            if (half[c] == 0)
                break;

            pref += target[i];
            half[c]--;
        }

        // If the complete left half matches target's left half,
        // check its palindrome.
        if ((int)pref.size() == m) {
            string rev = pref;
            reverse(rev.begin(), rev.end());

            string ans = pref;

            if (n % 2)
                ans += middle;

            ans += rev;

            if (ans > target)
                return ans;
        }


        // Rebuild half counts from scratch.
        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;

        // We will try every possible pivot.
        for (int pivot = m - 1; pivot >= 0; pivot--) {

            vector<int> rem = half;

            // Match target before pivot.
            bool possible = true;

            for (int i = 0; i < pivot; i++) {
                int c = target[i] - 'a';

                if (rem[c] == 0) {
                    possible = false;
                    break;
                }

                rem[c]--;
            }

            if (!possible)
                continue;

            int cur = target[pivot] - 'a';

            // Try the smallest possible character > target[pivot].
            for (int c = cur + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                string left = target.substr(0, pivot);

                left += char('a' + c);

                rem[c]--;

                // Smallest possible suffix.
                for (int x = 0; x < 26; x++) {
                    left += string(rem[x], char('a' + x));
                }

                string right = left;
                reverse(right.begin(), right.end());

                string ans = left;

                if (n % 2)
                    ans += middle;

                ans += right;

                return ans;
            }
        }

        return "";
    }
};