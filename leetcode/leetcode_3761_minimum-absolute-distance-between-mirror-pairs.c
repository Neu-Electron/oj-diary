
int reverse(int num) {
    int ans = 0;
    while (num > 0) {
        ans = ans * 10 + num % 10;
        num /= 10;
    }
    return ans;
}

typedef struct {
    int key;
    int value;
} Entry;

int find(Entry* table, int size, int key) {
    int h = key % size;
    while (table[h].key != 0 && table[h].key != key) {
        h = (h + 1) % size;
    }
    return (table[h].key == key) ? h : -1;
}

void insert(Entry* table, int size, int key, int value) {
    int h = key % size;
    while (table[h].key != 0 && table[h].key != key) {
        h = (h + 1) % size;
    }
    table[h].key = key;
    table[h].value = value;
}

int minMirrorPairDistance(int* nums, int numsSize) {
    if (numsSize < 2)
        return -1;

    const int HASH_SIZE = 300007;
    Entry* table = (Entry*)calloc(HASH_SIZE, sizeof(Entry));
    if (table == NULL)
        return -1;

    int ans = INT_MAX;

    for (int i = 0; i < numsSize; ++i) {
        int key = nums[i];
        int pos = find(table, HASH_SIZE, key);
        if (pos != -1) {
            int dist = i - table[pos].value;
            if (dist < ans)
                ans = dist;
        }

        int rev = reverse(nums[i]);
        insert(table, HASH_SIZE, rev, i);
    }

    free(table);
    return (ans == INT_MAX) ? -1 : ans;
}