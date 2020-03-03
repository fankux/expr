#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex16 {

/**
 ///////////// 161. One Edit Distance
Given two strings s and t, determine if they are both one edit distance apart.

Note:
There are 3 possiblities to satisify one edit distance apart:
Insert a character into s to get t
Delete a character from s to get t
Replace a character of s to get t

Example 1:
Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:
Input: s = "cab", t = "ad"
Output: false
Explanation: We cannot get t from s by only one step.

Example 3:
Input: s = "1203", t = "1213"
Output: true
Explanation: We can replace '0' with '1' to get t.
 */
bool isOneEditDistance(std::string s, std::string t) {
    return false;
}

/**
 ///////////// 162. Find Peak Element
A peak element is an element that is greater than its neighbors.
Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that nums[-1] = nums[n] = -∞.

Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5
Explanation: Your function can return either index number 1 where the peak element is 2,
             or index number 5 where the peak element is 6.

Note:
Your solution should be in logarithmic complexity.
 */
int findPeakElement(std::vector<int>& nums) {
    int l = 0;
    int r = nums.size() - 1; // to test nums[mid+1] safely, using closed right border
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] < nums[mid + 1]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return r;
}

FTEST(test_findPeakElement) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = findPeakElement(nns);
        LOG(INFO) << nums << " peak: " << re;
        return re;
    };

    t({});
    t({1});
    t({1, 2});
    t({2, 1});
    t({1, 1});
    t({1, 2, 1});
    t({1, 2, 1, 3});
    t({1, 2, 1, 3, 1});
    t({1, 2, 3, 1});
    t({1, 2, 1, 3, 5, 6, 4});
}

/**
 ///////////// 163. Missing Ranges
Given a sorted integer array where the range of elements are [0, 99] inclusive,
 return its missing ranges.
For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
 */
std::vector<std::string> findMissingRanges(std::vector<int>& nums, int lower, int upper) {
    return {};
}

/**
 ///////////// 164. Maximum Gap
Given an unsorted array, find the maximum difference between the successive elements
 in its sorted form.
Return 0 if the array contains less than 2 elements.

Example 1:
Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.

Example 2:
Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.

Note:
You may assume all elements in the array are non-negative integers
 and fit in the 32-bit signed integer range.
Try to solve it in linear time/space.

THOUGHTS:
 slot sort, then max gap must between adjucent slot;
 */
int maximumGap(std::vector<int>& nums) {
    int len = nums.size();
    if (len == 0) {
        return 0;
    }
    int mx = INT_MIN;
    int mn = INT_MAX;
    for (auto& n : nums) {
        mx = std::max(mx, n);
        mn = std::min(mn, n);
    }

    int slot_size = (mx - mn) / len + 1;
    int slot_count = (mx - mn) / slot_size + 1;
    std::vector<int> slot_maxs(slot_count, INT_MIN);
    std::vector<int> slot_mins(slot_count, INT_MAX);
    for (auto& n: nums) {
        int idx = (n - mn) / slot_size;
        slot_maxs[idx] = std::max(slot_maxs[idx], n);
        slot_mins[idx] = std::min(slot_mins[idx], n);
    }
    int res = 0;
    int pre = 0;
    for (int i = 1; i < slot_count; ++i) {
        if (slot_maxs[i] == INT_MIN || slot_mins[i] == INT_MAX) {
            continue;
        }
        res = std::max(res, slot_mins[i] - slot_maxs[pre]);
        pre = i;
    }
    return res;
}

FTEST(test_maximumGap) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = maximumGap(nns);
        LOG(INFO) << nums << " maximum gap: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({0}), 0);
    FEXP(t({1}), 0);
    FEXP(t({10}), 0);
    FEXP(t({1, 1}), 0);
    FEXP(t({1, 0}), 1);
    FEXP(t({0, 1}), 1);
    FEXP(t({0, 1, 3}), 2);
    FEXP(t({0, 3, 1}), 2);
    FEXP(t({3, 6, 9, 1}), 3);
}

