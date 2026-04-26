#include <stdint.h>

int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    const int MOD = 1000000007;
    
    for (int i = 0; i < queriesSize; i++) {
        int* row = queries[i];
        int start = row[0];
        int end = row[1];
        int step = row[2];
        int multiplier = row[3];
        
        for (int idx = start; idx <= end; idx += step) {
            nums[idx] = (int)(((long long)nums[idx] * multiplier) % MOD);
        }
    }
    
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }
    return result;
}