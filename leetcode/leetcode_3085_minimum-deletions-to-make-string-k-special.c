int minimumDeletions(char* word, int k) {
    int cnt[26] = {0};
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        cnt[c - 'a']++;
    }

    int max_f = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > max_f) {
            max_f = cnt[i];
        }
    }

    int ans = strlen(word);

    for (int x = 1; x <= max_f + 1; x++) {
        int deletions = 0;
        for (int i = 0; i < 26; i++) {
            int f = cnt[i];
            if (f == 0)
                continue;
            if (f < x) {
                deletions += f;
            } else if (f > x + k) {
                deletions += f - (x + k);
            }
        }
        if (deletions < ans) {
            ans = deletions;
        }
    }
    return ans;
}