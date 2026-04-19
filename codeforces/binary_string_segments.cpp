#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n{0};
    std::string s;
    std::cin >> n >> s;
    std::vector<int> ones;
    for (int i = 0; i < n; i++)
        if (s[i] == '1')
            ones.push_back(i);

    if (ones.empty()) {
        std::cout << "0 0\n";
        return;
    }

    int max_ans{0}, min_ans{0};
    int start{ones[0]};
    int prev{ones[0]};

    for (size_t i = 1; i < ones.size(); i++) {
        int cur = ones[i];
        if (cur - prev <= 2) {
            prev = cur;
        } else {
            int length = prev - start + 1;
            max_ans += length;
            min_ans += (length + 1) / 2;
            start = cur;
            prev = cur;
        }
    }

    int length = prev - start + 1;
    max_ans += length;
    min_ans += (length + 1) / 2;

    std::cout << min_ans << " " << max_ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int t{0};
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}