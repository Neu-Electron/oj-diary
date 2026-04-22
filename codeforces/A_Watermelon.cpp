#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int w;
    std::cin >> w;

    if (w & 1 || w == 2) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES";
    return 0;
}