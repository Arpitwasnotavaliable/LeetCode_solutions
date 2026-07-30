class Solution {
private:
    bool checkEqual(int a[26], int b[26]) {
        for (int i = 0; i < 26; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.length();
        int n2 = s2.length();
        if (n1 > n2) return false;  // s1 can't fit in s2

        int count1[26] = {0};
        for (int i = 0; i < n1; i++) {
            count1[s1[i] - 'a']++;
        }

        int winsize = n1;
        int count2[26] = {0};

        // build the first window
        for (int i = 0; i < winsize; i++) {
            count2[s2[i] - 'a']++;
        }

        if (checkEqual(count1, count2)) return true;

        // slide the window across the rest of s2
        for (int i = winsize; i < n2; i++) {
            count2[s2[i] - 'a']++;              // add new char entering window
            count2[s2[i - winsize] - 'a']--;    // remove char leaving window

            if (checkEqual(count1, count2)) return true;
        }

        return false;
    }
};