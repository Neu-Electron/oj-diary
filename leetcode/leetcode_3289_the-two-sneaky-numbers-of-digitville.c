/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    int n = numsSize - 2;
    int* count = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }
    
    int* result = (int*)malloc(2 * sizeof(int));
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (count[i] == 2) {
            result[idx++] = i;
        }
    }
    
    *returnSize = 2;
    free(count);
    return result;
}