#include <bits/stdc++.h>

int sumOfDigits(int n) {
    int sum{0};
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n{};
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int num{0};
        std::cin >> num;
        int ans{0};
        for (int y = num; y <= num + 90; ++y) {
            if (y - sumOfDigits(y) == num) {
                ans++;
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
}