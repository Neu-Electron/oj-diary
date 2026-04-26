#include <limits.h>
#include <math.h>
#include <stdlib.h>

long long minimumTotalDistance(int* robot, int robotSize, int** factory,
                               int factorySize, int* factoryColSize) {

    for (int i = 0; i < robotSize - 1; i++) {
        for (int j = 0; j < robotSize - i - 1; j++) {
            if (robot[j] > robot[j + 1]) {
                int temp = robot[j];
                robot[j] = robot[j + 1];
                robot[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < factorySize - 1; i++) {
        for (int j = 0; j < factorySize - i - 1; j++) {
            if (factory[j][0] > factory[j + 1][0]) {
                int* temp = factory[j];
                factory[j] = factory[j + 1];
                factory[j + 1] = temp;
            }
        }
    }

    const int n = robotSize;
    const int m = factorySize;
    const long long INF = LLONG_MAX;

    long long** dp = (long long**)malloc((m + 1) * sizeof(long long*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (long long*)malloc((n + 1) * sizeof(long long));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
        dp[i][0] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int pos = factory[i - 1][0];
        int limit = factory[i - 1][1];

        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];

            long long dist_sum = 0;
            int max_cnt = j < limit ? j : limit;

            for (int cnt = 1; cnt <= max_cnt; cnt++) {
                dist_sum += abs(robot[j - cnt] - pos);
                if (dp[i - 1][j - cnt] != INF) {
                    long long candidate = dp[i - 1][j - cnt] + dist_sum;
                    if (candidate < dp[i][j]) {
                        dp[i][j] = candidate;
                    }
                }
            }
        }
    }

    long long result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}