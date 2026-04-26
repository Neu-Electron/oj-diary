#include <bits/stdc++.h>

void fastIO() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void solve() {
    int n{0};
    std::cin>>n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) {
        std::vector<std::pair<int, int>> events;
        int init_count = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) continue;
            if (a[i] < a[j]) {
                int mid_low = (a[i] + a[j]) / 2;
                events.push_back({mid_low + 1, 1});
            } else {
                int k_lim;
                if ((a[i] + a[j]) >= 0) k_lim = (a[i] + a[j] - 1) / 2;
                else k_lim = (a[i] + a[j] - 1) / 2;

                init_count++;
                events.push_back({k_lim + 1, -1});
            }
        }
        std::sort(events.begin(),events.end());

        int max_j = init_count;
        int cur = init_count;
        for (auto& ev : events) {
            cur += ev.second;
            max_j = std::max(max_j, cur);
        }
        std::cout << max_j << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    fastIO();
    
    int t = 1;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}