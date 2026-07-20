class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int total = m * n;
        k %= total;
        
        vector<int> flat;
        flat.reserve(total);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                flat.push_back(grid[i][j]);
        
        vector<vector<int>> result(m, vector<int>(n));
        for (int idx = 0; idx < total; idx++) {
            int newIdx = (idx + k) % total;
            result[newIdx / n][newIdx % n] = flat[idx];
        }
        
        return result;
    }
};