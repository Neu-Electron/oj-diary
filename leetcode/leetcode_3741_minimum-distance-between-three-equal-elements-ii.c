#include <limits.h>

typedef struct {
    int num;
    int count;
    UT_hash_handle hh;
} CountEntry;

typedef struct {
    int num;
    int* indices;
    int size;
    int capacity;
    UT_hash_handle hh;
} IndexEntry;

int minimumDistance(int* nums, int numsSize) {

    CountEntry* count_map = NULL;
    for (int i = 0; i < numsSize; i++) {
        CountEntry* entry = NULL;
        HASH_FIND_INT(count_map, &nums[i], entry);
        if (entry == NULL) {
            entry = (CountEntry*)malloc(sizeof(CountEntry));
            entry->num = nums[i];
            entry->count = 1;
            HASH_ADD_INT(count_map, num, entry);
        } else {
            entry->count++;
        }
    }

    IndexEntry* index_map = NULL;
    for (int i = 0; i < numsSize; i++) {
        CountEntry* count_entry = NULL;
        HASH_FIND_INT(count_map, &nums[i], count_entry);

        if (count_entry != NULL && count_entry->count >= 3) {
            IndexEntry* index_entry = NULL;
            HASH_FIND_INT(index_map, &nums[i], index_entry);

            if (index_entry == NULL) {

                index_entry = (IndexEntry*)malloc(sizeof(IndexEntry));
                index_entry->num = nums[i];
                index_entry->size = 0;
                index_entry->capacity = 4;
                index_entry->indices =
                    (int*)malloc(sizeof(int) * index_entry->capacity);
                HASH_ADD_INT(index_map, num, index_entry);
            }

            if (index_entry->size >= index_entry->capacity) {
                index_entry->capacity *= 2;
                index_entry->indices = (int*)realloc(
                    index_entry->indices, sizeof(int) * index_entry->capacity);
            }

            index_entry->indices[index_entry->size++] = i;
        }
    }

    int min_dist = INT_MAX;
    IndexEntry *cur, *tmp;
    HASH_ITER(hh, index_map, cur, tmp) {
        int* indices = cur->indices;
        int size = cur->size;

        for (int first = 0; first + 2 < size; first++) {
            int third = first + 2;
            int dist = 2 * (indices[third] - indices[first]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
    }

    CountEntry *count_cur, *count_tmp;
    HASH_ITER(hh, count_map, count_cur, count_tmp) {
        HASH_DEL(count_map, count_cur);
        free(count_cur);
    }

    HASH_ITER(hh, index_map, cur, tmp) {
        HASH_DEL(index_map, cur);
        free(cur->indices);
        free(cur);
    }

    return (min_dist == INT_MAX) ? -1 : min_dist;
}