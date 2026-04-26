long long count_products(int* nums1, int nums1Size, int* nums2, int nums2Size,
                         long long t) {
    long long count = 0;
    for (int i = 0; i < nums1Size; i++) {
        int num1 = nums1[i];
        if (num1 == 0) {
            if (t >= 0)
                count += nums2Size;
            continue;
        }

        int low = 0, high = nums2Size;
        while (low < high) {
            int mid = (low + high) / 2;
            long long prod = (long long)num1 * nums2[mid];
            if (prod <= t) {
                if (num1 > 0)
                    low = mid + 1;
                else
                    high = mid;
            } else {
                if (num1 > 0)
                    high = mid;
                else
                    low = mid + 1;
            }
        }
        count += (num1 > 0) ? low : (nums2Size - low);
    }
    return count;
}

long long kthSmallestProduct(int* nums1, int nums1Size, int* nums2,
                             int nums2Size, long long k) {
    long long left = -1e10, right = 1e10;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (count_products(nums1, nums1Size, nums2, nums2Size, mid) < k)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}