#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define DIST(a, b) (ABS((a)/6 - (b)/6) + ABS((a)%6 - (b)%6))

int minimumDistance(char* word) {
    int n = strlen(word);
    if (n < 3)
        return 0;

    int dp[2][26] = {0};
    int cur = 0, nxt = 1;

    for (int i = n - 1; i >= 1; i--) {
        int c = word[i] - 'A';
        int p = word[i - 1] - 'A';

        for (int last = 0; last < 26; last++) {
            dp[nxt][last] =
                MIN(DIST(p, c) + dp[cur][last], DIST(last, c) + dp[cur][p]);
        }

        int tmp = cur;
        cur = nxt;
        nxt = tmp;
    }

    int ans = dp[cur][0];
    for (int i = 1; i < 26; i++) {
        if (dp[cur][i] < ans)
            ans = dp[cur][i];
    }
    return ans;
}