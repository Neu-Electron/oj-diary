#define MOD 1000000007

int possibleStringCount(char* word, int k) {
    int len = strlen(word);
    if (len == k)
        return 1;

    int* char_block = (int*)malloc(len * sizeof(int));
    int block_size = 0;
    int count = 1;
    for (int i = 1; i < len; i++) {
        if (word[i] == word[i - 1]) {
            count++;
        } else {
            char_block[block_size++] = count;
            count = 1;
        }
    }
    char_block[block_size++] = count;

    long long total = 1;
    for (int i = 0; i < block_size; i++) {
        total = (total * char_block[i]) % MOD;
    }

    if (k <= block_size) {
        free(char_block);
        return (int)total;
    }

    long long* dp = (long long*)calloc(k, sizeof(long long));
    dp[0] = 1;

    for (int i = 0; i < block_size; i++) {
        int num = char_block[i];
        long long* newDp = (long long*)calloc(k, sizeof(long long));
        long long sum = 0;
        
        for (int s = 0; s < k; ++s) {
            if (s > 0)
                sum = (sum + dp[s - 1]) % MOD;
            if (s > num)
                sum = (sum - dp[s - num - 1] + MOD) % MOD;
            newDp[s] = sum;
        }
        
        free(dp);
        dp = newDp;
    }

    long long invalid = 0;
    for (int s = block_size; s < k; ++s) {
        invalid = (invalid + dp[s]) % MOD;
    }

    free(char_block);
    free(dp);

    return (int)((total - invalid + MOD) % MOD);
}