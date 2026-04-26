typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} HashTable;

int findLHS(int* nums, int numsSize) {
    HashTable* map = NULL;
    int max_length = 0;

    for (int i = 0; i < numsSize; i++) {
        HashTable* tmp;
        HASH_FIND_INT(map, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (HashTable*)malloc(sizeof(HashTable));
            tmp->key = nums[i];
            tmp->value = 1;
            HASH_ADD_INT(map, key, tmp);
        } else {
            tmp->value++;
        }
    }

    HashTable *current, *tmp;
    HASH_ITER(hh, map, current, tmp) {
        int next_key = current->key + 1;
        HashTable* next;
        HASH_FIND_INT(map, &next_key, next);
        if (next != NULL) {
            int current_length = current->value + next->value;
            if (current_length > max_length) {
                max_length = current_length;
            }
        }
    }
    HASH_ITER(hh, map, current, tmp) {
        HASH_DEL(map, current);
        free(current);
    }

    return max_length;
}