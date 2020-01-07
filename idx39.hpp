#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex39 {

/**
 ///////////// 391.

 */

/**
 ///////////// 392.

 */


/**
 ///////////// 393.

 */


/**
 ///////////// 394.

 */


/**
 ///////////// 395. Longest Substring with At Least K Repeating Characters
Find the length of the longest substring T of a given string
 (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:
Input:
s = "aaabb", k = 3

Output:
3
The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:
Input:
s = "ababbc", k = 2

Output:
5
The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

 THOUGHTS:
    divide and conquer
    1. count each char appears count from left to right
    2. find the first appears count less than k, then split to left half.
      1-2 recusive.

             k=3   a  b  a  b  b  c  d  c  a  b  a
                   l              i        j      len
     cnts                         ↓     (cnts[a]>=3)
     a 4      (cnts[a]>=3)  (cnts[c or d]<3)
     b 4
     c 2     split to std::max(longest(l, i), longest(j, len))
     d 1

 */
int longestSubstringAtLeast(std::string s, int k) {
    int len = s.size();
    int res = 0;
    auto sliding_window_method = [&] {
        int counts[26] = {0};
        for (int cnt = 1; cnt <= 26; ++cnt) {
            int unique = 0;
            int lek = 0;
            int start = 0;
            for (int i = 0; i < len;) {
                if (cnt >= unique) {        // window right expand
                    int idx = s[i] - 'a';
                    if (counts[idx]++ == 0) {
                        ++unique;
                    }
                    if (counts[idx] == k) {
                        ++lek;
                    }
                    ++i;
                } else {                    // more than cnt chars in window, left shrink
                    int idx = s[start] - 'a';
                    if (counts[idx]-- == k) {
                        --lek;
                    }
                    if (counts[idx] == 0) {
                        --unique;
                    }
                    ++start;
                }
                if (unique == cnt && unique == lek) {
                    // all unique count of number appear more than k
                    res = std::max(res, i - start);
                }
            }
        }
        return res;
    };
    auto divide_conquer_method = [&] {
        std::function<int(int, int)> r_func;
        r_func = [&](int start, int end) {
            int counts[26] = {0};
            for (int i = start; i < end; ++i) {
                counts[s[i] - 'a']++;
            }
            int i = start;
            while (i < end && counts[s[i] - 'a'] >= k) {
                ++i;
            }
            if (i == end) {
                return end - start;
            }

            int j = i + 1;
            while (j < end && counts[s[j] - 'a'] < k) {
                ++j;
            }
            return std::max(r_func(start, i), r_func(j, end));
        };
        return r_func(0, len);
    };
    return divide_conquer_method();
}

FTEST(test_longestSubstringAtLeast) {
    auto t = [&](const std::string& s, int k) {
        auto re = longestSubstringAtLeast(s, k);
        LOG(INFO) << s << " " << k << " as least substr lenght: " << re;
        return re;
    };

    FEXP(t("", 0), 0);
    FEXP(t("", 1), 0);
    FEXP(t("a", 1), 1);
    FEXP(t("a", 2), 0);
    FEXP(t("aa", 3), 0);
    FEXP(t("aa", 2), 2);
    FEXP(t("aba", 2), 0);
    FEXP(t("baa", 2), 2);
    FEXP(t("aab", 2), 2);
    FEXP(t("aaa", 2), 3);
    FEXP(t("abaa", 3), 0);
    FEXP(t("aaba", 3), 0);
    FEXP(t("aaa", 3), 3);
    FEXP(t("aaab", 3), 3);
    FEXP(t("baaa", 3), 3);
    FEXP(t("aaabb", 3), 3);
    FEXP(t("bbaaa", 3), 3);
    FEXP(t("bbbaaa", 3), 6);
    FEXP(t("ababbc", 2), 5);
}

/**
 ///////////// 396.

 */


/**
 ///////////// 397.

 */


/**
 ///////////// 398.

 */


/**
 ///////////// 399.

 */


/**
 ///////////// 400.

 */



}