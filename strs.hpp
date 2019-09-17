#pragma once

#include "util.hpp"


void print_rhombus(int n) {
    if (n <= 0) {
        return;
    }

    int max_count = 2 * n + 1;

    for (int i = 0 - n; i <= n; ++i) {
        int count = 2 * (n - abs(i)) + 1;
        int delta = (max_count - count) / 2;

        for (int c = 0; c < max_count; ++c) {
            if (c < delta || c >= delta + count) {
                std::cout << " ";
            } else {
                std::cout << "*";
            }
        }
        std::cout << std::endl;
    }
}

void test_print_rhombus() {
//    print_rhombus(0);
    print_rhombus(1);
    print_rhombus(2);
//    print_rhombus(3);
    print_rhombus(8);
//    print_rhombus(16);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::string longest_palindrome(std::string s) {
    int max_len = 0;
    auto search = [&s](int left, int right, int& start, int& max_len) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        if (max_len < right - left - 1) {
            start = left + 1;
            max_len = right - left - 1;
        }
    };

    int n = s.size();
    if (n < 2) {
        return s;
    }
    int start = 0;
    for (int i = 0; i < n - 1; ++i) {
        search(i, i, start, max_len); // i as the center
        search(i, i + 1, start, max_len);
    }
    return s.substr(start, max_len);
}

std::string longest_palindrome_dp(std::string s) {
    if (s.empty()) {
        return "";
    }

    int n = s.size();
    int len = 1;
    int left = 0;
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // d[i][j] from i to j, max length of palindrome

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
        for (int j = 0; j < i; ++j) {
            if (i == j + 1) {
                dp[j][i] = s[i] == s[j];
            } else if (i > j + 1) {
                dp[j][i] = s[i] == s[j] && dp[j + 1][i - 1];
            }

            if (dp[j][i] && len < i - j + 1) {
                len = i - j + 1;
                left = j;
            }
        }
    }

    return s.substr(left, len);
}

