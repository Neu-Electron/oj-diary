#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return *(long long*)a - *(long long*)b;
}

int lower_bound(long long* arr, int size, long long target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int upper_bound(long long* arr, int size, long long target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    if (numsSize == 0)
        return 0;
    long long* sorted_nums = (long long*)malloc(numsSize * sizeof(long long));
    for (int i = 0; i < numsSize; i++) {
        sorted_nums[i] = (long long)nums[i];
    }
    qsort(sorted_nums, numsSize, sizeof(long long), cmp);
    long long* events = (long long*)malloc(3 * numsSize * sizeof(long long));
    int event_count = 0;

    for (int i = 0; i < numsSize; i++) {
        events[event_count++] = sorted_nums[i];
        events[event_count++] = sorted_nums[i] - k;
        events[event_count++] = sorted_nums[i] + k;
    }
    qsort(events, event_count, sizeof(long long), cmp);
    int unique_count = 0;
    for (int i = 0; i < event_count; i++) {
        if (i == 0 || events[i] != events[i - 1]) {
            events[unique_count++] = events[i];
        }
    }
    int* count = (int*)calloc(unique_count, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        int pos = lower_bound(events, unique_count, (long long)nums[i]);
        if (pos < unique_count && events[pos] == nums[i]) {
            count[pos]++;
        }
    }

    int l = 0, r = 0;
    long long sum_count = 0;
    int ans = 0;

    for (int i = 0; i < unique_count; i++) {
        long long pos = events[i];

        while (r < unique_count && events[r] <= pos + k) {
            sum_count += count[r];
            r++;
        }

        while (l < unique_count && events[l] < pos - k) {
            sum_count -= count[l];
            l++;
        }

        int same = count[i];
        int need_ops = sum_count - same;
        int cand = same + (need_ops < numOperations ? need_ops : numOperations);
        if (cand > ans) {
            ans = cand;
        }
    }

    free(sorted_nums);
    free(events);
    free(count);

    return ans;
}