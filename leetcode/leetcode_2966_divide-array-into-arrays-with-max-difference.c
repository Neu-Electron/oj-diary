int compare(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int** divideArray(int* nums, int numsSize, int k, int* returnSize,
                  int** returnColumnSizes) {
    if (numsSize % 3 != 0) {
        *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), compare);
    for (int i = 0; i < numsSize; i += 3) {
        if (i + 2 < numsSize && nums[i + 2] - nums[i] > k) {
            *returnSize = 0;
            return NULL;
        }
    }
    int groupCount = numsSize / 3;
    *returnSize = groupCount;
    int** result = (int**)malloc(groupCount * sizeof(int*));
    *returnColumnSizes = (int*)malloc(groupCount * sizeof(int));
    for (int i = 0; i < groupCount; i++) {
        result[i] = (int*)malloc(3 * sizeof(int));
        (*returnColumnSizes)[i] = 3;
    }
    for (int i = 0; i < numsSize; i++) {
        int groupIndex = i / 3;
        int inGroupIndex = i % 3;
        result[groupIndex][inGroupIndex] = nums[i];
    }
    return result;
}