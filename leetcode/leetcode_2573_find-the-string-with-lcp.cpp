#include <bits/stdc++.h>

class Solution {
  public:
    std::string findTheString(const std::vector<std::vector<int>> &lcp) {
        const int n = lcp.size();
        if (n == 0)
            return "";

        std::string word(n, '\0');
        char current = 'a';

        for (int i = 0; i < n; i++) {
            if (word[i] == '\0') {
                if (current > 'z')
                    return "";

                word[i] = current;
                const auto &lcp_i = lcp[i];
                for (int j = i + 1; j < n; ++j) {
                    if (lcp_i[j] > 0) {
                        word[j] = word[i];
                    }
                }
                ++current;
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            const auto &lcp_i = lcp[i];
            const char word_i = word[i];

            for (int j = n - 1; j >= 0; j--) {
                const int expected = lcp_i[j];

                if (word_i != word[j]) {
                    if (expected != 0)
                        return "";
                } else {
                    if (i == n - 1 || j == n - 1) {
                        if (expected != 1)
                            return "";
                    } else {
                        const int next_val = lcp[i + 1][j + 1];
                        if (expected != next_val + 1)
                            return "";
                    }
                }
            }
        }

        return word;
    }
};