int closestTarget(char** words, int wordsSize, char* target, int startIndex) {
    int ans = wordsSize;
    int n = wordsSize;

    for (int i = 0; i < n; ++i) {
        if (strcmp(words[i], target) == 0) {
            int dist = abs(i - startIndex);
            int ringDist = dist < n - dist ? dist : n - dist;
            if (ringDist < ans)
                ans = ringDist;
        }
    }

    return ans < n ? ans : -1;
}