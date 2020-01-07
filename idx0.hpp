#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;

/**
////////// 1
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
 */
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    if (nums.size() < 2) {
        return {};
    }

    std::unordered_map<int, int> cc;
    for (size_t i = 0; i < nums.size(); ++i) {
        cc.emplace(nums[i], i);
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        auto entry = cc.find(target - nums[i]);
        if (entry != cc.end() && i != entry->second) {
            return {(int) (i), entry->second};
        }
    }
    return {};
}

/**
////////// 2
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* h = nullptr;
    ListNode* prev = nullptr;

    bool carry = false;
    while (l1 || l2) {
        ListNode* c = nullptr;
        if (l1) {
            c = l1;
            l1->val += (l2 == nullptr ? 0 : l2->val) + (int) carry;
        } else if (l2) {
            c = l2;
            l2->val += (int) carry;
        }
        h = h != nullptr ? h : c;

        carry = c->val >= 10 ? c->val -= 10, true : false;

        prev = prev != nullptr ? prev->next = c, c : c;
        l1 = l1 != nullptr ? l1->next : nullptr;
        l2 = l2 != nullptr ? l2->next : nullptr;
    }
    prev->next = carry ? new ListNode(1) : nullptr;
    return h;
}

FTEST(test_addTwoNumbers) {
    ListNode* l = list_convert_leetcode(create_list({1, 2, 3}));
    ListNode* r = list_convert_leetcode(create_list({4, 5, 6}));
    ListNode* re = addTwoNumbers(l, r);
    print_list(re);

    l = list_convert_leetcode(create_list({1, 2, 4}));
    r = list_convert_leetcode(create_list({4, 5, 6}));
    re = addTwoNumbers(l, r);
    print_list(re);

    l = list_convert_leetcode(create_list({1, 6, 4}));
    r = list_convert_leetcode(create_list({4, 5, 6}));
    re = addTwoNumbers(l, r);
    print_list(re);

    l = list_convert_leetcode(create_list({2, 4}));
    r = list_convert_leetcode(create_list({4, 5, 6}));
    re = addTwoNumbers(l, r);
    print_list(re);

    l = list_convert_leetcode(create_list({1, 2, 4}));
    r = list_convert_leetcode(create_list({5, 6}));
    re = addTwoNumbers(l, r);
    print_list(re);
}

/**
////////// 3
 Given a string, find the length of the longest substring without repeating characters.

 Example 1:

 Input: "abcabcbb"
 Output: 3
 Explanation: The answer is "abc", with the length of 3.

 Example 2:

 Input: "bbbbb"
 Output: 1
 Explanation: The answer is "b", with the length of 1.

 Example 3:

 Input: "pwwkew"
 Output: 3
 Explanation: The answer is "wke", with the length of 3.
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */
int lengthOfLongestSubstring(std::string s) {
    std::vector<int> m(128, -1);
    int res = 0;
    int left = -1;
    for (int i = 0; i < s.size(); ++i) {
        left = std::max(left, m[s[i]]);
        m[s[i]] = i;
        res = std::max(res, i - left);
    }
    return res;
}

/**
////////// 4
 There are two sorted arrays nums1 and nums2 of size m and n respectively.
 Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 You may assume nums1 and nums2 cannot be both empty.

 Example 1:
 nums1 = [1, 3]
 nums2 = [2]
 The median is 2.0

 Example 2:
 nums1 = [1, 2]
 nums2 = [3, 4]
 The median is (2 + 3)/2 = 2.5
 */
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    return median_of_two_iteration(nums1, nums2);
}

/**
////////// 5
 Given a string s, find the longest palindromic substring in s.
 You may assume that the maximum length of s is 1000.

 Example 1:
 Input: "babad"
 Output: "bab"
 Note: "aba" is also a valid answer.

 Example 2:
 Input: "cbbd"
 Output: "bb"

 THOUGHTS:
 We initiate at diagonal, and iterate direction is [TOP->BOTTOM(diagonal line)]->RIGHT,
    just TOP-RIGHT half is enough because parlindrome is symmetric.
 dp[i][j] means if from i to j is palindrome.
 d[i][j] = {
    1                           (if i ==j )
    s[i]==[j]                   (j=i+i, adjacent)
    s[i]==[j] && s[i+1]==[j-1]  (j>i+i, not adjacent, this why our iterate direction chosen)
 }

       j=0 -->                                  0   1   2   3   4
        \ | b | a | b | a | d |             \ | b | a | b | a | d |
 i=0  | b | T |   |   |   |   |        0  | b | T | F*| T | F | T |
  ↓   -------------------------           ------------↗---↗---↗----
      | a |   | T |   |   |   |        1  | a |   | T | F*| T | F |
      -------------------------           ----------------↗---↗----
      | b |   |   | T |   |   |   =>   2  | b |   |   | T | F*| T |
      -------------------------           --------------------↗----
      | a |   |   |   | T |   |        3  | a |   |   |   | T | F*|
      -------------------------           -------------------------
      | d |   |   |   |   | T |        4  | d |   |   |   |   | T |
      -------------------------           -------------------------
    * means i,j is adjacent

 */
