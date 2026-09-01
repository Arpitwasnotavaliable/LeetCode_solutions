class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;

        vector<pair<int, int>> litter;

        // Find start and litter
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                }
                else if (classroom[r][c] == 'L') {
                    litter.push_back({r, c});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        // Give each litter a bit number
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int allMask = (1 << k) - 1;

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r,c) having collected 'mask'.
        */

        int masks = 1 << k;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(
                n,
                vector<int>(masks, -1)
            )
        );

        struct State {
            int r;
            int c;
            int mask;
            int energy;
        };

        queue<State> q;

        q.push({sr, sc, 0, energy});
        best[sr][sc][0] = energy;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                State cur = q.front();
                q.pop();

                int r = cur.r;
                int c = cur.c;
                int mask = cur.mask;
                int currEnergy = cur.energy;

                if (mask == allMask)
                    return moves;

                if (currEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        newMask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    /*
                        If we have already reached this
                        (position, mask) with >= energy,
                        this state is useless.
                    */
                    if (best[nr][nc][newMask] >= newEnergy)
                        continue;

                    best[nr][nc][newMask] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};