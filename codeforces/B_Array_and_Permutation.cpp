#include <bits/stdc++.h>

bool isSubsequence(const std::vector<int>& c, const std::vector<int>& p) {
    if (c.empty())
        return true;

    if (c.size() > p.size())
        return false;

    int i = 0;
    int j = 0;

    while (i < c.size() && j < p.size()) {
        if (c[i] == p[j]) {
            i++;
        }
        j++;
    }

    return i == c.size();
}

std::vector<int> compress(const std::vector<int>& a) {
    std::vector<int> res;
    if (a.empty())
        return res;
    res.push_back(a[0]);
    for (size_t i = 1; i < a.size(); ++i) {
        if (a[i] != a[i - 1]) {
            res.push_back(a[i]);
        }
    }
    return res;
}

void solve() {
    int n{0};
    std::cin >> n;
    std::vector<int> p(n), a(n);
    for (int i = 0; i < n; ++i) std::cin >> p[i];
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<int> c = compress(a);

    if (isSubsequence(c, p)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t{0};
    std::cin >> t;
    while (t--) solve();

    return 0;
}