#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::string>
    twoEditWords(std::vector<std::string> &queries,
                 std::vector<std::string> &dictionary) {
        int k = queries[0].size();
        std::vector<std::string> ans;
        for (const auto &word : queries) {
            bool found = false;
            for (const auto &dict : dictionary) {
                int count = 0;
                for (int i = 0; i < k; i++) {
                    if (word[i] != dict[i])
                        count++;
                    if (count > 2) {
                        break;
                    }
                }
                if (count <= 2) {
                    found = true;
                    break;
                }
            }
            if (found) ans.push_back(word);
        }
        return ans;
    }
};