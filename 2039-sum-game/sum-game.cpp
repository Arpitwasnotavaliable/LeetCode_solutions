class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int diff = 0;
        int q1 = 0, q2 = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                q1++;
            else
                diff += num[i] - '0';
        }

        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                q2++;
            else
                diff -= num[i] - '0';
        }

        // Alice gets the extra move.
        if ((q1 + q2) % 2 == 1)
            return true;

        // Bob wins only when he can force the final difference to 0.
        int required = 9 * (q2 - q1) / 2;

        return diff != required;
    }
};