int longestSubsequence(char* s, int k) {
    int length = strlen(s);
    if (length == 1) {
        if (s[0] == '1' && k < 1)
            return 0;
        else
            return 1;
    }
    int n = length;
    long long dight = 0, pow = 1;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            count++;
    }

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') {
            if (dight + pow > k)
                continue;
            dight += pow;
            count++;
        }
        pow <<= 1;
        if (pow > k)
            break;
    }

    return count;
}