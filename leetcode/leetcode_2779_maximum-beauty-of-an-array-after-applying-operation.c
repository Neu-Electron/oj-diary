#include <stdlib.h> 

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maximumBeauty(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    int left = 0;
    int count = 0;
    for (int right = 0; right < numsSize; right++) {
        while (nums[right] - nums[left] > 2 * k) {
            left++;
        }
        int current = right - left + 1;
        if (current > count) {
            count = current;
        }
    }
    return count;
}