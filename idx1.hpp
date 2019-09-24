#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;

/**
 //// 11. Container With Most Water
 Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai).
 n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
 Find two lines, which together with x-axis forms a container,
 such that the container contains the most water.

 Note: You may not slant the container and n is at least 2.
 The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case,
 the max area of water (blue section) the container can contain is 49.

 Example:
 Input: [1,8,6,2,5,4,8,3,7]
 Output: 49
 */
int maxArea(std::vector<int>& height) {
    int max = 0;
    int l = 0;
    int h = height.size() - 1;
    while (l < h) {
        max = std::max(max, std::min(height[l], height[h]) * (h - l));
        if (height[l] < height[h]) {
            ++l;
        } else {
            --h;
        }
    }
    return max;
}

FTEST(test_maxArea) {
    auto t = [](const std::vector<int>& s) {
        std::vector<int> height = s;
        int c = maxArea(height);
        LOG(INFO) << height << ": " << c;
        return c;
    };

    FEXP(t({1, 8, 6, 2, 5, 4, 8, 3, 7}), 49);
}

/**
 //// 12. Integer to Roman
 Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

 Symbol       Value
 I             1
 V             5
 X             10
 L             50
 C             100
 D             500
 M             1000
 For example, two is written as II in Roman numeral, just two one's added together.
 Twelve is written as, XII, which is simply X + II.
 The number twenty seven is written as XXVII, which is XX + V + II.

 Roman numerals are usually written largest to smallest from left to right. However,
 the numeral for four is not IIII. Instead, the number four is written as IV.
 Because the one is before the five we subtract it making four.
 The same principle applies to the number nine, which is written as IX.
 There are six instances where subtraction is used:

 I can be placed before V (5) and X (10) to make 4 and 9.
 X can be placed before L (50) and C (100) to make 40 and 90.
 C can be placed before D (500) and M (1000) to make 400 and 900.
 Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

 Example 1:
 Input: 3
 Output: "III"

 Example 2:
 Input: 4
 Output: "IV"

 Example 3:
 Input: 9
 Output: "IX"

 Example 4:
 Input: 58
 Output: "LVIII"
 Explanation: L = 50, V = 5, III = 3.

 Example 5:
 Input: 1994
 Output: "MCMXCIV"
 Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 */
std::string intToRoman(int num) {
    std::string res;



    return res;
}

/**
 //// 13. Roman to Integer
 Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 Symbol       Value
 I             1
 V             5
 X             10
 L             50
 C             100
 D             500
 M             1000
 For example, two is written as II in Roman numeral, just two one's added together.
 Twelve is written as, XII, which is simply X + II.
 The number twenty seven is written as XXVII, which is XX + V + II.

 Roman numerals are usually written largest to smallest from left to right.
 However, the numeral for four is not IIII. Instead, the number four is written as IV.
 Because the one is before the five we subtract it making four.
 The same principle applies to the number nine, which is written as IX.
 There are six instances where subtraction is used:

 I can be placed before V (5) and X (10) to make 4 and 9.
 X can be placed before L (50) and C (100) to make 40 and 90.
 C can be placed before D (500) and M (1000) to make 400 and 900.
 Given a roman numeral, convert it to an integer.
 Input is guaranteed to be within the range from 1 to 3999.

 Example 1:
 Input: "III"
 Output: 3

 Example 2:
 Input: "IV"
 Output: 4

 Example 3:
 Input: "IX"
 Output: 9

 Example 4:
 Input: "LVIII"
 Output: 58
 Explanation: L = 50, V= 5, III = 3.

 Example 5:
 Input: "MCMXCIV"
 Output: 1994
 Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 */
int romanToInt(std::string s) {
    return 0;
}

/**
 //// 14. Longest Common Prefix
 Write a function to find the longest common prefix string amongst an array of strings.
 If there is no common prefix, return an empty string "".

 Example 1:
 Input: ["flower","flow","flight"]
 Output: "fl"

 Example 2:
 Input: ["dog","racecar","car"]
 Output: ""
 Explanation: There is no common prefix among the input strings.

 Note:
 All given inputs are in lowercase letters a-z.
 */
std::string longestCommonPrefix(std::vector<std::string>& strs) {
    return "";
}

/**
 //// 15. 3Sum
 Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 Find all unique triplets in the array which gives the sum of zero.

 Note:
 The solution set must not contain duplicate triplets.

 Example:
 Given array nums = [-1, 0, 1, 2, -1, -4],

 A solution set is:
 [
   [-1, 0, 1],
   [-1, -1, 2]
 ]
 */
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    return {};
}

/**
 //// 16. 3Sum Closest
 Given an array nums of n integers and an integer target,
 find three integers in nums such that the sum is closest to target.
 Return the sum of the three integers.
 You may assume that each input would have exactly one solution.

 Example:
 Given array nums = [-1, 2, 1, -4], and target = 1.
 The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
int threeSumClosest(std::vector<int>& nums, int target) {
    return 0;
}

/**
 //// 17. Letter Combinations of a Phone Number
 Given a string containing digits from 2-9 inclusive, return all possible letter combinations
 that the number could represent.
 A mapping of digit to letters (just like on the telephone buttons) is given below.
 Note that 1 does not map to any letters.

 Example:
 Input: "23"
 Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

 Note:
 Although the above answer is in lexicographical order, your answer could be in any order you want.
 */
std::vector<std::string> letterCombinations(std::string digits) {
    return {};
}

/**
 //// 18. 4Sum
 Given an array nums of n integers and an integer target, are there elements a, b, c,
 and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array
 which gives the sum of target.

 Note:
 The solution set must not contain duplicate quadruplets.

 Example:
 Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

 A solution set is:
 [
   [-1,  0, 0, 1],
   [-2, -1, 1, 2],
   [-2,  0, 0, 2]
 ]
 */
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    return {};
}

/**
 //// 19. Remove Nth Node From End of List
 Given a linked list, remove the n-th node from the end of list and return its head.

 Example:
 Given linked list: 1->2->3->4->5, and n = 2.
 After removing the second node from the end, the linked list becomes 1->2->3->5.

 Note:
 Given n will always be valid.

 Follow up:
 Could you do this in one pass?
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    return nullptr;
}

/**
 //// 20. Valid Parentheses
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 determine if the input string is valid.

 An input string is valid if:
 Open brackets must be closed by the same type of brackets.
 Open brackets must be closed in the correct order.
 Note that an empty string is also considered valid.

 Example 1:
 Input: "()"
 Output: true

 Example 2:
 Input: "()[]{}"
 Output: true

 Example 3:
 Input: "(]"
 Output: false

 Example 4:
 Input: "([)]"
 Output: false

 Example 5:
 Input: "{[]}"
 Output: true
 */
bool isValid(std::string s) {
    return true;
}