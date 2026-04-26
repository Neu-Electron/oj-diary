int numberOfBeams(char** bank, int bankSize) {
    int prev = 0, total = 0;

    for (int i = 0; i < bankSize; i++) {
        int devices = 0;

        for (int j = 0; bank[i][j] != '\0'; j++) {
            if (bank[i][j] == '1')
                devices++;
        }

        if (devices > 0) {
            total += prev * devices;
            prev = devices;
        }
    }
    return total;
}