int furthestDistanceFromOrigin(char* moves) {
    int L = 0, R = 0, B = 0;
    int len = strlen(moves);
    for (int i = 0; i < len; i++) {
        char c = moves[i];
        if (c == 'L') {
            L++;
        } else if (c == 'R') {
            R++;
        } else {
            B++;
        }
    }
    return abs(L - R) + B;
}