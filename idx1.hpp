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
    std::unordered_map<int, std::string> mm{
            {0, ""},
            {1, "I"},
            {2, "II"},
            {3, "III"},
            {4, "IV"},
            {5, "V"},
            {6, "VI"},
            {7, "VII"},
            {8, "VIII"},
            {9, "IX"},
            {10, "X"},
            {20, "XX"},
            {30, "XXX"},
            {40, "XL"},
            {50, "L"},
            {60, "LX"},
            {70, "LXX"},
            {80, "LXXX"},
            {90, "XC"},
            {100, "C"},
            {200, "CC"},
            {300, "CCC"},
            {400, "CD"},
            {500, "D"},
            {600, "DC"},
            {700, "DCC"},
            {800, "DCCC"},
            {900, "CM"},
            {1000, "M"},
            {2000, "MM"},
            {3000, "MMM"}
    };
    int a = num / 1000;
    int b = (num % 1000) / 100;
    int c = (num % 100) / 10;
    int d = num % 10;
    return mm[a * 1000] + mm[b * 100] + mm[c * 10] + mm[d];
}

FTEST(test_intToRoman) {
    auto t = [](int num) {
        std::string c = intToRoman(num);
        LOG(INFO) << num << ": " << c;
        return c;
    };

    FEXP(t(0), "");
    FEXP(t(1), "I");
    FEXP(t(2), "II");
    FEXP(t(3), "III");
    FEXP(t(4), "IV");
    FEXP(t(5), "V");
    FEXP(t(6), "VI");
    FEXP(t(7), "VII");
    FEXP(t(8), "VIII");
    FEXP(t(9), "IX");
    FEXP(t(10), "X");
    FEXP(t(11), "XI");
    FEXP(t(14), "XIV");
    FEXP(t(15), "XV");
    FEXP(t(58), "LVIII");
    FEXP(t(1994), "MCMXCIV");
    FEXP(t(3999), "MMMCMXCIX");
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
    int mm[128];
    mm['I'] = 1;
    mm['V'] = 5;
    mm['X'] = 10;
    mm['L'] = 50;
    mm['C'] = 100;
    mm['D'] = 500;
    mm['M'] = 1000;

    int res = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if ((i < s.size() - 1 && mm[s[i]] >= mm[s[i + 1]]) || i == s.size() - 1) {
            res += mm[s[i]];
        } else {
            res -= mm[s[i]];
        }
    }
    return res;
}

FTEST(test_romanToInt) {
    auto t = [](const std::string& s) {
        int c = romanToInt(s);
        LOG(INFO) << s << ": " << c;
        return c;
    };

    FEXP(t(""), 0);
    FEXP(t("I"), 1);
    FEXP(t("II"), 2);
    FEXP(t("III"), 3);
    FEXP(t("IV"), 4);
    FEXP(t("V"), 5);
    FEXP(t("VI"), 6);
    FEXP(t("VII"), 7);
    FEXP(t("VIII"), 8);
    FEXP(t("IX"), 9);
    FEXP(t("X"), 10);
    FEXP(t("XI"), 11);
    FEXP(t("XIV"), 14);
    FEXP(t("XV"), 15);
    FEXP(t("LVIII"), 58);
    FEXP(t("MCMXCIV"), 1994);
    FEXP(t("MMMCMXCIX"), 3999);
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
    if (strs.empty()) {
        return "";
    }

    std::string res;
    for (size_t i = 0;; i++) {
        for (size_t j = 0; j < strs.size(); j++) {
            if ((i >= strs[j].size()) || (j && strs[j][i] != strs[j - 1][i])) {
                return res;
            }
        }
        res += strs[0][i];
    }
    return res;
}

FTEST(test_longestCommonPrefix) {
    auto t = [](const std::vector<std::string>& ss) {
        std::vector<std::string> strs = ss;
        std::string c = longestCommonPrefix(strs);
        LOG(INFO) << ss << ": " << c;
        return c;
    };

    FEXP(t({}), "");
    FEXP(t({""}), "");
    FEXP(t({"a"}), "a");
    FEXP(t({"a", "b"}), "");
    FEXP(t({"a", "a"}), "a");
    FEXP(t({"abc", "abd"}), "ab");
    FEXP(t({"flower", "flow", "flight"}), "fl");
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
    if (nums.size() < 3) {
        return {};
    }
    std::sort(nums.begin(), nums.end());
    if (nums.front() > 0) {
        return {};
    }
    std::vector<std::vector<int>> res;
    for (size_t i = 0; i < nums.size() - 2; ++i) {
        if (i > 0 && nums[i - 1] == nums[i]) {
            continue;
        }

        int target_in = 0 - nums[i];
        int l = i + 1;
        int h = nums.size() - 1;
        while (l < h) {
            int sum = nums[l] + nums[h];
            if (target_in == sum) {
                res.emplace_back(std::vector<int>{nums[i], nums[l], nums[h]});
                while (l < h && nums[l] == nums[l + 1]) {
                    ++l;
                }
                while (l < h && nums[h] == nums[h - 1]) {
                    --h;
                }
                ++l;
                --h;
            } else if (sum < target_in) {
                ++l;
            } else {
                --h;
            }
        }
    }
    return res;
}

