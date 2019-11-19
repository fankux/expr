#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 41. First Missing Positive
 Given an unsorted integer array, find the smallest missing positive integer.

 Example 1:
 Input: [1,2,0]
 Output: 3

 Example 2:
 Input: [3,4,-1,1]
 Output: 2

 Example 3:
 Input: [7,8,9,11,12]
 Output: 1

 Note:
 Your algorithm should run in O(n) time and uses constant extra space.

 THOUTGHTS:
    use output as working space to fullfill constant extra space.
    1. try to make each number to the place it should be(num == i+1), we do:
        - if num <=0 or num > input length, ignore
        - if num != num[num - 1], swap them, try it untill loop end
        (not that we can not do sort that could exceed O(n) time,
        by swapping each number which no at the right position with the one where it should be,
        finally we could get a roughly sorted nums, and once a num to the right postion,
        no more swap action happend to it anymore. it's still O(n) time)
    2. travse nums, if num != i+1, the i+1 is the result, else length+1 is the result

 EXAMPLE:
    3  4  -1  1
   -1  4   3  1     i=0 (3 swap -1, -1<0, loop end)
   -1  1   3  4     i=1 (4 swap 1)
   1  -1   3  4     i=1 (1 placed to right position, this will always happend if 1 exist. -1<0, loop end)
   1  -1   3  4     i=2 (3 already placed at right position, loop end)
   1  -1   3  4     i=3 (4 already placed at right position, loop end)
   -------------------------
   1  -1   3   4
       |
   -1 != 2, result is 2
*/
int firstMissingPositive(std::vector<int>& nums) {
    size_t n = nums.size();
    for (size_t i = 0; i < n; ++i) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            std::swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return n + 1;
}

FTEST(test_firstMissingPositive) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto n = firstMissingPositive(nns);
        LOG(INFO) << nums << " first missing positive: " << n;
        return n;
    };
    t({1, 2, 0});
    t({3, 4, -1, 1});
    t({7, 8, 9, 11, 12});
}

/**
 ///////////// 42. Trapping Rain Water
 Given n non-negative integers representing an elevation map where the width of each bar is 1,
 compute how much water it is able to trap after raining.

    |
    |
  3 |                    ____
    |                    |  |
  2 |        ____        |  |___  ____
    |        |  |========|     |==|  |
  1 |  ____  |  |========|     |==|  |___
    |  |  |==|     |==|                 |
  0 |__|__|==|_____|==|_________________|_______
     0  1  2  3  4  5  6  7  8  9  10 11

 The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case,
 6 units of rain water (blue section) are being trapped.
 Thanks Marcos for contributing this image!

 Example:
 Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 Output: 6

 THOUGHTS:
 EXAMPLE(STACK):
 we look at partial of above example, [0  3  2  1  0  3]:

  3 |  ____        ____
    |  |  |========|  |
  2 |  |  |========|  |
    |  |     |=====|  |
  1 |  |     |=====|  |
    |  |        |==|  |
  0 |__|________|==|__|_______
     0  1  2  3  4  5

 0                  stack: [0]
 0  3               stack: [3], pop 0: 3>0, stack empty, continue
 0  3  2  1  0      stack: [3,2,1,0], skip some steps
 0  3  2  1  0  3   stack: [3,2,1]
                    - 3>top(0), we start to calc rectangle are,
                        pop 0 as bottom, now stack top(1, idx:3) is the left border:
                        area=(idx(3) - left - 1) * (min(height[stack.top], height[idx]) - height[bottom])
 0  3  2  1  0  3   stack: [3,2]
                    - continue, 3>top(1), pop 1 as bottom, calc reactangle area between idx:2 and idx:5
 0  3  2  1  0  3   stack: [3]
                    - continue, 3>top(2), pop 2 as bottom, calc reactangle area between idx:1 and idx:5

  3 |  ____        ____       3 |  ____        ____       3 |  ____        ____
    |  |  |========|  |         |  |  |========|  |         |  |  |xxxxxxxx|  |
  2 |  |  |========|  |       2 |  |  |========|  |       2 |  |  |xxxxxxxx|  |
    |  |     |=====|  |  ==>    |  |     |xxxxx|  |  ==>    |  |     |=====|  |
  1 |  |     |=====|  |       1 |  |     |xxxxx|  |       1 |  |     |=====|  |
    |  |        |xx|  |         |  |        |==|  |         |  |        |==|  |
  0 |__|________|xx|__|__     0 |__|________|==|__|__     0 |__|________|==|__|__
     0  1  2  3  4  5            0  1  2  3  4  5            0  1  2  3  4  5


 */