std::string longestPalindrome(std::string s) {
    size_t n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    size_t left = 0;
    size_t max_len = 1;
    for (size_t i = 0; i < n; ++i) {
        dp[i][i] = 1;
        for (size_t j = 0; j < i; ++j) {
            if (i == j + 1) { // adjacent
                dp[j][i] = s[i] == s[j];
            } else if (i > j + 1) {
                dp[j][i] = s[i] == s[j] && dp[j + 1][i - 1];
            }

            if (dp[j][i] && i - j + 1 > max_len) {
                left = j;
                max_len = i - j + 1;
            }
        }
    }
    return s.substr(left, max_len);
}

/**
////////// 6
 The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 (you may want to display this pattern in a fixed font for better legibility)
 P   A   H   N
 A P L S I I G
 Y   I   R
 And then read line by line: "PAHNAPLSIIGYIR"

 Write the code that will take a string and make this conversion given a number of rows:
 string convert(string s, int numRows);

 Example 1:
 Input: s = "PAYPALISHIRING", numRows = 3
 Output: "PAHNAPLSIIGYIR"

 Example 2:
 Input: s = "PAYPALISHIRING", numRows = 4
 Output: "PINALSIGYAHRPI"

 Explanation:
 P     I    N
 A   L S  I G
 Y A   H R
 P     I
 */
std::string convert(std::string s, int numRows) {
    if (numRows == 1) {
        return s;
    }
    std::string res;
    int s_len = s.length();
    int cycle = (numRows << 1) - 2;  // 2*(numRows-2) + 2
    for (int row = 0; row < numRows; row++) {
        for (int j = row; j < s_len; j += cycle) {
            res += s[j];
            int second_j = j + cycle - (row << 1); // j-row + cycle-row
            if (second_j < s_len && row != 0 && row != numRows - 1) {
                res += s[second_j];
            }
        }
    }
    return res;
}

/**
////////// 7
 Given a 32-bit signed integer, reverse digits of an integer.

 Example 1:
 Input: 123
 Output: 321

 Example 2:
 Input: -123
 Output: -321

 Example 3:
 Input: 120
 Output: 21
 Note:
 Assume we are dealing with an environment which could only store integers within the 32-bit
 signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem,
 assume that your function returns 0 when the reversed integer overflows.
 */
int reverse(int x) {
    int64_t res = x;
    int len = 0;
    do {
        ++len;
        res /= 10;
    } while (res);

    res = 0;
    while (len > 0) {
        res = res * 10 + x % 10;
        x /= 10;
        --len;
    }

    return (res > INT_MAX || res < INT_MIN) ? 0 : res;
}

FTEST(test_reverse) {
    LOG(INFO) << "reverse: " << reverse(0);
    LOG(INFO) << "reverse: " << reverse(1);
    LOG(INFO) << "reverse: " << reverse(-1);
    LOG(INFO) << "reverse: " << reverse(10);
    LOG(INFO) << "reverse: " << reverse(-10);
    LOG(INFO) << "reverse: " << reverse(123);
    LOG(INFO) << "reverse: " << reverse(-123);
    LOG(INFO) << "reverse: " << reverse(INT_MAX);
    LOG(INFO) << "reverse: " << reverse(INT_MIN);
    LOG(INFO) << "reverse: " << reverse(INT_MIN + 1);
    LOG(INFO) << "reverse: " << reverse(INT_MAX - 1);
}

