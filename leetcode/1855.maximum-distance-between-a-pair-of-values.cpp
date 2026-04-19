#include <cassert>
#include <iostream>
#include <random>
#include <vector>

class Solution {
  public:
    int maxDistance(std::vector<int> &nums1, std::vector<int> &nums2) {
        int ans{0};
        int i{0};
        int n = nums1.size();
        int m = nums2.size();

        for (int j = 0; j < m; j++) {
            while (i < n && nums1[i] > nums2[j]) {
                i++;
            }

            if (i < n) {
                if (nums1[i] <= nums2[j]) {
                    ans = std::max(ans, j - i);
                }
            }
        }
        return ans;
    }
};

// 这些一套都是测试
class BruteForce {
  public:
    int maxDistance(std::vector<int> &nums1, std::vector<int> &nums2) {
        int maxDist = 0;
        for (size_t i = 0; i < nums1.size(); i++) {
            for (size_t j = i; j < nums2.size(); j++) {
                if (nums1[i] <= nums2[j]) {
                    maxDist = std::max(maxDist, static_cast<int>(j - i));
                }
            }
        }
        return maxDist;
    }
};

std::vector<int> generateNonIncreasing(int size, int minVal = 1,
                                       int maxVal = 100000) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    if (size == 0)
        return arr;

    arr[0] = dis(gen);
    for (int i = 1; i < size; i++) {
        arr[i] = dis(gen) % (arr[i - 1] + 1);
    }
    return arr;
}

void runAssertionTests() {
    Solution sol;
    std::vector<int> nums1_1 = {55, 30, 5, 4, 2};
    std::vector<int> nums2_1 = {100, 20, 10, 10, 5};
    assert(sol.maxDistance(nums1_1, nums2_1) == 2);

    std::vector<int> nums1_2 = {2, 2, 2};
    std::vector<int> nums2_2 = {10, 10, 1};
    assert(sol.maxDistance(nums1_2, nums2_2) == 1);

    std::vector<int> nums1_3 = {30, 29, 19, 5};
    std::vector<int> nums2_3 = {25, 25, 25, 25, 25};
    assert(sol.maxDistance(nums1_3, nums2_3) == 2);

    std::vector<int> nums1_4 = {1};
    std::vector<int> nums2_4 = {1};
    assert(sol.maxDistance(nums1_4, nums2_4) == 0);

    std::vector<int> nums1_5 = {5, 4, 3, 2, 1};
    std::vector<int> nums2_5 = {5, 4, 3, 2, 1};
    assert(sol.maxDistance(nums1_5, nums2_5) == 0);

    std::vector<int> nums1_6 = {100, 99, 98};
    std::vector<int> nums2_6 = {1, 1, 1};
    assert(sol.maxDistance(nums1_6, nums2_6) == 0);

    static_cast<void>(sol);
    std::cout << "✓ All assertion tests passed!" << std::endl;
}

void runCompareTests(int testCount = 10000) {
    Solution sol;
    BruteForce brute;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sizeDist(1, 100);

    for (int i = 0; i < testCount; i++) {
        int len1 = sizeDist(gen);
        int len2 = sizeDist(gen);

        std::vector<int> nums1 = generateNonIncreasing(len1);
        std::vector<int> nums2 = generateNonIncreasing(len2);

        std::vector<int> nums1_copy1 = nums1;
        std::vector<int> nums2_copy1 = nums2;
        std::vector<int> nums1_copy2 = nums1;
        std::vector<int> nums2_copy2 = nums2;

        int yourResult = sol.maxDistance(nums1_copy1, nums2_copy1);
        int correctResult = brute.maxDistance(nums1_copy2, nums2_copy2);

        if (yourResult != correctResult) {
            std::cout << "\n✗ Mismatch found at test #" << i + 1 << std::endl;
            std::cout << "nums1 = [";
            for (size_t j = 0; j < nums1.size(); j++) {
                std::cout << nums1[j] << (j < nums1.size() - 1 ? ", " : "");
            }
            std::cout << "]" << std::endl;
            std::cout << "nums2 = [";
            for (size_t j = 0; j < nums2.size(); j++) {
                std::cout << nums2[j] << (j < nums2.size() - 1 ? ", " : "");
            }
            std::cout << "]" << std::endl;
            std::cout << "Your result: " << yourResult
                      << ", Expected: " << correctResult << std::endl;
            assert(false);
        }

        if ((i + 1) % 1000 == 0) {
            std::cout << "Progress: " << i + 1 << "/" << testCount
                      << " tests passed" << std::endl;
        }
    }

    std::cout << "✓ All " << testCount << " random comparison tests passed!"
              << std::endl;
}

int main() {
    std::cout << "=== Running Assertion Tests ===" << std::endl;
    runAssertionTests();

    std::cout << "\n=== Running Random Comparison Tests ===" << std::endl;
    runCompareTests(10000);

    std::cout << "\n✓ All tests completed successfully!" << std::endl;

    return 0;
}