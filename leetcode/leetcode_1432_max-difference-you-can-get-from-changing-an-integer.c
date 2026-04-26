#define REPLACE(x, y, z)                                                       \
    do {                                                                       \
        for (int k = 0; x[k]; k++) {                                           \
            if (x[k] == (y))                                                   \
                x[k] = (z);                                                    \
        }                                                                      \
    } while (0)

int maxDiff(int num) {
    char str_num[12];
    sprintf(str_num, "%d", num);
    char max_str[12];
    strcpy(max_str, str_num);
    int i;
    for (i = 0; max_str[i]; i++) {
        if (max_str[i] != '9')
            break;
    }
    if (i < strlen(max_str)) {
        char c = max_str[i];
        REPLACE(max_str, c, '9');
    }

    char min_str[12];
    strcpy(min_str, str_num);
    if (min_str[0] != '1') {
        char c = min_str[0];
        REPLACE(min_str, c, '1');
    } else {
        int found = -1;
        for (int j = 1; min_str[j]; j++) {
            if (min_str[j] != '0' && min_str[j] != '1') {
                found = j;
                break;
            }
        }
        if (found != -1) {
            char c = min_str[found];
            REPLACE(min_str, c, '0');
        }
    }

    int max_val = atoi(max_str);
    int min_val = atoi(min_str);
    return max_val - min_val;
}