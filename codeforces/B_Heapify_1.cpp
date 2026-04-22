#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    for (int odd = 1; odd <= n; odd += 2) {
        std::vector<int> indices;
        for (int j = odd; j <= n; j *= 2) {
            indices.push_back(j);
        }

        std::vector<int> values;
        for (const int& idx : indices) {
            values.push_back(a[idx]);
        }

        std::sort(values.begin(), values.end());

        for (int k = 0; k < indices.size(); k++) {
            if (values[k] != indices[k]) {
                std::cout << "NO\n";
                return;
            }
        }
    }
    std::cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t{0};
    std::cin >> t;
    while (t--) solve();

    return 0;
}