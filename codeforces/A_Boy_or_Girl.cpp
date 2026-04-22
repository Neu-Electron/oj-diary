#include <bits/stdc++.h>

int countUniqueChars(const std::string& str) {
    std::bitset<26> seen;
    for (char c : str) {
        seen.set(c - 'a');
    }
    return seen.count();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string name;
    std::cin >> name;
    if (countUniqueChars(name) & 1) {
        std::cout << "IGNORE HIM!\n";
    } else {
        std::cout << "CHAT WITH HER!\n";
    }
    return 0;
}