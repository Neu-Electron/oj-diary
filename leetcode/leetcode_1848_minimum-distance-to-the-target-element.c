int getMinDistance(int* nums, int numsSize, int target, int start) {
    int left = start;
    int right = start;
    
    while (left >= 0 || right < numsSize) {
        if (left >= 0 && nums[left] == target) {
            return start - left;
        }
        if (right < numsSize && nums[right] == target) {
            return right - start;
        }
        left--;
        right++;
    }
    
    return -1;
}