int trap(std::vector<int>& height) {
    int res = 0;
    int len = height.size();
    if (len == 0) {
        return 0;
    }
    auto dp_func = [&] {
        std::vector<int> dpl(len, 0);
        dpl[0] = height[0];
        for (int i = 1; i < len; ++i) {
            dpl[i] = std::max(height[i], dpl[i - 1]);
        }
        std::vector<int> dpr(len, 0);
        dpr[len - 1] = height[len - 1];
        for (int i = len - 2; i >= 0; --i) {
            dpr[i] = std::max(height[i], dpr[i + 1]);
        }
        for (int i = 1; i < len; ++i) {
            res += std::min(dpl[i], dpr[i]) - height[i];
        }
    };
    auto dp_less_mem_func = [&] {
        int max = 0;
        std::vector<int> dp(len, 0);
        for (int i = 0; i < len; ++i) {
            dp[i] = max;
            max = std::max(height[i], max);
        }
        max = 0;
        for (int i = len - 1; i >= 0; --i) {
            dp[i] = std::min(dp[i], max);
            max = std::max(height[i], max);
            if (dp[i] > height[i]) {
                res += dp[i] - height[i];
            }
        }
    };
    auto stack_func = [&] {
        std::stack<int> ss;
        for (int i = 0; i < len; ++i) {
            while (!ss.empty() && height[i] > height[ss.top()]) {
                int prev_height = height[ss.top()];
                ss.pop();
                if (!ss.empty()) { // must not empty, otherwise no water could be traped
                    int left = ss.top();
                    // add rectangle area
                    res += (i - left - 1) * (std::min(height[i], height[left]) - prev_height);
                }
            }
            ss.push(i);
        }
    };
    auto two_pointer_func = [&] {
        int left = 0;
        int right = len - 1;
        int left_max = 0;
        int right_max = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {                            // there forms a water bottom, count one
                    res += left_max - height[left];
                }
                ++left;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    res += right_max - height[right];
                }
                --right;
            }
        }
    };
    stack_func();
    return res;
}

