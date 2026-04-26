#include <bits/stdc++.h>

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>


class Solution {
   public:
    int minimumHammingDistance(std::vector<int>& source, std::vector<int>& target,
                               std::vector<std::vector<int>>& allowedSwaps) {
        int n = source.size();
        std::vector<int> parent(n);
        std::iota(parent.begin(), parent.end(), 0);

        std::function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        for (auto& swap : allowedSwaps) {
            int a = find(swap[0]), b = find(swap[1]);

            if (a != b)
                parent[a] = b;
        }

        std::unordered_map<int, std::vector<int>> comps;
        for (int i = 0; i < n; i++) {
            comps[find(i)].push_back(i);
        }

        int total_match = 0;
        for (auto& [root, indices] : comps) {
            std::unordered_multiset<int> srcVals, tgtVals;
            for (int idx : indices) {
                srcVals.insert(source[idx]);
                tgtVals.insert(target[idx]);
            }

            for (int val : srcVals) {
                auto it = tgtVals.find(val);
                if (it != tgtVals.end()) {
                    total_match++;
                    tgtVals.erase(it);
                }
            }
        }
        return n - total_match;
    }
};