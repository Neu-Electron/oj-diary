int maximumDifference(int* nums, int numsSize) {
    int max_difference = -1;
    int l_min = 1000000000; // 相当于 1e9
    int r_max = -1;
    
    for (int l = 0, r = numsSize - 1; l < r; l++) {
        if (nums[l] < l_min) l_min = nums[l];
        
        while (l < r && nums[l + 1] > nums[l]) {
            l++;
            int diff = nums[l] - l_min;
            if (diff > max_difference) max_difference = diff;
        }
        
        if (nums[r] > r_max) r_max = nums[r];
        
        while (l < r && nums[r - 1] < nums[r]) {
            r--;
            int diff = nums[r] - r_max;
            if (diff > max_difference) max_difference = diff;
        }
        
        int diff = r_max - l_min;
        if (diff > max_difference) max_difference = diff;
    }

    return max_difference == 0 ? -1 : max_difference;
}