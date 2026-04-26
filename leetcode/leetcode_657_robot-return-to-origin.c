bool judgeCircle(char* moves) {
    int count_w = 0;
    int count_s = 0;
    
    while (*moves != '\0') {
        switch (*moves) {
            case 'U': count_w++; break;
            case 'D': count_w--; break;
            case 'L': count_s++; break;
            case 'R': count_s--; break;
        }
        moves++;
    }
    
    return count_s == 0 && count_w == 0;
}