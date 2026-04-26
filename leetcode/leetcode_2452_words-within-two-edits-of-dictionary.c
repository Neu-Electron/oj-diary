char** twoEditWords(char** queries, int queriesSize, char** dictionary,
                    int dictionarySize, int* returnSize) {

    int word_len = strlen(queries[0]);

    char** result = (char**)malloc(queriesSize * sizeof(char*));
    int result_idx = 0;

    for (int i = 0; i < queriesSize; i++) {
        char* query_word = queries[i];
        int found = 0;

        for (int j = 0; j < dictionarySize; j++) {
            char* dict_word = dictionary[j];
            int diff_count = 0;

            for (int k = 0; k < word_len; k++) {
                if (query_word[k] != dict_word[k]) {
                    diff_count++;
                }
                if (diff_count > 2) {
                    break;
                }
            }

            if (diff_count <= 2) {

                result[result_idx] =
                    (char*)malloc((word_len + 1) * sizeof(char));
                strcpy(result[result_idx], query_word);
                result_idx++;
                found = 1;
                break;
            }
        }
    }

    *returnSize = result_idx;
    return result;
}