FTEST(test_trap) {
    auto t = [](const std::vector<int>& height) {
        std::vector<int> nns = height;
        auto n = trap(nns);
        LOG(INFO) << height << " first max trap wather: " << n;
        return n;
    };

    t({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
    t({0, 3, 2, 1, 0, 3});
}

/**
 ///////////// 43. Multiply Strings
 Given two non-negative integers num1 and num2 represented as strings,
 return the product of num1 and num2, also represented as a string.

 Example 1:
 Input: num1 = "2", num2 = "3"
 Output: "6"

 Example 2:
 Input: num1 = "123", num2 = "456"
 Output: "56088"

 Note:
 1. The length of both num1 and num2 is < 110.
 2. Both num1 and num2 contain only digits 0-9.
 3. Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 4. You must not use any built-in BigInteger library or convert the inputs to integer directly.
 */
std::string multiply(std::string num1, std::string num2) {
    int l1 = num1.size();
    int l2 = num2.size();
    std::vector<int> vals(l1 + l2, 0);
    for (int i = l1 - 1; i >= 0; --i) {
        for (int j = l2 - 1; j >= 0; --j) {
            int n = (num1[i] - '0') * (num2[j] - '0') + vals[i + j + 1];
            vals[i + j + 1] = n % 10;
            vals[i + j] += n / 10;    // here could be exceed 10, last routine should fix it
        }
    }
    std::string res;
    for (int v : vals) {
        if (!res.empty() || v != 0) {
            res.push_back(v + '0');
        }
    }
    return res.empty() ? "0" : res;
}

FTEST(test_multiply) {
    auto t = [](const std::string& num1, const std::string& num2) {
        auto n = multiply(num1, num2);
        LOG(INFO) << num1 << "*" << num2 << "=" << n;
        return n;
    };

    FEXP(t("0", "0"), "0");
    FEXP(t("0", "1"), "0");
    FEXP(t("1", "0"), "0");
    FEXP(t("1", "1"), "1");
    FEXP(t("2", "3"), "6");
    FEXP(t("100", "1"), "100");
    FEXP(t("101", "1"), "101");
    FEXP(t("100", "10"), "1000");
    FEXP(t("100", "100"), "10000");
    FEXP(t("123", "456"), "56088");
    FEXP(t("123456789", "987654321"), "121932631112635269");
}

/**
 ///////////// 44. Wildcard Matching
 Given an input string (s) and a pattern (p),
 implement wildcard pattern matching with support for '?' and '*'.

 '?' Matches any single character.
 '*' Matches any sequence of characters (including the empty sequence).
 The matching should cover the entire input string (not partial).

 Note:
 s could be empty and contains only lowercase letters a-z.
 p could be empty and contains only lowercase letters a-z, and characters like ? or *.

 Example 1:
 Input:
 s = "aa"
 p = "a"
 Output: false
 Explanation: "a" does not match the entire string "aa".

 Example 2:
 Input:
 s = "aa"
 p = "*"
 Output: true
 Explanation: '*' matches any sequence.

 Example 3:
 Input:
 s = "cb"
 p = "?a"
 Output: false
 Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

 Example 4:
 Input:
 s = "adceb"
 p = "*a*b"
 Output: true
 Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

 Example 5:
 Input:
 s = "acdcb"
 p = "a*c?b"
 Output: false

 THOUGHTS:
 DP state transfer:
        (at first row)if p[j]=='*':
            see LEFT

        if s[i]==p[j] or p[j]=='?':
            see LEFT-TOP
        elif p[j]=='*':
            see LEFT-or-TOP

   | \ |' '| a | * | c | ? | b |
   |' '| T | F → F | F | F | F |
   |-------↘-----↓-----↘-------|
   | a | F | T → T | F | F | F |
   |-------------↓-↘---↘-------|
   | c | F | F → T | T | F | F |
   |-------------↓-----↘-------|
   | d | F | F → T | F | T | F |
   |-------------↓-↘---↘-------|
   | c | F | F → T | T | F | F |
   |-------------↓-----↘---↘---|
   | b | F | F → T | F | T | F |
   |---------------------------|

    TODO.. not dp method
 */
bool isWildcardMatch(std::string s, std::string p) {
    size_t slen = s.size();
    size_t plen = p.size();
    std::vector<std::vector<bool>> dp(slen + 1, std::vector<bool>(plen + 1, false));
    dp[0][0] = true;
    for (size_t i = 1; i <= plen; ++i) {
        if (p[i - 1] == '*') {
            dp[0][i] = dp[0][i - 1];
        }
    }
    for (size_t i = 1; i <= slen; ++i) {
        for (size_t j = 1; j <= plen; ++j) {
            if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
            }
        }
    }
    return dp.back().back();
}

FTEST(test_isWildcardMatch) {
    auto t = [](const std::string& num1, const std::string& num2) {
        auto n = isWildcardMatch(num1, num2);
        LOG(INFO) << num1 << " macth " << num2 << ": " << n;
        return n;
    };
    FEXP(t({""}, {""}), true);
    FEXP(t({"aa"}, {"a"}), false);
    FEXP(t({"aa"}, {"*"}), true);
    FEXP(t({"cb"}, {"?a"}), false);
    FEXP(t({"adceb"}, {"*a*b"}), true);
    FEXP(t({"acdcb"}, {"a*c?b"}), false);
}

/**
 ///////////// 45. Jump Game II
 Given an array of non-negative integers, you are initially positioned at the first index of the array.
 Each element in the array represents your maximum jump length at that position.
 Your goal is to reach the last index in the minimum number of jumps.

 Example:
 Input: [2,3,1,1,4]
 Output: 2
 Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.

 Note:
 You can assume that you can always reach the last index.

 THOUGHTS:
 greedy, BFS, each num as a node,
 - check the each next node of current can jump to,
 - find the max one as next current.
 - if max exceed last, return result.
 - if not max one(less than current), there is no result.

 */
int jump(std::vector<int>& nums) {
    int len = nums.size();
    int res = 0;
    int cur = 0;
    while (cur < len - 1) {
        int max = 0;
        for (size_t i = 0; i <= nums[cur]; ++i) {
            int idx = cur + i;
            if (idx >= len - 1) { // result happend when detect
                return res + 1;
            }
            if (idx + nums[idx] > max + nums[max]) {
                max = idx;
            }
        }
        if (max == cur) {   // no larger next node found, no result
            return -1;
        }
        cur = max;
        ++res;
    }
    return res;
}

FTEST(test_jump) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> ns = nums;
        auto n = jump(ns);
        LOG(INFO) << nums << " jump min count: " << n;
        return n;
    };

    FEXP(t({1}), 0);
    FEXP(t({1, 2}), 1);
    FEXP(t({2, 3, 1, 1, 4}), 2);
}

