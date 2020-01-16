#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex64 {

/**
 ///////////// 641.

 */

/**
 ///////////// 642.

 */


/**
 ///////////// 643.

 */


/**
 ///////////// 644.

 */


/**
 ///////////// 645.

 */


/**
 ///////////// 646.

 */


/**
 ///////////// 647. Palindromic Substrings
Given a string, your task is to count how many palindromic substrings in this string.
The substrings with different start indexes or end indexes are counted as different substrings
 even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Note:
 The input string length won't exceed 1000.
 */
int countPalindromicSubstrings(std::string s) {
    size_t len = s.size();
    std::vector<std::vector<bool>> state(len, std::vector<bool>(len, false));
    int res = len;
    for (size_t i = 0; i < len; ++i) {
        state[i][i] = true;
        for (size_t j = 0; j < i; ++j) {
            if (i == j + 1) {
                state[j][i] = s[i] == s[j];
            } else if (i > j + 1) {
                state[j][i] = s[i] == s[j] && state[j + 1][i - 1];
            }
            if (state[j][i]) {
                ++res;
            }
        }
    }
    return res;
}

FTEST(test_countPalindromicSubstrings) {
    auto t = [](const std::string& s) {
        auto re = countPalindromicSubstrings(s);
        LOG(INFO) << s << " palindroms count: " << re;
        return re;
    };

    FEXP(t(""), 0);
    FEXP(t("a"), 1);
    FEXP(t("ab"), 2);
    FEXP(t("aa"), 3);
    FEXP(t("aaa"), 6);
    FEXP(t("baa"), 4);
    FEXP(t("aab"), 4);
    FEXP(t("aba"), 4);
    FEXP(t("abc"), 3);
    FEXP(t("abab"), 6);
    FEXP(t("ebababb"), 12);

}

/**
 ///////////// 648.

 */


/**
 ///////////// 649.

 */


/**
 ///////////// 650.

 */



}