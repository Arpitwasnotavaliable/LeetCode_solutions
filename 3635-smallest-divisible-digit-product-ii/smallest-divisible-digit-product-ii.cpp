class Solution {
public:
    int A, B, C, D, dB, dC, dD;
    vector<int> minDig;
    int digitFac[10][4];

    inline int idx(int a, int b, int c, int d) {
        return ((a * dB + b) * dC + c) * dD + d;
    }

    void apply(int a, int b, int c, int d, int dig, int &na, int &nb, int &nc, int &nd) {
        na = max(a - digitFac[dig][0], 0);
        nb = max(b - digitFac[dig][1], 0);
        nc = max(c - digitFac[dig][2], 0);
        nd = max(d - digitFac[dig][3], 0);
    }

    // Greedily build the smallest L-digit zero-free suffix that reduces
    // state (a,b,c,d) down to (0,0,0,0).
    string buildSuffix(int a, int b, int c, int d, int L) {
        string res(L, '1');
        for (int pos = 0; pos < L; pos++) {
            int rem = L - pos - 1;
            for (int dig = 1; dig <= 9; dig++) {
                int na, nb, nc, nd;
                apply(a, b, c, d, dig, na, nb, nc, nd);
                if (minDig[idx(na, nb, nc, nd)] <= rem) {
                    res[pos] = char('0' + dig);
                    a = na; b = nb; c = nc; d = nd;
                    break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        // Factor t into 2^A * 3^B * 5^C * 7^D (digits 1-9 only have these prime factors)
        long long tt = t;
        A = B = C = D = 0;
        while (tt % 2 == 0) { tt /= 2; A++; }
        while (tt % 3 == 0) { tt /= 3; B++; }
        while (tt % 5 == 0) { tt /= 5; C++; }
        while (tt % 7 == 0) { tt /= 7; D++; }
        if (tt != 1) return "-1"; // impossible - leftover prime factor

        dB = B + 1; dC = C + 1; dD = D + 1;
        minDig.assign((long long)(A + 1) * dB * dC * dD, 0);

        // digitFac[d] = {power of 2, power of 3, power of 5, power of 7} contributed by digit d
        int df[10][4] = {
            {0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {2,0,0,0},
            {0,0,1,0}, {1,1,0,0}, {0,0,0,1}, {3,0,0,0}, {0,2,0,0}
        };
        for (int i = 0; i < 10; i++)
            for (int k = 0; k < 4; k++)
                digitFac[i][k] = df[i][k];

        // minDig[a][b][c][d] = minimum number of digits (2-9) needed to
        // reduce remaining requirement (a,b,c,d) down to (0,0,0,0)
        const int INF = 1e9;
        for (int a = 0; a <= A; a++)
        for (int b = 0; b <= B; b++)
        for (int c = 0; c <= C; c++)
        for (int d = 0; d <= D; d++) {
            if (!a && !b && !c && !d) { minDig[idx(a,b,c,d)] = 0; continue; }
            int best = INF;
            for (int dig = 2; dig <= 9; dig++) {
                int na, nb, nc, nd;
                apply(a, b, c, d, dig, na, nb, nc, nd);
                if (na == a && nb == b && nc == c && nd == d) continue; // no progress
                best = min(best, 1 + minDig[idx(na, nb, nc, nd)]);
            }
            minDig[idx(a, b, c, d)] = best;
        }

        int n = num.size();

        // j = position of first '0' in num (or n if none)
        int j = n;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') { j = i; break; }
        }

        // prefix state after processing num[0..k-1], only valid up to index j
        vector<array<int,4>> pref(j + 1);
        pref[0] = {A, B, C, D};
        for (int k = 1; k <= j; k++) {
            int dig = num[k - 1] - '0';
            int na, nb, nc, nd;
            apply(pref[k-1][0], pref[k-1][1], pref[k-1][2], pref[k-1][3], dig, na, nb, nc, nd);
            pref[k] = {na, nb, nc, nd};
        }

        // Case 1: num itself is already valid (zero-free and product divisible by t)
        if (j == n) {
            auto &s = pref[n];
            if (!s[0] && !s[1] && !s[2] && !s[3]) return num;
        }

        // Case 2: find the rightmost position where we can bump the digit up,
        // keeping the same length
        int startI = min(n - 1, j);
        for (int i = startI; i >= 0; i--) {
            auto &s0 = pref[i];
            int startD = (num[i] == '0') ? 1 : (num[i] - '0' + 1);
            int L = n - 1 - i; // digits remaining after position i
            for (int dg = startD; dg <= 9; dg++) {
                int na, nb, nc, nd;
                apply(s0[0], s0[1], s0[2], s0[3], dg, na, nb, nc, nd);
                if (minDig[idx(na, nb, nc, nd)] <= L) {
                    return num.substr(0, i) + char('0' + dg) + buildSuffix(na, nb, nc, nd, L);
                }
            }
        }

        // Case 3: no same-length answer exists — the result must have more digits.
        // It needs at least n+1 digits (to exceed num), and at least M digits
        // (the minimum possible to satisfy the product requirement at all).
        int M = minDig[idx(A, B, C, D)];
        int Lp = max(n + 1, M);
        return buildSuffix(A, B, C, D, Lp);
    }
};