FTEST(test_longest_palindrome) {
    std::cout << longest_palindrome("") << std::endl;
    std::cout << longest_palindrome("a") << std::endl;
    std::cout << longest_palindrome("aa") << std::endl;
    std::cout << longest_palindrome("baa") << std::endl;
    std::cout << longest_palindrome("aab") << std::endl;
    std::cout << longest_palindrome("ab") << std::endl;
    std::cout << longest_palindrome("abab") << std::endl;
    std::cout << longest_palindrome("aba") << std::endl;
    std::cout << longest_palindrome("ebababb") << std::endl;

    std::cout << longest_palindrome_dp("") << std::endl;
    std::cout << longest_palindrome_dp("a") << std::endl;
    std::cout << longest_palindrome_dp("aa") << std::endl;
    std::cout << longest_palindrome_dp("baa") << std::endl;
    std::cout << longest_palindrome_dp("aab") << std::endl;
    std::cout << longest_palindrome_dp("ab") << std::endl;
    std::cout << longest_palindrome_dp("abab") << std::endl;
    std::cout << longest_palindrome_dp("aba") << std::endl;
    std::cout << longest_palindrome_dp("ebababb") << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void kmp_nexts(const std::string& pattern, std::vector<ssize_t>& nexts) {
    if (pattern.empty()) {
        return;
    }
    nexts.resize(pattern.size(), -1);
    ssize_t k = -1;
    int i = 0;
    while (i < pattern.size() - 1) {
        if (k == -1 || pattern[i] == pattern[k]) {
            ++k;
            ++i;
            if (pattern[i] == pattern[k]) {
                nexts[i] = nexts[k];
            } else {
                nexts[i] = k;
            }
        } else {
            k = nexts[k];
        }
    }
}

ssize_t substr_kmp(const std::string& str, const std::string& pattern) {
    std::cout << "\"" << str << "\" kmp substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }

    std::vector<ssize_t> nexts;
    kmp_nexts(pattern, nexts);

    ssize_t i = 0;
    ssize_t j = 0;
    while (i < (ssize_t)str.size() && j < (ssize_t)pattern.size()) {
        if (j == -1 || str[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            j = nexts[j];
        }
    }
    if (j >= pattern.size()) {
        return i - j;
    }
    return -1;
}

void bm_bads(const std::string& pattern, char (& bads)[256]) {
    memset(bads, -1, sizeof(bads));

    for (size_t i = 0; i < pattern.size(); ++i) {
        bads[pattern[i]] = pattern.size() - 1 - i;
    }
}

void bm_goods_suffix(const std::string& pattern, std::vector<size_t>& suffix) {
    suffix.resize(pattern.size(), 0);

    for (size_t i = 0; i < pattern.size(); ++i) {
        if (i == pattern.size() - 1) {
            suffix[i] = pattern.size();
            continue;
        }
        ssize_t j = i;
        while (j >= 0 && pattern[j] == pattern[pattern.size() - 1 - i + j]) {
            --j;
        }
        suffix[i] = i - j;
    }
}

void bm_goods(const std::string& pattern, std::vector<size_t>& goods) {

    std::vector<size_t> suffix;
    bm_goods_suffix(pattern, suffix);

    goods.resize(pattern.size(), pattern.size());

    // full match suffix
    size_t j = 0;
    for (ssize_t i = pattern.size() - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (; j < pattern.size() - 1 - i; j++) {
                if (goods[j] == pattern.size()) { // means no assign value after initialize
                    goods[j] = pattern.size() - 1 - i;
                }
            }
        }
    }

    // partial match suffix
    for (ssize_t i = 0; i <= pattern.size() - 2; i++) {
        goods[pattern.size() - 1 - suffix[i]] = pattern.size() - 1 - i;
    }
}

ssize_t substr_bm(const std::string& str, const std::string& pattern) {
    // FIXME
    std::cout << "\"" << str << "\" bm substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }
    char bads[256];
    std::vector<size_t> goods;
    bm_bads(pattern, bads);
    bm_goods(pattern, goods);

    size_t j = 0;
    while (j <= str.size() - pattern.size()) {
        ssize_t i;
        for (i = pattern.size() - 1; i >= 0 && pattern[i] == str[i + j]; i--) {}
        if (i < 0) {
            j += goods[0];
            return j;
        } else {
            j += std::max(bads[str[i + j]] - pattern.size() + 1, goods[i]);
        }
    }
    return -1;
}

ssize_t substr_sunday(const std::string& str, const std::string& pattern) {
    std::cout << "\"" << str << "\" sunday substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }

    size_t steps[256] = {pattern.size() + 1};
    for (size_t i = 0; i < pattern.size(); ++i) {
        steps[pattern[i]] = pattern.size() - i;
    }

    size_t i = 0;
    while (i <= str.size() - pattern.size()) {
        size_t j = 0;
        while (str[i + j] == pattern[j]) {
            ++j;
            if (j >= pattern.size()) {
                return i;
            }
        }
        i += steps[str[i + pattern.size()]];
    }

    return -1;
}

FTEST(test_substr) {
    std::vector<std::function<ssize_t(const std::string&, const std::string&)>> substr_funcs;
    substr_funcs.emplace_back(substr_kmp);
//    substr_funcs.emplace_back(substr_bm);
    substr_funcs.emplace_back(substr_sunday);

    for (auto& substr : substr_funcs) {
//        std::cout << substr("", "") << std::endl;
//        std::cout << substr("", "1") << std::endl;
//        std::cout << substr("1", "") << std::endl;
//        std::cout << substr("1", "1") << std::endl;
//        std::cout << substr("1", "2") << std::endl;
//        std::cout << substr("12", "") << std::endl;
//        std::cout << substr("12", "1") << std::endl;
//        std::cout << substr("12", "2") << std::endl;
//        std::cout << substr("12", "12") << std::endl;
//        std::cout << substr("12", "123") << std::endl;
//        std::cout << substr("123", "") << std::endl;
//        std::cout << substr("123", "1") << std::endl;
//        std::cout << substr("123", "2") << std::endl;
//        std::cout << substr("123", "12") << std::endl;
//        std::cout << substr("123", "123") << std::endl;
//        std::cout << substr("11233", "123") << std::endl;
        std::cout << substr("abbcabababbc", "bcababab") << std::endl;
    }
}
