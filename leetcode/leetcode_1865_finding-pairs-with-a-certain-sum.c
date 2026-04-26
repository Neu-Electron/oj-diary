typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} HashEntry;

typedef struct {
    int* nums1;
    int nums1Size;
    int* nums2;
    int nums2Size;
    HashEntry* cnt;
} FindSumPairs;

FindSumPairs* findSumPairsCreate(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    FindSumPairs* obj = (FindSumPairs*)malloc(sizeof(FindSumPairs));
    if (!obj) return NULL;
    obj->nums1 = (int*)malloc(nums1Size * sizeof(int));
    if (!obj->nums1) {
        free(obj);
        return NULL;
    }
    memcpy(obj->nums1, nums1, nums1Size * sizeof(int));
    obj->nums1Size = nums1Size;
    obj->nums2 = (int*)malloc(nums2Size * sizeof(int));
    if (!obj->nums2) {
        free(obj->nums1);
        free(obj);
        return NULL;
    }
    memcpy(obj->nums2, nums2, nums2Size * sizeof(int));
    obj->nums2Size = nums2Size;
    obj->cnt = NULL;
    for (int i = 0; i < nums2Size; i++) {
        HashEntry* entry = NULL;
        HASH_FIND_INT(obj->cnt, &nums2[i], entry);
        if (entry) {
            entry->value++;
        } else {
            entry = (HashEntry*)malloc(sizeof(HashEntry));
            entry->key = nums2[i];
            entry->value = 1;
            HASH_ADD_INT(obj->cnt, key, entry);
        }
    }
    
    return obj;
}

void findSumPairsAdd(FindSumPairs* obj, int index, int val) {
    if (index < 0 || index >= obj->nums2Size) return;
    int oldVal = obj->nums2[index];
    HashEntry* entry = NULL;
    HASH_FIND_INT(obj->cnt, &oldVal, entry);
    if (entry) {
        entry->value--;
        if (entry->value == 0) {
            HASH_DEL(obj->cnt, entry);
            free(entry);
        }
    }
    obj->nums2[index] += val;
    int newVal = obj->nums2[index];
    HASH_FIND_INT(obj->cnt, &newVal, entry);
    if (entry) {
        entry->value++;
    } else {
        entry = (HashEntry*)malloc(sizeof(HashEntry));
        entry->key = newVal;
        entry->value = 1;
        HASH_ADD_INT(obj->cnt, key, entry);
    }
}

int findSumPairsCount(FindSumPairs* obj, int tot) {
    int count = 0;
    HashEntry* entry = NULL;
    
    for (int i = 0; i < obj->nums1Size; i++) {
        int target = tot - obj->nums1[i];
        HASH_FIND_INT(obj->cnt, &target, entry);
        if (entry) {
            count += entry->value;
        }
    }
    
    return count;
}

void findSumPairsFree(FindSumPairs* obj) {
    if (!obj) return;
    HashEntry *current, *tmp;
    HASH_ITER(hh, obj->cnt, current, tmp) {
        HASH_DEL(obj->cnt, current);
        free(current);
    }
    free(obj->nums1);
    free(obj->nums2);
    free(obj);
}

/**
 * Your FindSumPairs struct will be instantiated and called as such:
 * FindSumPairs* obj = findSumPairsCreate(nums1, nums1Size, nums2, nums2Size);
 * findSumPairsAdd(obj, index, val);
 
 * int param_2 = findSumPairsCount(obj, tot);
 
 * findSumPairsFree(obj);
*/