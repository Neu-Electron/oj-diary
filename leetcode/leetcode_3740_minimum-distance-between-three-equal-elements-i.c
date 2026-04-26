int minimumDistance(int* nums, int numsSize) {
    int result = INT_MAX;
    int temp = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            for (int k = j + 1; k < numsSize; k++) {
                if (nums[i] == nums[j] && nums[j] == nums[k]) {
                    temp = abs(i - j) + abs(j - k) + abs(k - i);
                    if (temp < result) {
                        result = temp;
                    }
                }
            }
        }
    }
    return result == INT_MAX ? -1 : result;
}