#include <bits/stdc++.h>

// x = 2a + 3b + 4c
// y = a - c
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n{};
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int x{0}, y{0};
        std::cin >> x >> y;
        if (x >= 2 && x - 2 * y >= 0 && (x - 2 * y) % 3 == 0 && (y >= 0 || x >= -4 * y)) {
            std::cout << "YES\n";
            continue;
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}