int possibleStringCount(char* word) {
    int count = 1;
    int len = strlen(word);
    for (int i = 0; i < len - 1; i++) {
        if (word[i] == word[i + 1]) {
            count++;
        }
    }
    return count;
}