/**
 ///////////// 165. Compare Version Numbers
Compare two version numbers version1 and version2.
 If version1 > version2 return 1;
 if version1 < version2 return -1;
 otherwise return 0.
You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three",
 it is the fifth second-level revision of the second first-level revision.
You may assume the default revision number for each level of a version number to be 0.
 For example, version number 3.4 has a revision number of 3 and 4 for its first
 and second level revision number. Its third and fourth level revision number are both 0.

Example 1:
Input: version1 = "0.1", version2 = "1.1"
Output: -1

Example 2:
Input: version1 = "1.0.1", version2 = "1"
Output: 1

Example 3:
Input: version1 = "7.5.2.4", version2 = "7.5.3"
Output: -1

Example 4:
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation: Ignoring leading zeroes, both “01” and “001" represent the same number “1”

Example 5:
Input: version1 = "1.0", version2 = "1.0.0"
Output: 0
Explanation: The first version number does not have a third level revision number,
 which means its third level revision number is default to "0"

Note:
Version strings are composed of numeric strings separated by dots .
 and this numeric strings may have leading zeroes.
Version strings do not start or end with dots, and they will not be two consecutive dots.
 */
int compareVersion(std::string version1, std::string version2) {
    int i = 0;
    int j = 0;
    int len1 = version1.size();
    int len2 = version2.size();

    int left = 0;
    while (i < len1 && j < len2) {
        left = i;
        while (i < len1 && version1[i] != '.') {
            ++i;
        }
        int v1 = std::strtoul(version1.c_str() + left, nullptr, 10);

        left = j;
        while (j < len2 && version2[j] != '.') {
            ++j;
        }
        int v2 = std::strtoul(version2.c_str() + left, nullptr, 10);
        ++i;
        ++j;
        if (v1 == v2) {
            continue;
        }
        return v1 < v2 ? -1 : 1;
    }
    while (i < len1) {
        left = i;
        while (i < len1 && version1[i] != '.') {
            ++i;
        }
        int v = std::strtoul(version1.c_str() + left, nullptr, 10);
        ++i;
        if (v == 0) {
            continue;
        }
        return v < 0 ? -1 : 1;
    }
    while (j < len2) {
        left = j;
        while (j < len2 && version2[j] != '.') {
            ++j;
        }
        int v = std::strtoul(version2.c_str() + left, nullptr, 10);
        ++j;
        if (v == 0) {
            continue;
        }
        return 0 < v ? -1 : 1;
    }
    return 0;
}

FTEST(test_compareVersion) {
    auto t = [](const std::string& version1, const std::string& version2) {
        auto re = compareVersion(version1, version2);
        LOG(INFO) << version1 << " compare " << version2 << ": " << re;
        return re;
    };

    FEXP(t("", ""), 0);
    FEXP(t("0", ""), 0);
    FEXP(t("0.0", ""), 0);
    FEXP(t("", "0"), 0);
    FEXP(t("", "0.0"), 0);
    FEXP(t("0.1", ""), 1);
    FEXP(t("", "0.1"), -1);
    FEXP(t("1", ""), 1);
    FEXP(t("", "1"), -1);
    FEXP(t("1.0", "1.0"), 0);
    FEXP(t("1.1", "1.1"), 0);
    FEXP(t("1.0", "1.1"), -1);
    FEXP(t("1.1", "1.0"), 1);
    FEXP(t("0.1", "1.1"), -1);
    FEXP(t("1.0.1", "1"), 1);
    FEXP(t("7.5.2.4", "7.5.3"), -1);
    FEXP(t("1.01", "1.001"), 0);
    FEXP(t("1.0", "1.0.0"), 0);
}

/**
 ///////////// 166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction,
 return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:
Input: numerator = 1, denominator = 2
Output: "0.5"

Example 2:
Input: numerator = 2, denominator = 1
Output: "2"

Example 3:
Input: numerator = 2, denominator = 3
Output: "0.(6)"

 THOUGHTS:
    once repeated remainder in fractional part, the fractional is Recurring.
    notice that, we use set to remeber the remainder instead of quotient,
    see:
    1. 1 / 333   quotient: 0, remainder: 1
    2. 10 / 333   quotient: 0, remainder: 10
    3. 100 / 333   quotient: 0, remainder: 100
    4. 1000 / 333   quotient: 3, remainder: 1
    step 1~3, quotient is same as 0, so that step 2 could output wrong result
    if we use quotient as a repeat checker.
    But 4 output the correct result. remainder is a good checker.

 */
