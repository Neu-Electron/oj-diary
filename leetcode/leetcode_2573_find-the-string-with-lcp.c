static inline char* get_empty_string(void) {
    char* empty = (char*)malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
}

char* findTheString(int** lcp, int lcpSize, int* lcpColSize) {
    int n = lcpSize;
    if (n == 0) {
        return get_empty_string();
    }
    
    char* word = (char*)malloc((n + 1) * sizeof(char));
    if (!word) return get_empty_string();
    memset(word, 0, (n + 1) * sizeof(char));
    
    char current = 'a';
    
    for (int i = 0; i < n; i++) {
        if (word[i] == '\0') {
            if (current > 'z') {
                free(word);
                return get_empty_string();
            }
            word[i] = current;
            for (int j = i + 1; j < n; j++) {
                if (lcp[i][j] > 0) {
                    word[j] = word[i];
                }
            }
            current++;
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (word[i] != word[j]) {
                if (lcp[i][j] != 0) {
                    free(word);
                    return get_empty_string();
                }
            } else {
                if (i == n - 1 || j == n - 1) {
                    if (lcp[i][j] != 1) {
                        free(word);
                        return get_empty_string();
                    }
                } else {
                    if (lcp[i][j] != lcp[i + 1][j + 1] + 1) {
                        free(word);
                        return get_empty_string();
                    }
                }
            }
        }
    }
    
    word[n] = '\0';
    return word;
}