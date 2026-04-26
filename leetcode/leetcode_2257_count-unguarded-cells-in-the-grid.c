int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize, int* wallsColSize) {

    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < wallsSize; i++) {
        int x = walls[i][0];
        int y = walls[i][1];
        grid[x][y] = 3;
    }

    for (int i = 0; i < guardsSize; i++) {
        int x = guards[i][0];
        int y = guards[i][1];
        grid[x][y] = 2;
    }

    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < guardsSize; i++) {
        int startX = guards[i][0];
        int startY = guards[i][1];

        for (int d = 0; d < 4; d++) {
            int dx = directions[d][0];
            int dy = directions[d][1];

            int x = startX + dx;
            int y = startY + dy;

            while (x >= 0 && x < m && y >= 0 && y < n) {

                if (grid[x][y] == 3 || grid[x][y] == 2) {
                    break;
                }

                grid[x][y] = 1;

                x += dx;
                y += dy;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                count++;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);

    return count;
}