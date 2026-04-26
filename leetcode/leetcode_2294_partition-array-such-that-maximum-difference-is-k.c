int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int partitionArray(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    int start_min = nums[0];
    int count = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] - start_min > k) {
            start_min = nums[i];
            count++;
        }
    }
    return count;
}