/**
 ///////////// 46. Permutations
 Given a collection of distinct integers, return all possible permutations.

 Example:
 Input: [1,2,3]
 Output:
 [
   [1,2,3],
   [1,3,2],
   [2,1,3],
   [2,3,1],
   [3,1,2],
   [3,2,1]
 ]
 */
std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    std::function<void(std::vector<int>&, std::vector<bool>&)> visit_r;
    visit_r = [&](std::vector<int>& re, std::vector<bool>& visit) {
        if (re.size() == nums.size()) {
            res.emplace_back(re);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (!visit[i]) {
                re.emplace_back(nums[i]);
                visit[i] = true;
                visit_r(re, visit);
                re.pop_back();
                visit[i] = false;
            }
        }
    };
    auto visit_func = [&] {
        std::vector<int> re;
        std::vector<bool> visit(nums.size(), false);
        visit_r(re, visit);
    };
    std::function<void(int)> swap_func;
    swap_func = [&](int start) {
        if (start >= nums.size()) {
            res.emplace_back(nums);
            return;
        }
        for (size_t i = start; i < nums.size(); ++i) {
            std::swap(nums[i], nums[start]);
            swap_func(start + 1);
            std::swap(nums[i], nums[start]);
        }
    };
//    visit_func();
    swap_func(0);
    return res;
}

FTEST(test_permute) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> ns = nums;
        auto n = permute(ns);
        LOG(INFO) << nums << " premutations: " << n;
        return n;
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
}

/**
 ///////////// 47. Permutations II
 Given a collection of numbers that might contain duplicates, return all possible unique permutations.

 Example:
 Input: [1,1,2]
 Output:
 [
   [1,1,2],
   [1,2,1],
   [2,1,1]
 ]
 */
std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    std::function<void(std::vector<int>&, std::vector<bool>&)> visit_r;
    visit_r = [&](std::vector<int>& re, std::vector<bool>& visit) {
        if (re.size() == nums.size()) {
            res.emplace_back(re);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (i > 0 && visit[i - 1] && nums[i] == nums[i - 1]) {
                continue;
            }
            if (!visit[i]) {
                re.emplace_back(nums[i]);
                visit[i] = true;
                visit_r(re, visit);
                re.pop_back();
                visit[i] = false;
            }
        }
    };
    auto visit_func = [&] {
        std::vector<int> re;
        std::vector<bool> visit(nums.size(), false);
        visit_r(re, visit);
    };
    std::function<void(int, std::string)> swap_func;
    swap_func = [&](int start, std::string indention) {
        if (start >= nums.size()) {
            res.emplace_back(nums);
            LOG(INFO) << indention << "save, start:" << start << ", " << nums;
            return;
        }
        for (size_t i = start; i < nums.size(); ++i) {
            // the numbers after start index here are sorted
            // if any same number before i exist, means duplication happend, ignore it.
            int j = i - 1;
            while (j >= start && nums[j] != nums[i]) {
                --j;
            }
            if (j != start - 1) {
                LOG(INFO) << indention << "skip, (" << start << "," << i << "), " << nums;
                continue;
            }
            LOG(INFO) << indention << "togo, (" << start << "," << i << "), " << nums;
            std::swap(nums[i], nums[start]);
            LOG(INFO) << indention << "swap, (" << start << "," << i << "), " << nums;
            swap_func(start + 1, indention + "\t");
            LOG(INFO) << indention << "done, (" << start << "," << i << "), " << nums;
            std::swap(nums[i], nums[start]);
            LOG(INFO) << indention << "rcvr, (" << start << "," << i << "), " << nums;
        }
    };
