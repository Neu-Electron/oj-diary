int mirrorDistance(int n) {
    int an = n;
    while( (n % 10 == 0) && n!=0) {
        n /= 10;
    }

    int result = 0;
    while (n > 0) {
        int dight = n % 10;
        result = result * 10 + dight;
        n /= 10;
    }
    return abs(an - result);
}