class Solution {
public:
    struct Node {
        int len = 0;
        int pref = 0;
        int suff = 0;
        int best = 0;
        char left = 0, right = 0;
    };

    vector<Node> seg;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.left = a.left;
        res.right = b.right;

        // Prefix
        res.pref = a.pref;
        if (a.pref == a.len && a.right == b.left)
            res.pref = a.len + b.pref;

        // Suffix
        res.suff = b.suff;
        if (b.suff == b.len && a.right == b.left)
            res.suff = b.len + a.suff;

        // Best inside either child
        res.best = max(a.best, b.best);

        // Best substring crossing the boundary
        if (a.right == b.left)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int idx, int l, int r, const string& s) {
        if (l == r) {
            seg[idx].len = 1;
            seg[idx].pref = 1;
            seg[idx].suff = 1;
            seg[idx].best = 1;
            seg[idx].left = seg[idx].right = s[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, s);
        build(idx * 2 + 1, mid + 1, r, s);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            seg[idx].left = seg[idx].right = c;
            seg[idx].pref = seg[idx].suff = seg[idx].best = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, c);
        else
            update(idx * 2 + 1, mid + 1, r, pos, c);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.size();
        int k = queryIndices.size();

        seg.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> ans;
        ans.reserve(k);

        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1,
                   queryIndices[i],
                   queryCharacters[i]);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};