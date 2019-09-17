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
 */
std::string longestPalindrome(std::string s) {
    size_t n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    size_t left = 0;
    size_t max_len = 1;
    for (size_t i = 0; i < n; ++i) {
        dp[i][i] = 1;
        for (size_t j = 0; j < i; ++j) {
            if (i == j + 1) { // adjucent
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
    return "";
}

////////// 7
int reverse(int x) {
    return 0;
}

////////// 8
int myAtoi(std::string str) {
    return 0;
}

////////// 9
bool isPalindrome(int x) {
    return false;
}

////////// 10
bool isMatch(std::string s, std::string p) {
    return false;
}