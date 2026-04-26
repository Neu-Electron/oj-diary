#define MOD 1000000007

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int numSubseq(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), compare);

    int power[numsSize];
    power[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        power[i] = (power[i - 1] * 2) % MOD;
    }

    int left = 0, right = numsSize - 1;
    int result = 0;

    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            result = (result + power[right - left]) % MOD;
            left++;
        } else {
            right--;
        }
    }

    return result;
}