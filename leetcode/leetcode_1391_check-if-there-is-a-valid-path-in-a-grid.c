#include <stdbool.h>
#include <stdlib.h>

bool hasValidPath(int **grid, int gridSize, int *gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    bool canMove[7][4] = {false};
    canMove[1][2] = canMove[1][3] = true;
    canMove[2][0] = canMove[2][1] = true;
    canMove[3][2] = canMove[3][1] = true;
    canMove[4][3] = canMove[4][1] = true;
    canMove[5][2] = canMove[5][0] = true;
    canMove[6][3] = canMove[6][0] = true;

    bool *visited = (bool *)calloc(m * n, sizeof(bool));
    if (!visited)
        return false;

    int *stack_r = (int *)malloc(m * n * sizeof(int));
    int *stack_c = (int *)malloc(m * n * sizeof(int));
    if (!stack_r || !stack_c) {
        free(visited);
        free(stack_r);
        free(stack_c);
        return false;
    }
    int top = 0; // 栈顶指针

    stack_r[top] = 0;
    stack_c[top] = 0;
    top++;
    visited[0 * n + 0] = true;

    while (top > 0) {
        top--;
        int r = stack_r[top];
        int c = stack_c[top];

        if (r == m - 1 && c == n - 1) {
            free(visited);
            free(stack_r);
            free(stack_c);
            return true;
        }

        int type = grid[r][c];
        for (int d = 0; d < 4; ++d) {
            if (!canMove[type][d])
                continue;

            int nr = r + dx[d];
            int nc = c + dy[d];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;
            if (visited[nr * n + nc])
                continue;

            int ntype = grid[nr][nc];
            int rev = d ^ 1; // 反向方向：0↔1, 2↔3
            if (canMove[ntype][rev]) {
                visited[nr * n + nc] = true;
                stack_r[top] = nr;
                stack_c[top] = nc;
                top++;
            }
        }
    }

    free(visited);
    free(stack_r);
    free(stack_c);
    return false;
}