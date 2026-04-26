int findLucky(int* arr, int arrSize) {
    int freq[501] = {0}, xMax = 0;
    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]]++;
        xMax = arr[i] > xMax ? arr[i] : xMax;
    }
    for (int x = xMax; x >= 1; x--) {
        if (freq[x] == x)
            return x;
    }
    return -1;
}