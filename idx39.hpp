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
 ///////////// 394. Decode String
Given an encoded string, return its decoded string.
The encoding rule is: k[encoded_string],
 where the encoded_string inside the square brackets is being repeated exactly k times.
 Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; No extra white spaces,
 square brackets are well-formed, etc.
Furthermore, you may assume that the original data does not contain any digits and that
 digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:
s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 */
std::string decodeString(std::string s) {
    std::string res;

    enum {
        TEXT = 0,
        DIGITAL,
        LEFT,
    } st;

    std::stack<int> ts;
    std::stack<std::string> tss;
    size_t digital_l = 0;
    size_t digital_r = 0;
    std::string str;

    st = TEXT;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (st == TEXT) {
            if (isdigit(c)) {
                digital_l = i;

                st = DIGITAL;
            } else {
                res += c;
            }
        } else if (st == DIGITAL) {
            if (isdigit(c)) {
                // still
            } else if (c == '[') {
                digital_r = i;
                ts.emplace(std::stoi(s.substr(digital_l, digital_r - digital_l)));

                st = LEFT;
            }
        } else if (st == LEFT) {
            if (c == ']') {
                if (ts.empty()) {
                    // error
                    return "";
                }
                std::string section;
                if (!tss.empty()) {
                    section = tss.top();
                    tss.pop();
                }
                for (int j = 0; j < ts.top(); ++j) {
                    section += str;
                }
                ts.pop();

                if (!ts.empty()) {
                    str = std::move(section);
                } else {
                    res += section;
                    str.clear();
                    st = TEXT;
                }

            } else if (isdigit(c)) {
                tss.emplace(str);
                str.clear();
                digital_l = i;

                st = DIGITAL;
            } else {
                str += c;
            }
        }
    }
    return res;
}

FTEST(test_decodeString) {
    auto t = [&](const std::string& s) {
        auto re = decodeString(s);
        LOG(INFO) << s << " decode: " << re;
        return re;
    };

    FEXP(t(""), "");
    FEXP(t("a"), "a");
    FEXP(t("ab"), "ab");
    FEXP(t("abc"), "abc");
    FEXP(t("1[]"), "");
    FEXP(t("2[]"), "");
    FEXP(t("3[]"), "");
    FEXP(t("1[ ]"), " ");
    FEXP(t("2[ ]"), "  ");
    FEXP(t("3[ ]"), "   ");
    FEXP(t("1[a]"), "a");
    FEXP(t("2[a]"), "aa");
    FEXP(t("3[a]"), "aaa");
    FEXP(t("1[ab]"), "ab");
    FEXP(t("2[ab]"), "abab");
    FEXP(t("3[ab]"), "ababab");
    FEXP(t("1[abc]"), "abc");
    FEXP(t("2[abc]"), "abcabc");
    FEXP(t("3[abc]"), "abcabcabc");
    FEXP(t("3[a]2[bc]"), "aaabcbc");
    FEXP(t("3[2[c]]"), "cccccc");
    FEXP(t("3[2[1[cb]]]"), "cbcbcbcbcbcb");
    FEXP(t("3[a2[c]]"), "accaccacc");
    FEXP(t("3[2[c]a]"), "ccaccacca");
    FEXP(t("3[a2[c]b]"), "accbaccbaccb");
    FEXP(t("2[abc]3[cd]ef"), "abcabccdcdcdef");
}

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
    sliding window
    Try to find count of different chars is i(1~26) that at least K in target string.
    Using 'count of char' to check if it's the expect, note that 'unique' or 'lek' changing is
    'level trigger', means this happend when 'count of char' come to 0.

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
            int unique = 0;     // count of different char
            int lek = 0;        // count of char which count at least K
            int start = 0;      // start is window left border, i is right border
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