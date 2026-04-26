#include <stdbool.h>

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

bool dfs(char** grid, int m, int n, bool visited[500][500], int r, int c,
         int pr, int pc) {
    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
            grid[nr][nc] == grid[r][c]) {
            if (visited[nr][nc]) {
                if (nr != pr || nc != pc)
                    return true;
            } else {
                if (dfs(grid, m, n, visited, nr, nc, r, c))
                    return true;
            }
        }
    }
    return false;
}

bool containsCycle(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    bool visited[500][500] = {false};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                if (dfs(grid, m, n, visited, i, j, -1, -1)) {
                    return true;
                }
            }
        }
    }

    return false;
}