/**
////////// 8
 Implement atoi which converts a string to an integer.
 The function first discards as many whitespace characters as necessary until the first
 non-whitespace character is found. Then, starting from this character,
 takes an optional initial plus or minus sign followed by as many numerical digits as possible,
 and interprets them as a numerical value.

 The string can contain additional characters after those that form the integral number,
 which are ignored and have no effect on the behavior of this function.

 If the first sequence of non-whitespace characters in str is not a valid integral number,
 or if no such sequence exists because either str is empty or it contains only whitespace
 characters, no conversion is performed.

 If no valid conversion could be performed, a zero value is returned.

 Note:
 Only the space character ' ' is considered as whitespace character.
 Assume we are dealing with an environment which could only store integers within the 32-bit
 signed integer range: [−2^31,  2^31 − 1]. If the numerical value is out of the range of
 representable values, INT_MAX (2^31 − 1) or INT_MIN (−2^31) is returned.

 Example 1:
 Input: "42"
 Output: 42

 Example 2:
 Input: "   -42"
 Output: -42
 Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

 Example 3:
 Input: "4193 with words"
 Output: 4193
 Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

 Example 4:
 Input: "words and 987"
 Output: 0
 Explanation: The first non-whitespace character is 'w', which is not a numerical
            digit or a +/- sign. Therefore no valid conversion could be performed.

 Example 5:
 Input: "-91283472332"
 Output: -2147483648
 Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
            Thefore INT_MIN (−2^31) is returned.
 */
int myAtoi(std::string str) {
    int64_t res = 0;
    size_t len = str.size();
    int state = 0;
    int sign = 1;
    for (size_t i = 0; i < len; ++i) {
        if (res * sign > INT_MAX) {
            return INT_MAX;
        }
        if (res * sign < INT_MIN) {
            return INT_MIN;
        }
        char c = str[i];
        if (state == 0) {
            if (c == ' ') {
                continue;
            }
            if (c >= '0' && c <= '9') {
                res = res * 10 + c - '0';
            } else if (c == '-' || c == '+') {
                sign = (c == '-' ? -1 : 1);
            } else {
                return 0;
            }

            state = 1;
            continue;
        }

        if (state == 1) {
            if (c >= '0' && c <= '9') {
                res = res * 10 + c - '0';
            } else {
                break;
            }
        }
    }
    res *= sign;
    return (res > INT_MAX ? INT_MAX : (res < INT_MIN ? INT_MIN : res));
}

FTEST(test_myAtoi) {
    LOG(INFO) << "INT_MIN:" << INT_MIN << ", INT_MAX:" << INT_MAX;
    LOG(INFO) << "myAtoi: " << myAtoi("");
    LOG(INFO) << "myAtoi: " << myAtoi("0");
    LOG(INFO) << "myAtoi: " << myAtoi(" 0");
    LOG(INFO) << "myAtoi: " << myAtoi("1");
    LOG(INFO) << "myAtoi: " << myAtoi(" 1");
    LOG(INFO) << "myAtoi: " << myAtoi(" 1aaa");
    LOG(INFO) << "myAtoi: " << myAtoi("-1  ");
    LOG(INFO) << "myAtoi: " << myAtoi("123");
    LOG(INFO) << "myAtoi: " << myAtoi("123bf1");
    LOG(INFO) << "myAtoi: " << myAtoi("123 bf1");
    LOG(INFO) << "myAtoi: " << myAtoi("-123");
    LOG(INFO) << "myAtoi: " << myAtoi(" -123");
    LOG(INFO) << "myAtoi: " << myAtoi(" -123gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" -2147483647 gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" -2147483648 gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" -2147483649 gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" 2147483646 gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" 2147483647 gf");
    LOG(INFO) << "myAtoi: " << myAtoi(" 2147483648 gf");
}

/**
////////// 9
 Determine whether an integer is a palindrome. An integer is a palindrome when it reads
 the same backward as forward.

 Example 1:
 Input: 121
 Output: true

 Example 2:
 Input: -121
 Output: false
 Explanation: From left to right, it reads -121. From right to left,
            it becomes 121-. Therefore it is not a palindrome.

 Example 3:
 Input: 10
 Output: false
 Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

 Follow up:
 Coud you solve it without converting the integer to a string?
 */
bool isPalindrome(int x) {
    if (x < 0 || (x != 0 && x % 10 == 0)) {
        return false;
    }

    int n = x;
    int h = 1;
    while (n / 10) {
        n /= 10;
        h *= 10;
    }

    int l = 10;
    while (l <= h) {
        if (((x / h) % 10) != ((x % l) / (l / 10))) {
            return false;
        }
        h /= 10;
        l *= 10;
    }
    return true;
}

FTEST(test_isPalindrome) {
    LOG(INFO) << "isPalindrome: " << isPalindrome(0);
    LOG(INFO) << "isPalindrome: " << isPalindrome(1);
    LOG(INFO) << "isPalindrome: " << isPalindrome(10);
    LOG(INFO) << "isPalindrome: " << isPalindrome(100);
    LOG(INFO) << "isPalindrome: " << isPalindrome(12);
    LOG(INFO) << "isPalindrome: " << isPalindrome(121);
    LOG(INFO) << "isPalindrome: " << isPalindrome(1000021);
    LOG(INFO) << "isPalindrome: " << isPalindrome(1200021);
    LOG(INFO) << "isPalindrome: " << isPalindrome(120021);
    LOG(INFO) << "isPalindrome: " << isPalindrome(1000030001);
}

/**
////////// 10
 Given an input string (s) and a pattern (p), implement regular expression matching
 with support for '.' and '*'.

 '.' Matches any single character.
 '*' Matches zero or more of the preceding element.
 The matching should cover the entire input string (not partial).

 Note:
 s could be empty and contains only lowercase letters a-z.
 p could be empty and contains only lowercase letters a-z, and characters like . or *.

 Example 1:
 Input:
 s = "aa"
 p = "a"
 Output: false
 Explanation: "a" does not match the entire string "aa".

 Example 2:
 Input:
 s = "aa"
 p = "a*"
 Output: true
 Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

 Example 3:
 Input:
 s = "ab"
 p = ".*"
 Output: true
 Explanation: ".*" means "zero or more (*) of any character (.)".

 Example 4:
 Input:
 s = "aab"
 p = "c*a*b"
 Output: true
 Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".

 Example 5:
 Input:
 s = "mississippi"
 p = "mis*is*p*."
 Output: false
 */

// TODO... backtracking method
bool isMatch(std::string s, std::string p) {
    size_t slen = s.size();
    size_t plen = p.size();
    std::vector<std::vector<bool>> dp(slen + 1, std::vector<bool>(plen + 1, false));

    dp[0][0] = true;
    for (size_t i = 1; i <= plen; ++i) {
        if (i >= 2 && p[i - 1] == '*') {
            dp[0][i] = dp[0][i - 2];
        }
    }
    for (size_t i = 1; i <= slen; ++i) {
        for (size_t j = 1; j <= plen; ++j) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            if (p[j - 1] == '*' && j >= 2) {
                dp[i][j] = dp[i][j - 2];
                if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] | dp[i - 1][j];
                }
            }
        }
    }
    return dp.back().back();
}

