#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;

        bool has67 = false;

        for (int i = 0; i < n; i++) {
            int x;
            std::cin >> x;
            if (x == 67)
                has67 = true;
        }

        std::cout << (has67 ? "YES" : "NO") << "\n";
    }
    return 0;
}