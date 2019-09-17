#pragma once

#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::pair<size_t, size_t>> len_of_longest_substr(const std::string& s) {
    std::vector<std::pair<size_t, size_t>> res;

    std::vector<int> m(128, -1);
    int max_len = 0;
    int left = -1;
    for (int i = 0; i < s.size(); ++i) {
        left = std::max(left, m[s[i]]);
        m[s[i]] = i;

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

std::vector<std::pair<size_t, size_t>> len_of_longest_substr_two_distinct(const std::string& s) {
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

FTEST(test_len_of_longest_substr) {
    LOG(INFO) << "len_of_longest_substr";
    LOG(INFO) << len_of_longest_substr("abc");
    LOG(INFO) << len_of_longest_substr("ababc");
    LOG(INFO) << len_of_longest_substr("ababcabc");
    LOG(INFO) << len_of_longest_substr("aaaaaaa");
    LOG(INFO) << len_of_longest_substr("abcdef");

    LOG(INFO) << "len_of_longest_substr_two_distinct";
    LOG(INFO) << len_of_longest_substr_two_distinct("eceba");
    LOG(INFO) << len_of_longest_substr_two_distinct("abc");
    LOG(INFO) << len_of_longest_substr_two_distinct("ababc");
    LOG(INFO) << len_of_longest_substr_two_distinct("ababcabc");
    LOG(INFO) << len_of_longest_substr_two_distinct("aaaaaaa");
    LOG(INFO) << len_of_longest_substr_two_distinct("abcdef");
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