FTEST(test_isMatch) {
#define isMatcht(s, p, expect) do {                             \
        FEXP(isMatch(s, p), expect);                            \
        LOG(INFO) << s << "->" << p << ": " << expect;          \
    } while (0)

    isMatcht("", "", true);
    isMatcht("", "*", false);
    isMatcht("", "***", false);
    isMatcht("", ".", false);
    isMatcht("", "..", false);
    isMatcht("", "..*", false);
    isMatcht("", ".*", true);
    isMatcht("a", "*", false);
    isMatcht("aaa", "*", false);
    isMatcht("aaa", "***", false);
    isMatcht("aaa", ".", false);
    isMatcht("aaa", "..", false);
    isMatcht("aaa", "...", true);

    isMatcht("aaa", ".*", true);
    isMatcht("aaa", "..*", true);
    isMatcht("aaa", ".*.", true);
    isMatcht("aaa", ".*..", true);
    isMatcht("aaa", "..*.", true);
    isMatcht("aaa", "...*", true);

    isMatcht("abc", ".*", true);
    isMatcht("abc", "..*", true);
    isMatcht("abc", ".*.", true);
    isMatcht("abc", ".*..", true);
    isMatcht("abc", "..*.", true);
    isMatcht("abc", "...*", true);

    isMatcht("aab", ".*", true);
    isMatcht("aab", "..*", true);
    isMatcht("aab", ".*.", true);
    isMatcht("aab", ".*..", true);
    isMatcht("aab", "..*.", true);
    isMatcht("aab", "...*", true);

    isMatcht("abb", ".*", true);
    isMatcht("abb", "..*", true);
    isMatcht("abb", ".*.", true);
    isMatcht("abb", ".*..", true);
    isMatcht("abb", "..*.", true);
    isMatcht("abb", "...*", true);

    isMatcht("abbc", "ab*c", true);
    isMatcht("abbc", "ab*bc", true);
    isMatcht("abbc", "ab*bbc", true);

    isMatcht("abbcd", "ab*cd", true);
    isMatcht("abbcd", "ab*bcd", true);
    isMatcht("abbcd", "ab*bbca", false);
    isMatcht("abbcd", "ab*bcd", true);
}
