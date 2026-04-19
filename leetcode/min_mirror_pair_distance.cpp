#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <unordered_map>
#include <vector>

class Solution {
  private:
    int reverse(int num) {
        int ans = 0;
        while (num > 0) {
            ans = ans * 10 + num % 10;
            num /= 10;
        }
        return ans;
    }

  public:
    int minMirrorPairDistance(std::vector<int> &nums) {
        int ans = INT_MAX;
        std::unordered_map<int, int> map;

        for (size_t i = 0; i < nums.size(); i++) {

            if (map.count(nums[i])) {
                ans = std::min(ans, static_cast<int>(i) - map[nums[i]]);
            }

            int rev = reverse(nums[i]);
            map[rev] = i;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};