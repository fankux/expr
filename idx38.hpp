#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex38 {

/**
 ///////////// 381.

 */

/**
 ///////////// 382.

 */


/**
 ///////////// 383.

 */


/**
 ///////////// 384.

 */


/**
 ///////////// 385.

 */


/**
 ///////////// 386.

 */


/**
 ///////////// 387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index.
 If it doesn't exist, return -1.

Examples:
s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
 */
int firstUniqChar(std::string s) {
    int mm[26] = {0};
    for (char c : s) {
        ++mm[c - 'a'];
    }
    for (size_t i = 0; i < s.size(); ++i) {
        if (mm[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}

FTEST(test_firstUniqChar) {
    auto t = [&](const std::string& s) {
        auto re = firstUniqChar(s);
        LOG(INFO) << s << " first unique char: " << re;
        return re;
    };

    FEXP(t(""), -1);
    FEXP(t("a"), 0);
    FEXP(t("aa"), -1);
    FEXP(t("aab"), 2);
    FEXP(t("leetcode"), 0);
    FEXP(t("loveleetcode"), 2);
}

/**
 ///////////// 388.

 */


/**
 ///////////// 389.

 */


/**
 ///////////// 390.

 */



}