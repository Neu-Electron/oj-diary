#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Element;

int compareValueDesc(const void* a, const void* b) {
    Element* x = (Element*)a;
    Element* y = (Element*)b;
    if (x->value > y->value)
        return -1;
    else if (x->value < y->value)
        return 1;
    else
        return 0;
}

int compareIndexAsc(const void* a, const void* b) {
    Element* x = (Element*)a;
    Element* y = (Element*)b;
    return x->index - y->index;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize) {
    if (k == 0 || numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    if (k == numsSize) {
        *returnSize = k;
        int* result = (int*)malloc(k * sizeof(int));
        for (int i = 0; i < k; i++) {
            result[i] = nums[i];
        }
        return result;
    }
    int n = numsSize;
    Element* elements = (Element*)malloc(n * sizeof(Element));
    for (int i = 0; i < n; i++) {
        elements[i].value = nums[i];
        elements[i].index = i;
    }
    qsort(elements, n, sizeof(Element), compareValueDesc);
    qsort(elements, k, sizeof(Element), compareIndexAsc);
    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        result[i] = elements[i].value;
    }
    *returnSize = k;
    free(elements);
    return result;
}