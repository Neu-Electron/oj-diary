int maxDistance(char* s, int k) {
    int n = strlen(s);
    int ans = 0;
    int cnt_xy = 0;
    int cnt_x_y = 0;
    int cnt_neg_xy = 0;
    int cnt_neg_x_y = 0;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        switch (c) {
        case 'N':
            cnt_x_y++;
            cnt_neg_x_y++;
            break;
        case 'S':
            cnt_xy++;
            cnt_neg_xy++;
            break;
        case 'E':
            cnt_x_y++;
            cnt_neg_xy++;
            break;
        case 'W':
            cnt_xy++;
            cnt_neg_x_y++;
            break;
        }

        int len = i + 1;
        int val1 = (cnt_xy <= k) ? len : len - 2 * (cnt_xy - k);
        int val2 = (cnt_x_y <= k) ? len : len - 2 * (cnt_x_y - k);
        int val3 = (cnt_neg_xy <= k) ? len : len - 2 * (cnt_neg_xy - k);
        int val4 = (cnt_neg_x_y <= k) ? len : len - 2 * (cnt_neg_x_y - k);
        int curMax = val1;
        if (val2 > curMax)
            curMax = val2;
        if (val3 > curMax)
            curMax = val3;
        if (val4 > curMax)
            curMax = val4;
        if (curMax > ans)
            ans = curMax;
    }
    return ans;
}