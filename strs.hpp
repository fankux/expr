#pragma once

#include <string.h>
#include "util.hpp"

std::string print_rhombus(int n) {
    std::string res;
    if (n <= 0) {
        return res;
    }
    int max_count = 2 * n + 1;
    for (int i = 0 - n; i <= n; ++i) {
        int count = 2 * (n - abs(i)) + 1;
        int delta = (max_count - count) / 2;
        for (int c = 0; c < max_count; ++c) {
            if (c < delta || c >= delta + count) {
                res += " ";
            } else {
                res += "*";
            }
        }
        res += "\n";
    }
    return res;
}

FTEST(test_print_rhombus) {
    LOG(INFO) << "\n" << print_rhombus(0);
    LOG(INFO) << "\n" << print_rhombus(1);
    LOG(INFO) << "\n" << print_rhombus(2);
    LOG(INFO) << "\n" << print_rhombus(3);
    LOG(INFO) << "\n" << print_rhombus(8);
    LOG(INFO) << "\n" << print_rhombus(16);
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
    while (i < (ssize_t) str.size() && j < (ssize_t) pattern.size()) {
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
        std::cout << substr("", "") << std::endl;
        std::cout << substr("", "1") << std::endl;
        std::cout << substr("1", "") << std::endl;
        std::cout << substr("1", "1") << std::endl;
        std::cout << substr("1", "2") << std::endl;
        std::cout << substr("12", "") << std::endl;
        std::cout << substr("12", "1") << std::endl;
        std::cout << substr("12", "2") << std::endl;
        std::cout << substr("12", "12") << std::endl;
        std::cout << substr("12", "123") << std::endl;
        std::cout << substr("123", "") << std::endl;
        std::cout << substr("123", "1") << std::endl;
        std::cout << substr("123", "2") << std::endl;
        std::cout << substr("123", "12") << std::endl;
        std::cout << substr("123", "123") << std::endl;
        std::cout << substr("11233", "123") << std::endl;
        std::cout << substr("abbcabababbc", "bcababab") << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

size_t edit_distance_recusive_handle(const std::string& s1, const std::string& s2, size_t i,
        size_t j, std::vector<std::vector<size_t>>& counts) {
    if (i == s1.size()) {
        return s2.size() - j;
    }
    if (j == s2.size()) {
        return s1.size() - i;
    }
    if (counts[i][j] > 0) {
        return counts[i][j];
    }

    if (s1[i] == s2[j]) {
        return edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    }

    size_t insert_count = edit_distance_recusive_handle(s1, s2, i, j + 1, counts);
    size_t delete_count = edit_distance_recusive_handle(s1, s2, i + 1, j, counts);
    size_t update_count = edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    size_t count = std::min(insert_count, std::min(delete_count, update_count)) + 1;
    counts[i][j] = count;
    return count;
}

size_t edit_distance_recusive(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";
    std::vector<std::vector<size_t>> counts(s1.size(), std::vector<size_t>(s2.size()));
    return edit_distance_recusive_handle(s1, s2, 0, 0, counts);
}

size_t edit_distance_dp(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";

    std::vector<std::vector<size_t>> counts(s1.size() + 1, std::vector<size_t>(s2.size() + 1));
    for (size_t i = 0; i <= s1.size(); ++i) {
        counts[i][0] = i;
    }
    for (size_t i = 0; i <= s2.size(); ++i) {
        counts[0][i] = i;
    }

    for (size_t i = 1; i <= s1.size(); ++i) {
        for (size_t j = 1; j <= s2.size(); ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                counts[i][j] = counts[i - 1][j - 1];
            } else {
                counts[i][j] = std::min(counts[i - 1][j - 1],
                        std::min(counts[i - 1][j], counts[i][j - 1])) + 1;
            }
        }
    }
    return counts[s1.size()][s2.size()];
}

FTEST(test_edit_distance) {
    std::cout << edit_distance_recusive("", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "") << std::endl;
    std::cout << edit_distance_recusive("", "") << std::endl;
    std::cout << edit_distance_recusive("1", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "2") << std::endl;
    std::cout << edit_distance_recusive("2", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "11") << std::endl;
    std::cout << edit_distance_recusive("1", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "1") << std::endl;
    std::cout << edit_distance_recusive("12", "1") << std::endl;
    std::cout << edit_distance_recusive("11", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "22") << std::endl;

    std::cout << std::endl;

    std::cout << edit_distance_dp("", "1") << std::endl;
    std::cout << edit_distance_dp("1", "") << std::endl;
    std::cout << edit_distance_dp("", "") << std::endl;
    std::cout << edit_distance_dp("1", "1") << std::endl;
    std::cout << edit_distance_dp("1", "2") << std::endl;
    std::cout << edit_distance_dp("2", "1") << std::endl;
    std::cout << edit_distance_dp("1", "11") << std::endl;
    std::cout << edit_distance_dp("1", "12") << std::endl;
    std::cout << edit_distance_dp("11", "1") << std::endl;
    std::cout << edit_distance_dp("12", "1") << std::endl;
    std::cout << edit_distance_dp("11", "12") << std::endl;
    std::cout << edit_distance_dp("11", "22") << std::endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::pair<size_t, size_t>> len_of_longest_substr(const std::string& s) {
    std::vector<std::pair<size_t, size_t>> res;

    std::vector<int> m(128, -1);
    int max_len = 0;
    int left = -1;
    for (int i = 0; i < s.size(); ++i) {
        left = std::max(left, m[s[i]]);
        m[s[i]] = i;
        //max_len = std::max(max_len, i - left);
        int delta = i - left;
        if (delta >= max_len) {
            if (delta > max_len) {
                res.clear();
            }
            res.emplace_back(std::make_pair(left + 1, i));
            max_len = delta;
        }
    }
    return res;
}

std::vector<std::pair<size_t, size_t>> longest_substr_two_distinct(const std::string& s) {
    std::vector<std::pair<size_t, size_t>> res;

    int max_len = 0, left = 0;
    std::unordered_map<char, size_t> m;
    for (size_t i = 0; i < s.size(); ++i) {
        ++m[s[i]];
        while (m.size() > 2) {
            if (--m[s[left]] == 0) {
                m.erase(s[left]);
            }
            ++left;
        }

        size_t delta = i - left + 1;
        if (delta >= max_len) {
            if (delta > max_len) {
                res.clear();
            }
            res.emplace_back(std::make_pair(left, i));
            max_len = delta;
        }
    }
    return res;
}

std::vector<std::pair<size_t, size_t>> longest_substr_k_distinct(const std::string& s, int k) {
    std::vector<std::pair<size_t, size_t>> res;

    int max_len = 0, left = 0;
    std::unordered_map<char, size_t> m;
    for (size_t i = 0; i < s.size(); ++i) {
        ++m[s[i]];
        while (m.size() > k) {
            if (--m[s[left]] == 0) {
                m.erase(s[left]);
            }
            ++left;
        }
        //max_len = std::max(max_len, i - left + 1);
        size_t delta = i - left + 1;
        if (delta >= max_len) {
            if (delta > max_len) {
                res.clear();
            }
            res.emplace_back(std::make_pair(left, i));
            max_len = delta;
        }
    }
    return res;
}

FTEST(test_len_of_longest_substr) {
    LOG(INFO) << "longest_substr";
    LOG(INFO) << len_of_longest_substr("abc");
    LOG(INFO) << len_of_longest_substr("ababc");
    LOG(INFO) << len_of_longest_substr("ababcabc");
    LOG(INFO) << len_of_longest_substr("aaaaaaa");
    LOG(INFO) << len_of_longest_substr("abcdef");

    LOG(INFO) << "longest_substr_two_distinct";
    LOG(INFO) << longest_substr_two_distinct("eceba");
    LOG(INFO) << longest_substr_two_distinct("abc");
    LOG(INFO) << longest_substr_two_distinct("ababc");
    LOG(INFO) << longest_substr_two_distinct("ababcabc");
    LOG(INFO) << longest_substr_two_distinct("aaaaaaa");
    LOG(INFO) << longest_substr_two_distinct("abcdef");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void debug_lcs_seq(const std::string& s1, const std::string& s2,
        const std::vector<std::vector<int>>& seqs) {
    std::cout << "\\| ";
    for (size_t j = 1; j <= s2.size(); ++j) {
        std::cout << s2[j - 1] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 1; i <= s1.size(); ++i) {
        std::cout << s1[i - 1] << "| ";
        for (size_t j = 1; j <= s2.size(); ++j) {
            std::cout << seqs[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @param direction  0, left; 1, up
 */
void lcs_path(const std::string& s1, const std::string& s2, int s1_pos, int s2_pos,
        int direction, const std::vector<std::vector<int>>& seqs, std::string& seq,
        std::vector<std::string>& results) {

    size_t i = s1_pos;
    size_t j = s2_pos;
    while (i > 0 && j > 0) {

        if (s1[i - 1] == s2[j - 1]) {
            seq = s1[i - 1] + seq;
            --i;
            --j;
            continue;
        }

        if (seqs[i - 1][j] > seqs[i][j - 1]) { // move up
            --i;
        } else if (seqs[i - 1][j] < seqs[i][j - 1]) { // move left
            --j;
        } else {
            //chose a direction, recuresive for multiple path
            if (direction == 1 && j != s2_pos) {
                std::string seq_left = seq;
                lcs_path(s1, s2, i, j - 1, 0, seqs, seq_left, results);
            }
            if (direction == 0 && i != s1_pos) {
                std::string seq_right = seq;
                lcs_path(s1, s2, i - 1, j, 1, seqs, seq_right, results);
            }
            if (direction == 0) {
                --j;
            } else {
                --i;
            }
        }
    }
    results.emplace_back(seq);
}

void lcs(const std::string& s1, const std::string& s2, std::vector<std::string>& results) {
    if (s1.empty() || s2.empty()) {
        return;
    }

    std::vector<std::vector<int>> seqs;
    for (size_t i = 0; i <= s1.size(); ++i) {
        seqs.emplace_back(std::vector<int>());
        for (size_t j = 0; j <= s2.size(); ++j) {
            seqs[i].emplace_back(0);
        }
    }

    for (size_t i = 0; i < s1.size(); ++i) {
        for (size_t j = 0; j < s2.size(); ++j) {
            if (s1[i] == s2[j]) {
                seqs[i + 1][j + 1] = seqs[i][j] + 1;
            } else {
                seqs[i + 1][j + 1] = std::max(seqs[i + 1][j], seqs[i][j + 1]);
            }
        }
    }

    debug_lcs_seq(s1, s2, seqs);

    std::string seq;
    lcs_path(s1, s2, s1.size(), s2.size(), 0, seqs, seq, results);
}

FTEST(test_lcs) {
    std::string a = "13456778";
    std::string b = "357486782";
    std::vector<std::string> seqs;

    lcs(a, b, seqs);

    for (auto& seq : seqs) {
        std::cout << seq << std::endl;
    }
}