std::string fractionToDecimal(int numerator, int denominator) {
    bool negative = ((numerator < 0) ^ (denominator < 0)) && numerator != 0;
    std::string res = negative ? "-" : "";
    int64_t num = abs((int64_t) numerator);
    int64_t deno = abs((int64_t) denominator);
    if (num < deno && num != 0) {
        res += "0.";
    } else {
        res += std::to_string(num / deno);
        num = num % deno;
        if (num != 0) {
            res += '.';
        }
    }
    int pos = 0;
    std::map<int64_t, int> ee;
    std::string fraction;
    while (num != 0) {
        auto entry = ee.find(num);
        if (entry != ee.end()) {
            fraction.insert(entry->second, "(");
            fraction += ")";
            break;
        } else {
            ee.emplace(num, pos++);
        }
        num *= 10;
        fraction += std::to_string(num / deno);
        num %= deno;
    }
    return res + fraction;
}

FTEST(test_fractionToDecimal) {
    auto t = [](int numerator, int denominator) {
        auto re = fractionToDecimal(numerator, denominator);
        LOG(INFO) << numerator << '/' << denominator << "=" << re;
        return re;
    };

    FEXP(t(0, 2), "0");
    FEXP(t(0, -2), "0");
    FEXP(t(1, 1), "1");
    FEXP(t(-1, 1), "-1");
    FEXP(t(1, -1), "-1");
    FEXP(t(-1, -1), "1");
    FEXP(t(1, 2), "0.5");
    FEXP(t(1, -2), "-0.5");
    FEXP(t(2, 1), "2");
    FEXP(t(11, 5), "2.2");
    FEXP(t(2, 3), "0.(6)");
    FEXP(t(4, 333), "0.(012)");
    FEXP(t(1, 6), "0.1(6)");
    FEXP(t(1, 333), "0.(003)");
    FEXP(t(-1, -2147483648), "0.0000000004656612873077392578125");
}

/**
 ///////////// 167. Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order,
 find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such
 that they add up to the target, where index1 must be less than index2.

Note:
Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use
 the same element twice.

Example:
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
 */
std::vector<int> twoSumII(std::vector<int>& numbers, int target) {
    int l = 0;
    int r = numbers.size() - 1;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target) {
            return {l + 1, r + 1};
        }
        if (sum < target) {
            ++l;
        } else {
            --r;
        }
    }
    return {};
}

/**
 ///////////// 168. Excel Sheet Column Title
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
    ...

Example 1:
Input: 1
Output: "A"

Example 2:
Input: 28
Output: "AB"

Example 3:
Input: 701
Output: "ZY"
 */
std::string convertToTitle(int n) {
    std::string res;
    while (n) {
        int remainder = (n - 1) % 26;
        res.insert(res.begin(), remainder + 'A');
        n = (n - remainder) / 26;
    }
    return res;
}

FTEST(test_convertToTitle) {
    auto t = [](int n) {
        auto re = convertToTitle(n);
        LOG(INFO) << n << " number: " << re;
        return re;
    };

    FEXP(t(0), "");
    FEXP(t(1), "A");
    FEXP(t(2), "B");
    FEXP(t(25), "Y");
    FEXP(t(26), "Z");
    FEXP(t(27), "AA");
    FEXP(t(28), "AB");
    FEXP(t(701), "ZY");
    FEXP(t(702), "ZZ");
    FEXP(t(703), "AAA");

}

/**
 ///////////// 169. Majority Element
Given an array of size n, find the majority element.
 The majority element is the element that appears more than ⌊ n/2 ⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:
Input: [3,2,3]
Output: 3

Example 2:
Input: [2,2,1,1,1,2,2]
Output: 2
 */
int majorityElement(std::vector<int>& nums) {
    int res = nums.front();
    int count = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        if (count == 0) {
            res = nums[i];
            ++count;
        } else {
            nums[i] == res ? ++count : --count;
        }
    }
    return res;
}

FTEST(test_majorityElement) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = majorityElement(nns);
        LOG(INFO) << nums << " majority: " << re;
        return re;
    };

    FEXP(t({1}), 1);
    FEXP(t({1, 1}), 1);
    FEXP(t({1, 2, 2}), 2);
    FEXP(t({1, 2, 2, 1}), 2);
    FEXP(t({1, 2, 2, 1, 1}), 1);
    FEXP(t({3, 2, 3}), 3);
    FEXP(t({2, 2, 1, 1, 1, 2, 2}), 2);
}

/**
 ///////////// 170. Two Sum III - Data structure design
Design and implement a TwoSum class. It should support the following operations:add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false
 */
class TwoSumIII {
public:
    void add(int number) {
    }

    bool find(int value) {
        return false;
    }
};

}