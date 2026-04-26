int* findKDistantIndices(int* nums, int numsSize, int key, int k, int* returnSize) {
    int* res = (int*)malloc(numsSize * sizeof(int));
    int pos = 0;
    int r = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == key) {
            int l = (r > (i - k)) ? r : (i - k);
            int current_upper = i + k;
            if (current_upper >= numsSize) {
                current_upper = numsSize - 1;
            }
            for (int j = l; j <= current_upper; j++) {
                res[pos++] = j;
            }
            r = current_upper + 1;
        }
    }

    *returnSize = pos;
    return res;
}