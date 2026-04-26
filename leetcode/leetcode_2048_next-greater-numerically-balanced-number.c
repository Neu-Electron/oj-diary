#define MAX_BALANCED_NUMBERS 10000

int balanced_numbers[MAX_BALANCED_NUMBERS];
int balanced_count = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generate_permutations(int* digits, int start, int end) {
    if (start == end) {
        if (digits[0] == 0)
            return;
        int num = 0;
        for (int i = 0; i <= end; i++) {
            num = num * 10 + digits[i];
        }
        int found = 0;
        for (int i = 0; i < balanced_count; i++) {
            if (balanced_numbers[i] == num) {
                found = 1;
                break;
            }
        }
        if (!found) {
            balanced_numbers[balanced_count++] = num;
        }
        return;
    }
    for (int i = start; i <= end; i++) {
        if (i != start && digits[i] == digits[start])
            continue;

        swap(&digits[start], &digits[i]);
        generate_permutations(digits, start + 1, end);
        swap(&digits[start], &digits[i]);
    }
}

void dfs(int* chosen, int chosen_count, int total_len) {
    if (total_len > 7)
        return;

    if (chosen_count > 0) {
        int digits[15];
        int idx = 0;
        for (int i = 0; i < chosen_count; i++) {
            int d = chosen[i];
            for (int j = 0; j < d; j++) {
                digits[idx++] = d;
            }
        }
        generate_permutations(digits, 0, total_len - 1);
    }
    int start = (chosen_count == 0) ? 1 : chosen[chosen_count - 1] + 1;
    for (int d = start; d <= 9; d++) {
        if (total_len + d <= 7) {
            chosen[chosen_count] = d;
            dfs(chosen, chosen_count + 1, total_len + d);
        }
    }
}

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int binary_search(int n) {
    int left = 0, right = balanced_count - 1;
    int result = balanced_numbers[balanced_count - 1];

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (balanced_numbers[mid] > n) {
            result = balanced_numbers[mid];
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

int nextBeautifulNumber(int n) {
    if (balanced_count == 0) {
        int chosen[10] = {0};
        dfs(chosen, 0, 0);
        qsort(balanced_numbers, balanced_count, sizeof(int), compare);
    }

    return binary_search(n);
}