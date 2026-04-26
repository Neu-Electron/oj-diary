#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxDistance(int* colors, int colorsSize) {
    int ans = 0;
    for (int i = 0; i < colorsSize; i++) {
        for (int j = i + 1; j < colorsSize; j++) {
            if (colors[i] == colors[j]) {
                continue;
            } else {
                ans = MAX(ans, j - i);
            }
        }
    }
    return ans;
}