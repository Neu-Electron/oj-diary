typedef struct {
    int key;
    int* indices;
    int size;
    int capacity;
    UT_hash_handle hh;
} MapEntry;

typedef struct {
    long long sum;
    int size;
} PrefixInfo;

void addIndex(MapEntry** map, int key, int index) {
    MapEntry* entry = NULL;
    HASH_FIND_INT(*map, &key, entry);
    
    if (!entry) {
        entry = (MapEntry*)malloc(sizeof(MapEntry));
        entry->key = key;
        entry->size = 0;
        entry->capacity = 4;
        entry->indices = (int*)malloc(entry->capacity * sizeof(int));
        HASH_ADD_INT(*map, key, entry);
    }
    
    if (entry->size >= entry->capacity) {
        entry->capacity *= 2;
        entry->indices = (int*)realloc(entry->indices, entry->capacity * sizeof(int));
    }
    
    entry->indices[entry->size++] = index;
}

long long* distance(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    long long* ans = (long long*)malloc(numsSize * sizeof(long long));
    
    MapEntry* map = NULL;
    
    // Build map: value -> list of indices
    for (int i = 0; i < numsSize; i++) {
        addIndex(&map, nums[i], i);
    }
    
    // Process each group
    MapEntry* entry, *tmp;
    HASH_ITER(hh, map, entry, tmp) {
        int m = entry->size;
        int* pos = entry->indices;
        
        // Calculate total sum of indices
        long long sum = 0;
        for (int i = 0; i < m; i++) {
            sum += pos[i];
        }
        
        long long leftSum = 0;
        for (int i = 0; i < m; i++) {
            long long rightSum = sum - leftSum - pos[i];
            
            long long left = (long long)pos[i] * i - leftSum;
            long long right = rightSum - (long long)pos[i] * (m - i - 1);
            
            ans[pos[i]] = left + right;
            
            leftSum += pos[i];
        }
    }
    
    // Free hash table memory
    HASH_ITER(hh, map, entry, tmp) {
        HASH_DEL(map, entry);
        free(entry->indices);
        free(entry);
    }
    
    return ans;
}