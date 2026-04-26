int countValidSelections(int* nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        total += nums[i];
    }

    int count = 0;
    int left = 0, right = total;

    for (int i = 0; i < numsSize; i++) {
        left += nums[i];
        right -= nums[i];

        if (nums[i] != 0)
            continue;

        if (left == right) {
            count += 2;
        } else if (abs(left - right) == 1) {
            count += 1;
        }
    }

    return count;
}