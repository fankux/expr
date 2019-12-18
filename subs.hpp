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

///////////////////////////////////////////////////////////////////////////////////////////////////

ssize_t lower_bound(const std::vector<int>& nums, int target) {
    size_t l = 0;
    size_t h = nums.size();
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}

ssize_t upper_bound(const std::vector<int>& nums, int target) {
    int l = 0;
    int h = nums.size();
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}

ssize_t bin_search(const std::vector<int>& nums, int target) {
    ssize_t re = lower_bound(nums, target);
    return re == nums.size() || nums[re] != target ? -1 : re;
}

ssize_t bin_search_1st_great_equal(const std::vector<int>& nums, int target) {
    ssize_t re = lower_bound(nums, target);
    return re == nums.size() ? -1 : re;
}

ssize_t bin_search_1st_great(const std::vector<int>& nums, int target) {
    ssize_t re = upper_bound(nums, target);
    return re == nums.size() ? -1 : re;
}

void test_bin_search() {
    auto binary_search_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search(nums, target);
        LOG(INFO) << nums << " find " << target << ": " << re;
        return re;
    };
    binary_search_t({}, 1);
    binary_search_t({1}, 0);
    binary_search_t({1}, 2);
    binary_search_t({1}, 1);
    binary_search_t({1, 2}, 0);
    binary_search_t({1, 2}, 3);
    binary_search_t({1, 2}, 1);
    binary_search_t({1, 2}, 2);
    binary_search_t({1, 2, 3}, 0);
    binary_search_t({1, 2, 3}, 1);
    binary_search_t({1, 2, 3}, 2);
    binary_search_t({1, 2, 3}, 3);
    binary_search_t({1, 2, 3}, 4);
    binary_search_t({1, 2, 3, 4}, 1);
    binary_search_t({1, 2, 3, 4}, 2);
    binary_search_t({1, 2, 3, 4}, 3);
    binary_search_t({1, 2, 3, 4}, 4);
    binary_search_t({1, 2, 3, 4, 5}, 1);
    binary_search_t({1, 2, 3, 4, 5}, 2);
    binary_search_t({1, 2, 3, 4, 5}, 3);
    binary_search_t({1, 2, 3, 4, 5}, 4);
    binary_search_t({1, 2, 3, 4, 5}, 5);
    binary_search_t({1, 2, 2, 4, 5}, 2);
    binary_search_t({1, 2, 3, 3, 5}, 3);

    auto bound_t = [](const std::vector<int>& nums, int target) {
        auto re = lower_bound(nums, target);
        LOG(INFO) << nums << " lower x>=" << target << "(closed): " << re;
        re = upper_bound(nums, target);
        LOG(INFO) << nums << " upper x<=" << target << "(unclosed): " << re;
        return re;
    };
    bound_t({1}, 1);
    bound_t({1, 1}, 1);
    bound_t({1, 1, 1}, 1);
    bound_t({1, 1, 1, 1}, 1);
    bound_t({1, 1, 1, 1, 1}, 1);
    bound_t({1}, 0);
    bound_t({1}, 2);
    bound_t({1, 1, 1, 1, 1}, 0);
    bound_t({1, 1, 1, 1, 1}, 2);
    bound_t({1, 2, 2, 2, 3}, 2);

    auto first_ge_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search_1st_great_equal(nums, target);
        LOG(INFO) << nums << " 1st x>=" << target << ": " << re;
        return re;
    };
    first_ge_t({}, 1);
    first_ge_t({1}, 0);
    first_ge_t({1}, 2);
    first_ge_t({1}, 1);
    first_ge_t({1, 2}, 0);
    first_ge_t({1, 2}, 3);
    first_ge_t({1, 2}, 1);
    first_ge_t({1, 2}, 2);
    first_ge_t({1, 2, 3}, 0);
    first_ge_t({1, 2, 3}, 1);
    first_ge_t({1, 2, 3}, 2);
    first_ge_t({1, 2, 3}, 3);
    first_ge_t({1, 2, 3}, 4);
    first_ge_t({1, 2, 3, 4}, 1);
    first_ge_t({1, 2, 3, 4}, 2);
    first_ge_t({1, 2, 3, 4}, 3);
    first_ge_t({1, 2, 3, 4}, 4);
    first_ge_t({1, 2, 3, 4, 5}, 1);
    first_ge_t({1, 2, 3, 4, 5}, 2);
    first_ge_t({1, 2, 3, 4, 5}, 3);
    first_ge_t({1, 2, 3, 4, 5}, 4);
    first_ge_t({1, 2, 3, 4, 5}, 5);
    first_ge_t({1, 2, 2, 4, 5}, 2);
    first_ge_t({1, 2, 3, 3, 5}, 3);

    auto first_g_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search_1st_great(nums, target);
        LOG(INFO) << nums << " 1st x>" << target << ": " << re;
        return re;
    };
    first_g_t({}, 1);
    first_g_t({1}, 0);
    first_g_t({1}, 2);
    first_g_t({1}, 1);
    first_g_t({1, 2}, 0);
    first_g_t({1, 2}, 3);
    first_g_t({1, 2}, 1);
    first_g_t({1, 2}, 2);
    first_g_t({1, 2, 3}, 0);
    first_g_t({1, 2, 3}, 1);
    first_g_t({1, 2, 3}, 2);
    first_g_t({1, 2, 3}, 3);
    first_g_t({1, 2, 3}, 4);
    first_g_t({1, 2, 3, 4}, 1);
    first_g_t({1, 2, 3, 4}, 2);
    first_g_t({1, 2, 3, 4}, 3);
    first_g_t({1, 2, 3, 4}, 4);
    first_g_t({1, 2, 3, 4, 5}, 1);
    first_g_t({1, 2, 3, 4, 5}, 2);
    first_g_t({1, 2, 3, 4, 5}, 3);
    first_g_t({1, 2, 3, 4, 5}, 4);
    first_g_t({1, 2, 3, 4, 5}, 5);
    first_g_t({1, 2, 2, 4, 5}, 2);
    first_g_t({1, 2, 3, 3, 5}, 3);
}