typedef struct {
    int key;
    int* indices;
    int size;
    int capacity;
    UT_hash_handle hh;
} NumHash;

void add_index(NumHash** hash, int num, int index) {
    NumHash* entry = NULL;
    HASH_FIND_INT(*hash, &num, entry);

    if (!entry) {
        entry = (NumHash*)malloc(sizeof(NumHash));
        entry->key = num;
        entry->indices = NULL;
        entry->size = 0;
        entry->capacity = 0;
        HASH_ADD_INT(*hash, key, entry);
    }

    if (entry->size >= entry->capacity) {
        entry->capacity = entry->capacity == 0 ? 4 : entry->capacity * 2;
        entry->indices =
            (int*)realloc(entry->indices, entry->capacity * sizeof(int));
    }

    entry->indices[entry->size++] = index;
}

int lower_bound(int* arr, int size, int target) {
    int left = 0, right = size - 1;
    int pos = size;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return pos;
}

int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize,
                  int* returnSize) {
    *returnSize = queriesSize;
    int* ans = (int*)malloc(queriesSize * sizeof(int));

    NumHash* hash = NULL;
    for (int i = 0; i < numsSize; i++) {
        add_index(&hash, nums[i], i);
    }

    for (int i = 0; i < queriesSize; i++) {
        int q = queries[i];
        int val = nums[q];

        NumHash* entry = NULL;
        HASH_FIND_INT(hash, &val, entry);

        if (!entry || entry->size == 1) {
            ans[i] = -1;
            continue;
        }

        int* indices = entry->indices;
        int m = entry->size;

        int pos = lower_bound(indices, m, q);

        int prev = indices[(pos - 1 + m) % m];
        int next = indices[(pos + 1) % m];

        int dist_next = (next - q + numsSize) % numsSize;
        int dist_prev = (q - prev + numsSize) % numsSize;

        ans[i] = dist_next < dist_prev ? dist_next : dist_prev;
    }

    NumHash *current, *tmp;
    HASH_ITER(hh, hash, current, tmp) {
        free(current->indices);
        HASH_DEL(hash, current);
        free(current);
    }

    return ans;
}