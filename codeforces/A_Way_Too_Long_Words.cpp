#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n{0};
    std::cin >> n;

    std::vector<std::string> strs;
    for (int i = 0; i < n; i++) {
        std::string temp;
        std::cin >> temp;
        int str_n = temp.size();
        if (str_n > 10) {
            temp = temp[0] + std::to_string(str_n - 2) + temp[str_n - 1];
        }
        std::cout << temp << '\n';
    }
    return 0;
}