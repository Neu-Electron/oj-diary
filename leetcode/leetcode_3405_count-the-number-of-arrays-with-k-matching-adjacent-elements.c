#define MOD 1000000007LL
#define MAX_N 100000

static int preprocessed = 0;
static long long fact[MAX_N + 1];
static long long inv_fact[MAX_N + 1];

long long pow_mod(long long base, long long exp, long long mod);

int countGoodArrays(int n, int m, int k) {
    if (!preprocessed) {
        fact[0] = 1;
        for (int i = 1; i <= MAX_N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        inv_fact[MAX_N] = pow_mod(fact[MAX_N], MOD - 2, MOD);
        for (int i = MAX_N - 1; i >= 0; i--) {
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
        }
        preprocessed = 1;
    }

    if (k < 0 || k > n - 1) {
        return 0;
    }

    long long comb = fact[n - 1] * inv_fact[k] % MOD;
    comb = comb * inv_fact[n - 1 - k] % MOD;

    long long power = pow_mod(m - 1, n - 1 - k, MOD);
    long long ans = 1;
    ans = ans * (m % MOD) % MOD;
    ans = ans * power % MOD;
    ans = ans * comb % MOD;
    return (int)ans;
}

long long pow_mod(long long base, long long exp, long long mod) {
    base %= mod;
    if (base == 0) {
        return exp == 0 ? 1 : 0;
    }
    long long res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}