//    visit_func();
    swap_func(0, "");
    return res;
}

FTEST(test_permuteUnique) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> ns = nums;
        auto n = permuteUnique(ns);
        LOG(INFO) << nums << " premutations: " << n;
        return n;
    };

    t({});
    t({1});
    t({1, 1});
    t({1, 1, 1});
    t({2, 1, 1});
    t({2, 1, 2});
    t({3, 1, 2});
    t({1, 2, 3, 3});
}

/**
 ///////////// 48. Rotate Image
 You are given an n x n 2D matrix representing an image. Rotate the image by 90 degrees (clockwise).

 Note:
 You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
 DO NOT allocate another 2D matrix and do the rotation.

 Example 1:
 Given input matrix =
 [
   [1,2,3],
   [4,5,6],
   [7,8,9]
 ],

 rotate the input matrix in-place such that it becomes:
 [
   [7,4,1],
   [8,5,2],
   [9,6,3]
 ]

 Example 2:
 Given input matrix =
 [
   [ 5, 1, 9,11],
   [ 2, 4, 8,10],
   [13, 3, 6, 7],
   [15,14,12,16]
 ],

 rotate the input matrix in-place such that it becomes:
 [
   [15,13, 2, 5],
   [14, 3, 4, 1],
   [12, 6, 8, 9],
   [16, 7,10,11]
 ]
 */
void rotate(std::vector<std::vector<int>>& matrix) {
    int len = matrix.size();
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - 1; ++j) {
            std::swap(matrix[i][j], matrix[len - j - 1][len - i - 1]);
        }
    }
    int half = len / 2;
    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < len; ++j) {
            std::swap(matrix[i][j], matrix[len - i - 1][j]);
        }
    }
}

/**
 ///////////// 49. Group Anagrams
 Given an array of strings, group anagrams together.

 Example:
 Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 Output:
 [
   ["ate","eat","tea"],
   ["nat","tan"],
   ["bat"]
 ]

 Note:
    - All inputs will be in lowercase.
    - The order of your output does not matter.
 */
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> ss;
    for (auto& str : strs) {
        std::string key = str;
        std::sort(key.begin(), key.end());
        ss[key].emplace_back(std::move(str));
    }
    int idx = 0;
    std::vector<std::vector<std::string>> res(ss.size());
    for (auto& entry : ss) {
        res[idx++] = std::move(entry.second);
    }
    return res;
}

FTEST(test_groupAnagrams) {
    auto t = [](const std::vector<std::string>& strs) {
        std::vector<std::string> ns = strs;
        auto n = groupAnagrams(ns);
        LOG(INFO) << strs << " groupAnagrams: " << n;
        return n;
    };

    t({"eat", "tea", "tan", "ate", "nat", "bat"});
}

/**
 ///////////// 50. Pow(x, n)
 Implement pow(x, n), which calculates x raised to the power n (xn).

 Example 1:
 Input: 2.00000, 10
 Output: 1024.00000

 Example 2:
 Input: 2.10000, 3
 Output: 9.26100

 Example 3:
 Input: 2.00000, -2
 Output: 0.25000
 Explanation: 2-2 = 1/22 = 1/4 = 0.25

 Note:
 -100.0 < x < 100.0
 n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
 */
double myPow(double x, int n) {
    int res = 1.0;
    for (int i = n; i != 0; i /= 2) {
        if (i % 2 != 0) {
            res *= x;
        }
        x *= x;
    }
    return n < 0 ? 1 / res : res;
}