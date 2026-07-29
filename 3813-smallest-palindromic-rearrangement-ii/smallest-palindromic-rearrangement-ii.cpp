class Solution {
public:
    static const long long CAP = 1000001LL; // > max possible k (1e6)

    // C(n, r) capped at CAP (returns CAP+1 if the true value exceeds CAP)
    long long nCrCapped(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        if (r > n - r) r = n - r;
        long long res = 1;
        for (long long i = 1; i <= r; i++) {
            res = res * (n - r + i) / i;
            if (res > CAP) return CAP + 1;
        }
        return res;
    }

    // multinomial coefficient of counts[], capped at CAP
    long long multinomialCapped(vector<long long>& counts) {
        long long total = 0;
        for (long long c : counts) total += c;
        long long res = 1;
        for (long long c : counts) {
            if (c == 0) continue;
            long long term = nCrCapped(total, c);
            if (term > CAP) return CAP + 1;
            res *= term;
            if (res > CAP) return CAP + 1;
            total -= c;
        }
        return res;
    }

    string smallestPalindrome(string s, int k) {
        long long K = k;
        int n = s.size();
        vector<long long> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        vector<long long> half(26, 0);
        char mid = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) mid = 'a' + i;
            half[i] = cnt[i] / 2;
        }

        long long L = 0;
        for (int i = 0; i < 26; i++) L += half[i];

        long long totalPerms = multinomialCapped(half);
        if (totalPerms < K) return "";

        string result;
        result.reserve(L);
        vector<long long> remaining = half;

        for (long long pos = 0; pos < L; pos++) {
            for (int c = 0; c < 26; c++) {
                if (remaining[c] == 0) continue;
                remaining[c]--;
                long long cntPerms = multinomialCapped(remaining);
                if (K <= cntPerms) {
                    result += (char)('a' + c);
                    break;
                } else {
                    K -= cntPerms;
                    remaining[c]++;
                }
            }
        }

        string res = result;
        if (mid != 0) res += mid;
        for (int i = (int)result.size() - 1; i >= 0; i--) res += result[i];

        return res;
    }
};