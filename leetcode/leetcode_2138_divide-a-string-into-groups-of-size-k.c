/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** divideString(char* s, int k, char fill, int* returnSize) {
    int n = strlen(s);
    int groups = (n + k - 1) / k;
    *returnSize = groups;
    char** result = (char**)malloc(groups * sizeof(char*));
    for (int i = 0; i < groups; ++i) {
        result[i] = (char*)malloc((k + 1) * sizeof(char));
        int start = i * k;
        int len = (start + k <= n) ? k : (n - start);
        strncpy(result[i], s + start, len);
        if (len < k) {
            for (int j = len; j < k; ++j) {
                result[i][j] = fill;
            }
        }
        result[i][k] = '\0';
    }
    return result;
}