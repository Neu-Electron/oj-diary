int minMaxDifference(int num) {
    char s[20];
    sprintf(s, "%d", num);
    int max_val = num;
    int min_val = num;
    int len = strlen(s);
    int digits[10] = {0};
    for (int i = 0; i < len; i++) {
        digits[s[i] - '0'] = 1;
    }
    for (int d = 0; d < 10; d++) {
        if (digits[d]) {
            char candidate[20];
            strcpy(candidate, s);
            for (int i = 0; i < len; i++) {
                if (candidate[i] - '0' == d) {
                    candidate[i] = '9';
                }
            }
            int val = atoi(candidate);
            if (val > max_val) {
                max_val = val;
            }
        }
    }
    for (int d = 0; d < 10; d++) {
        if (digits[d]) {
            char candidate[20];
            strcpy(candidate, s);
            for (int i = 0; i < len; i++) {
                if (candidate[i] - '0' == d) {
                    candidate[i] = '0';
                }
            }
            int val = atoi(candidate);
            if (val < min_val) {
                min_val = val;
            }
        }
    }

    return max_val - min_val;
}