FTEST(test_threeSum) {
    auto t = [](const std::vector<int>& nums, int sum) {
        std::vector<int> nums_in = nums;
        LOG(INFO) << nums_in << " result: " << threeSum(nums_in);
    };

    t({1, 0, 2}, 0);
    t({-1, -3, -5}, 0);
    t({-1, 0, 1}, 0);
    t({-1, -1, 0, 1, 0, 1}, 0);
    t({-1, 0, -1, 0, 1, 1}, 0);
    t({-1, -1, 0, 0, 1, 1}, 0);
    t({-1, 0, 1, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, 0);

    t({1, 0, 2}, 3);
    t({-1, -3, -5}, -9);
    t({-1, 0, 1}, 0);
    t({-1, -1, 0, 1, 0, 1}, 2);
    t({-1, 0, -1, 0, 1, 1}, -2);
    t({-1, -1, 0, 0, 1, 1}, 1);
    t({-1, 0, 1, -1, 0, 1}, -1);
    t({-3, 1, 2, -1, 0, 1}, 3);
    t({-3, 1, 2, -1, 0, 1}, 4);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
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
    int res = 0;
    int min = INT_MAX;
    std::sort(nums.begin(), nums.end());

    for (size_t i = 0; i < nums.size() - 2; ++i) {
        int target_in = target - nums[i];
        int l = i + 1;
        int h = nums.size() - 1;
        while (l < h) {
            bool dedup = false;
            int sum = nums[l] + nums[h];
            int delta = abs(target_in - sum);
            if (delta <= min) {
                min = delta;
                res = sum + nums[i];
                dedup = true;
            }

            if (sum < target_in) {
                while (dedup && l < h && nums[l] == nums[l + 1]) {
                    ++l;
                }
                ++l;
            } else {
                while (dedup && l < h && nums[h] == nums[h - 1]) {
                    --h;
                }
                --h;
            }
        }
    }
    return res;
}

FTEST(test_threeSumClosest) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nums_in = nums;
        int c = threeSumClosest(nums_in, target);
        LOG(INFO) << nums_in << " find: " << target << ", result: " << c;
        return c;
    };

    FEXP(t({-1, 2, 1, -4}, 1), 2);

    t({1, 0, 2}, 0);
    t({-1, -3, -5}, 0);
    t({-1, 0, 1}, 0);
    t({-1, -1, 0, 1, 0, 1}, 0);
    t({-1, 0, -1, 0, 1, 1}, 0);
    t({-1, -1, 0, 0, 1, 1}, 0);
    t({-1, 0, 1, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, 0);

    t({1, 0, 2}, 3);
    t({-1, -3, -5}, -9);
    t({-1, 0, 1}, 0);
    t({-1, -1, 0, 1, 0, 1}, 2);
    t({-1, 0, -1, 0, 1, 1}, -2);
    t({-1, -1, 0, 0, 1, 1}, 1);
    t({-1, 0, 1, -1, 0, 1}, -1);
    t({-3, 1, 2, -1, 0, 1}, 3);
    t({-3, 1, 2, -1, 0, 1}, 4);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
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
    if (nums.size() < 4) {
        return {};
    }
    std::sort(nums.begin(), nums.end());
    if (nums.front() > 0) {
        return {};
    }
    std::vector<std::vector<int>> res;
    for (size_t i = 0; i < nums.size() - 3; ++i) {
        if (i > 0 && nums[i - 1] == nums[i]) {
            continue;
        }

        for (size_t j = i + 1; j < nums.size() - 2; ++j) {
            if (j > i + 1 && nums[j - 1] == nums[j]) {
                continue;
            }

            int target_in = target - nums[i];
            int l = j + 1;
            int h = nums.size() - 1;
            while (l < h) {
                int sum = nums[l] + nums[h] + nums[j];
                if (target_in == sum) {
                    res.emplace_back(std::vector<int>{nums[i], nums[j], nums[l], nums[h]});
                    while (l < h && nums[l] == nums[l + 1]) {
                        ++l;
                    }
                    while (l < h && nums[h] == nums[h - 1]) {
                        --h;
                    }
                    ++l;
                    --h;
                } else if (sum < target_in) {
                    ++l;
                } else {
                    --h;
                }
            }
        }
    }
    return res;
}

FTEST(test_fourSum) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nums_in = nums;
        auto c = fourSum(nums_in, target);
        LOG(INFO) << nums_in << " find: " << target << " sum result: " << c;
        return c;
    };

    t({1, 0, -1, 0, -2, 2}, 0);

    t({1, 0, 2, -3}, 0);
    t({-1, -3, -5, 0}, 0);
    t({-1, 0, 1, 0}, 0);
    t({-1, -1, 0, 1, 0, 1}, 0);
    t({-1, 0, -1, 0, 1, 1}, 0);
    t({-1, -1, 0, 0, 1, 1}, 0);
    t({-1, 0, 1, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1}, 0);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, 0);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -1);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, 1);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, 2);

    t({1, 0, 2}, 3);
    t({-1, -3, -5}, -9);
    t({-1, 0, 1}, 0);
    t({-1, -1, 0, 1, 0, 1}, 3);
    t({-1, 0, -1, 0, 1, 1}, -2);
    t({-1, -1, 0, 0, 1, 1}, 1);
    t({-1, 0, 1, -1, 0, 1}, -1);
    t({-3, 1, 2, -1, 0, 1}, 3);
    t({-3, 1, 2, -1, 0, 1}, 4);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    t({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
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
    if (s.size() <= 1) {
        return s.empty();
    }
    std::map<char, char> pairs{
            {')', '('},
            {']', '['},
            {'}', '{'}
    };
    std::stack<char> ss;
    for (auto c : s) {
        auto ee = pairs.find(c);
        if (ee != pairs.end()) {
            if (ss.empty() || ss.top() != ee->second) {
                return false;
            }
            ss.pop();
        } else {
            ss.push(c);
        }
    }
    return ss.empty();
}