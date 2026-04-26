#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define ll long long

#define MUL(a, b)                                                              \
    ({                                                                         \
        ll _a = (a), _b = (b);                                                 \
        ((_a * _b) % MOD);                                                     \
    })

#define INIT_CAPACITY 16
#define GROW_CAPACITY(cap) ((cap) * 2)

#define PUSH_BACK(arr, size, cap, val)                                         \
    do {                                                                       \
        if ((size) >= (cap)) {                                                 \
            (cap) = GROW_CAPACITY(cap);                                        \
            (arr) = (__typeof__(arr))realloc((arr), (cap) * sizeof(*(arr)));   \
        }                                                                      \
        (arr)[(size)++] = (val);                                               \
    } while (0)

#define ALLOC(type, size) ((type*)malloc((size) * sizeof(type)))
#define CALLOC(type, size) ((type*)calloc((size), sizeof(type)))
#define FREE(ptr)                                                              \
    do {                                                                       \
        if (ptr) {                                                             \
            free(ptr);                                                         \
            (ptr) = NULL;                                                      \
        }                                                                      \
    } while (0)

#define FOR(i, start, end) for (__typeof__(start) i = (start); i < (end); i++)
#define FOR_STEP(i, start, end, step)                                          \
    for (__typeof__(start) i = (start); i <= (end); i += (step))

#define FILL(arr, start, end, val)                                             \
    do {                                                                       \
        for (int _i = (start); _i < (end); _i++) {                             \
            (arr)[_i] = (val);                                                 \
        }                                                                      \
    } while (0)

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

static inline int pow_mod(ll x, ll y) {
    ll res = 1;
    x %= MOD;
    for (; y; y >>= 1) {
        if (y & 1) {
            res = MUL(res, x);
        }
        x = MUL(x, x);
    }
    return (int)res;
}

typedef struct {
    int l, r, v;
} Query;

int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize,
                    int* queriesColSize) {
    int n = numsSize;
    int T = (int)sqrt(n);
    if (UNLIKELY(T < 1))
        T = 1;

    Query** groups = ALLOC(Query*, T);
    int* groupSizes = CALLOC(int, T);
    int* groupCaps = CALLOC(int, T);

    for (int i = 0; i < T; i++) {
        groupCaps[i] = INIT_CAPACITY;
        groups[i] = ALLOC(Query, groupCaps[i]);
    }

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        int k = queries[i][2];
        int v = queries[i][3];

        if (k < T) {
            Query q = {l, r, v};
            PUSH_BACK(groups[k], groupSizes[k], groupCaps[k], q);
        } else {
            for (int j = l; j <= r; j += k) {
                nums[j] = MUL(nums[j], v);
            }
        }
    }

    ll* dif = ALLOC(ll, n + T);

    for (int k = 1; k < T; k++) {
        if (UNLIKELY(groupSizes[k] == 0))
            continue;

        for (int i = 0; i < n + T; i++) {
            dif[i] = 1;
        }

        for (int i = 0; i < groupSizes[k]; i++) {
            Query q = groups[k][i];
            dif[q.l] = MUL(dif[q.l], q.v);

            int R = ((q.r - q.l) / k + 1) * k + q.l;
            if (LIKELY(R < n + T)) {
                dif[R] = MUL(dif[R], pow_mod(q.v, MOD - 2));
            }
        }

        for (int i = k; i < n; i++) {
            dif[i] = MUL(dif[i], dif[i - k]);
        }

#pragma GCC ivdep
        for (int i = 0; i < n; i++) {
            nums[i] = MUL(nums[i], dif[i]);
        }
    }

    int res = 0;
#pragma GCC ivdep
    for (int i = 0; i < n; i++) {
        res ^= nums[i];
    }

    for (int i = 0; i < T; i++) {
        FREE(groups[i]);
    }
    FREE(groups);
    FREE(groupSizes);
    FREE(groupCaps);
    FREE(dif);

    return res;
}