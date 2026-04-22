#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int _n{0};
    std::cin >> _n;

    for (int i = 0; i < _n; i++) {
        int n{0}, w{0}, result{0};
        std::cin >> n >> w;
        result = n - static_cast<int>(n / w);
        std::cout << result << '\n';
    }
    return 0;
}