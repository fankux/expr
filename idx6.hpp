#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;

/**
 ///////////// 61. Rotate List
 Given a linked list, rotate the list to the right by k places, where k is non-negative.

 Example 1:
 Input: 1->2->3->4->5->NULL, k = 2
 Output: 4->5->1->2->3->NULL
 Explanation:
 rotate 1 steps to the right: 5->1->2->3->4->NULL
 rotate 2 steps to the right: 4->5->1->2->3->NULL

 Example 2:
 Input: 0->1->2->NULL, k = 4
 Output: 2->0->1->NULL
 Explanation:
 rotate 1 steps to the right: 2->0->1->NULL
 rotate 2 steps to the right: 1->2->0->NULL
 rotate 3 steps to the right: 0->1->2->NULL
 rotate 4 steps to the right: 2->0->1->NULL
*/
ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr) {
        return head;
    }
    auto normal_func = [&] {
        std::vector<ListNode*> nodes;
        ListNode* p = head;
        while (p) {
            nodes.emplace_back(p);
            p = p->next;
        }
        int len = nodes.size();
        k %= len;
        // while k=0, len-k is out of range, mod make it head node.
        nodes[len - k - 1]->next = nullptr;
        nodes.back()->next = k == 0 ? nullptr : head;
        return nodes[(len - k) % len];
    };
    auto traverse_func = [&] {
        int len = 1;
        ListNode* p = head;
        while (p->next) {
            ++len;
            p = p->next;
        }
        p->next = head;
        k %= len;
        int idx = 0;
        p = head;
        while (idx < len - k) {
            ++idx;
            head = p;
            p = p->next;
        }
        head->next = nullptr;
        return p;
    };
    return traverse_func();
}

FTEST(test_rotateRight) {
    auto t = [](const std::vector<int>& nums, int k) {
        ListNode* head = list_convert_leetcode(create_list(nums));
        auto re = rotateRight(head, k);
        print_list(re);
    };

    t({}, 0);
    t({1}, 0);
    t({1}, 1);
    t({1}, 8);
    t({1, 2}, 0);
    t({1, 2}, 1);
    t({1, 2}, 2);
    t({0, 1, 2}, 4);
    t({1, 2, 3, 4, 5}, 2);
}

/**
 ///////////// 62. Unique Paths
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 The robot can only move either down or right at any point in time. The robot is trying to
  reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 How many possible unique paths are there?
 ___________________________________________
 |Robot|     |     |     |     |     |     |
 |Start|     |     |     |     |     |     |
 -------------------------------------------
 |     |     |     |     |     |     |     |
 |     |     |     |     |     |     |     |
 -------------------------------------------
 |     |     |     |     |     |     |     |
 |     |     |     |     |     |     | Fin |
 -------------------------------------------
 Above is a 7 x 3 grid. How many possible unique paths are there?
 Note: m and n will be at most 100.

 Example 1:
 Input: m = 3, n = 2
 Output: 3
 Explanation:
 From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
 1. Right -> Right -> Down
 2. Right -> Down -> Right
 3. Down -> Right -> Right

 Example 2:
 Input: m = 7, n = 3
 Output: 28
*/
int uniquePaths(int m, int n) {
    std::vector<int> dp(m, 1);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[j] += dp[j - 1];
        }
    }
    return dp[m - 1];
}

FTEST(test_uniquePaths) {
    auto t = [](int m, int n) {
        auto re = uniquePaths(m, n);
        LOG(INFO) << m << "x" << n << " uniquePath count: " << re;
        return re;
    };

    t(1, 1);
    t(1, 2);
    t(2, 1);
    t(2, 2);
    t(2, 3);
    t(3, 2);
    t(7, 3);
}

/**
 ///////////// 63. Unique Paths II
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 The robot can only move either down or right at any point in time. The robot is trying to
 reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 Now consider if some obstacles are added to the grids. How many unique paths would there be?
 ___________________________________________
 |Robot|     |     |     |     |     |     |
 |Start|     |     |     |     |     |     |
 -------------------------------------------
 |     |     |     |     |     |     |     |
 |     |     |     |     |     |     |     |
 -------------------------------------------
 |     |     |     |     |     |     |     |
 |     |     |     |     |     |     | Fin |
 -------------------------------------------
 An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 Note: m and n will be at most 100.

 Example 1:
 Input:
 [
   [0,0,0],
   [0,1,0],
   [0,0,0]
 ]
 Output: 2
 Explanation:
 There is one obstacle in the middle of the 3x3 grid above.
 There are two ways to reach the bottom-right corner:
 1. Right -> Right -> Down -> Down
 2. Down -> Down -> Right -> Right
*/
int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid.front().empty() || obstacleGrid[0][0] == 1) {
        return 0;
    }
    int m = obstacleGrid.front().size();
    int n = obstacleGrid.size();
    std::vector<int64_t> dp(m, 0);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (obstacleGrid[i][j] == 1) {
                dp[j] = 0;
            } else if (j > 0) {
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp[m - 1];
}

FTEST(test_uniquePathsWithObstacles) {
    auto t = [](const std::vector<std::vector<int>>& obstacleGrid) {
        std::vector<std::vector<int>> nns = obstacleGrid;
        auto re = uniquePathsWithObstacles(nns);
        LOG(INFO) << nns << " uniquePath count: " << re;
        return re;
    };

    t({});
    t({{}});
    t({{1}});
    t({{0}});
    t({{0, 1}});
    t({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}});
}

/**
 ///////////// 64. Minimum Path Sum
 Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right
 which minimizes the sum of all numbers along its path.
 Note: You can only move either down or right at any point in time.

 Example:
 Input:
 [
   [1,3,1],
   [1,5,1],
   [4,2,1]
 ]
 Output: 7
 Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/
int minPathSum(std::vector<std::vector<int>>& grid
#ifdef VERBOSE
        , std::vector<int>& path
#endif
) {
    if (grid.empty() || grid.front().empty()) {
        return 0;
    }
    int m = grid.front().size();
    int n = grid.size();
    auto single_func = [&] {
        std::vector<int> dp(m, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j > 0) {
                    dp[j] = std::min(dp[j - 1], dp[j]);
                }
                dp[j] += grid[i][j];
            }
        }
        return dp[m - 1];
    };
#ifdef VERBOSE
    auto with_path_func = [&] {
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MAX));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int j = 1; j < m; ++j) {
            dp[0][j] = grid[0][j] + dp[0][j - 1];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                dp[i][j] = std::min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
            }
        }

        int i = n - 1;
        int j = m - 1;
        path.emplace_back(grid[n - 1][m - 1]);
        while (i > 0 && j > 0) {
            if (dp[i - 1][j] < dp[i][j - 1]) {
                path.emplace_back(grid[i - 1][j]);
                --i;
            } else {
                path.emplace_back(grid[i][j - 1]);
                --j;
            }
        }
        while (j-- > 0) {
            path.emplace_back(grid[0][j]);
        }
        while (i-- > 0) {
            path.emplace_back(grid[i][0]);
        }
        std::reverse(path.begin(), path.end());
        return dp[n - 1][m - 1];
    };
    return with_path_func();
#else
    return single_func();
#endif
}

FTEST(test_minPathSum) {
    auto t = [](const std::vector<std::vector<int>>& grid) {
        std::vector<std::vector<int>> nns = grid;
        std::vector<int> path;
        auto re = minPathSum(nns, path);
        LOG(INFO) << nns << " min path count: " << re << ", path:" << path;
        return re;
    };

    t({});
    t({{}});
    t({{1}});
    t({{0}});
    t({{0, 1}});
    t({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}});
    t({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}});
}

/**
 ///////////// 65. Valid Number
 Validate if a given string can be interpreted as a decimal number.

 Some examples:
 "0" => true
 " 0.1 " => true
 "abc" => false
 "1 a" => false
 "2e10" => true
 " -90e3   " => true
 " 1e" => false
 "e3" => false
 " 6e-1" => true
 " 99e2.5 " => false
 "53.5e93" => true
 " --6 " => false
 "-+3" => false
 "95a54e53" => false

 Note: It is intended for the problem statement to be ambiguous.
 You should gather all requirements up front before implementing one. However,
 here is a list of characters that can be in a valid decimal number:

 Numbers 0-9
 Exponent - "e"
 Positive/negative sign - "+"/"-"
 Decimal point - "."
 Of course, the context of these characters also matters in the input.

 Update (2015-02-10):
 The signature of the C++ function had been updated. If you still see your function signature
 accepts a const char * argument, please click the reload button to reset your code definition.
*/
bool isNumber(std::string s) {
    typedef enum {
        BEGIN = 0,
        SIGNATURE_1,
        NUMBER_1,
        BEGIN_POINTER,
        POINTER,
        NUMBER_1_AFTER,
        EXPONENT,
        SIGNATURE_2,
        NUMBER_2,
        END
    } STATE;

    int state = BEGIN;
    for (char c : s) {
        switch (state) {
            case BEGIN: {
                if (c == ' ') {
                    continue;
                }
                if (c == '-' || c == '+') {
                    state = SIGNATURE_1;
                    continue;
                }
                if (c >= '0' && c <= '9') {
                    state = NUMBER_1;
                    continue;
                }
                if (c == '.') {
                    state = BEGIN_POINTER;
                    continue;
                }
                return false;
            }
            case SIGNATURE_1: {
                if (c >= '0' && c <= '9') {
                    state = NUMBER_1;
                    continue;
                }
                if (c == '.') {
                    state = BEGIN_POINTER;
                    continue;
                }
                return false;
            }
            case NUMBER_1: {
                if (c >= '0' && c <= '9') {
                    continue;
                }
                if (c == '.') {
                    state = POINTER;
                    continue;
                }
                if (c == 'e') {
                    state = EXPONENT;
                    continue;
                }
                if (c == ' ') {
                    state = END;
                    continue;
                }
                return false;
            }
            case BEGIN_POINTER: {
                if (c >= '0' && c <= '9') {
                    state = NUMBER_1_AFTER;
                    continue;
                }
                return false;
            }
            case POINTER: {
                if (c >= '0' && c <= '9') {
                    state = NUMBER_1_AFTER;
                    continue;
                }
                if (c == 'e') {
                    state = EXPONENT;
                    continue;
                }
                if (c == ' ') {
                    state = END;
                    continue;
                }
                return false;
            }
            case NUMBER_1_AFTER: {
                if (c >= '0' && c <= '9') {
                    continue;
                }
                if (c == 'e') {
                    state = EXPONENT;
                    continue;
                }
                if (c == ' ') {
                    state = END;
                    continue;
                }
                return false;
            }
            case EXPONENT: {
                if (c >= '0' && c <= '9') {
                    state = NUMBER_2;
                    continue;
                }
                if (c == '-' || c == '+') {
                    state = SIGNATURE_2;
                    continue;
                }
                return false;
            }
            case SIGNATURE_2: {
                if (c >= '0' && c <= '9') {
                    state = NUMBER_2;
                    continue;
                }
                return false;
            }
            case NUMBER_2: {
                if (c >= '0' && c <= '9') {
                    continue;
                }
                if (c == ' ') {
                    state = END;
                    continue;
                }
                return false;
            }
            case END: {
                if (c == ' ') {
                    continue;
                }
                return false;
            }
            default:
                return false;
        }
    }
    return state == NUMBER_1 || state == NUMBER_1_AFTER || state == NUMBER_2 ||
            state == POINTER || state == END;
}

FTEST(test_isNumber) {
    auto t = [](const std::string& s) {
        auto re = isNumber(s);
        LOG(INFO) << s << " is number: " << re;
        return re;
    };

    FEXP(t(""), false);
    FEXP(t(" "), false);
    FEXP(t(" "), false);
    FEXP(t("0"), true);
    FEXP(t(".0"), true);
    FEXP(t(" .0"), true);
    FEXP(t(".1"), true);
    FEXP(t(" .1"), true);
    FEXP(t(" 0.1 "), true);
    FEXP(t("3."), true);
    FEXP(t("+.8"), true);
    FEXP(t(" +.8"), true);
    FEXP(t("3. "), true);
    FEXP(t("abc"), false);
    FEXP(t("1 a"), false);
    FEXP(t("2e10"), true);
    FEXP(t(" -90e3   "), true);
    FEXP(t(" 1e"), false);
    FEXP(t("e3"), false);
    FEXP(t(" 6e-1"), true);
    FEXP(t(" 99e2.5 "), false);
    FEXP(t("53.5e93"), true);
    FEXP(t("46.e3"), true);
    FEXP(t(" --6 "), false);
    FEXP(t("-+3"), false);
    FEXP(t("95a54e53"), false);
}

/**
 ///////////// 66. Plus One
 Given a non-empty array of digits representing a non-negative integer, plus one to the integer.
 The digits are stored such that the most significant digit is at the head of the list,
 and each element in the array contain a single digit.
 You may assume the integer does not contain any leading zero, except the number 0 itself.

 Example 1:
 Input: [1,2,3]
 Output: [1,2,4]
 Explanation: The array represents the integer 123.

 Example 2:
 Input: [4,3,2,1]
 Output: [4,3,2,2]
 Explanation: The array represents the integer 4321.
*/
std::vector<int> plusOne(std::vector<int>& digits) {
    int carry = 1;
    for (int i = digits.size() - 1; i >= 0; --i) {
        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        digits.insert(digits.begin(), carry);
    }
    return digits;
}

FTEST(test_plusOne) {
    auto t = [](const std::vector<int>& digits) {
        std::vector<int> nns = digits;
        auto re = plusOne(nns);
        LOG(INFO) << digits << " plue one: " << re;
        return re;
    };

    t({});
    t({0});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({9});
    t({9, 9});
    t({9, 9, 9});
    t({1, 0, 2, 3});
    t({4, 3, 2, 1});
}

/**
 ///////////// 67. Add Binary
 Given two binary strings, return their sum (also a binary string).
 The input strings are both non-empty and contains only characters 1 or 0.

 Example 1:
 Input: a = "11", b = "1"
 Output: "100"

 Example 2:
 Input: a = "1010", b = "1011"
 Output: "10101"
*/
std::string addBinary(std::string a, std::string b) {
    return "";
}

/**
 ///////////// 68. Text Justification
 Given an array of words and a width maxWidth, format the text such that each line has exactly
 maxWidth characters and is fully (left and right) justified.
 You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
 Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 Extra spaces between words should be distributed as evenly as possible.
 If the number of spaces on a line do not divide evenly between words,
 the empty slots on the left will be assigned more spaces than the slots on the right.

 For the last line of text, it should be left justified and no extra space is inserted between words.
 Note:
 A word is defined as a character sequence consisting of non-space characters only.
 Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
 The input array words contains at least one word.

 Example 1:
 Input:
 words = ["This", "is", "an", "example", "of", "text", "justification."]
 maxWidth = 16
 Output:
 [
    "This    is    an",
    "example  of text",
    "justification.  "
 ]

 Example 2:
 Input:
 words = ["What","must","be","acknowledgment","shall","be"]
 maxWidth = 16
 Output:
 [
   "What   must   be",
   "acknowledgment  ",
   "shall be        "
 ]
 Explanation: Note that the last line is "shall be    " instead of "shall     be",
              because the last line must be left-justified instead of fully-justified.
              Note that the second line is also left-justified becase it contains only one word.

 Example 3:
 Input:
 words = ["Science","is","what","we","understand","well","enough","to","explain",
          "to","a","computer.","Art","is","everything","else","we","do"]
 maxWidth = 20
 Output:
 [
   "Science  is  what we",
   "understand      well",
   "enough to explain to",
   "a  computer.  Art is",
   "everything  else  we",
   "do                  "
 ]
*/
std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth) {
    return {};
}

/**
 ///////////// 69. Sqrt(x)
 Implement int sqrt(int x).
 Compute and return the square root of x, where x is guaranteed to be a non-negative integer.
 Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

 Example 1:
 Input: 4
 Output: 2

 Example 2:
 Input: 8
 Output: 2
 Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.
*/
int mySqrt(int x) {
    return 0;
}

/**
 ///////////// 70. Climbing Stairs
 You are climbing a stair case. It takes n steps to reach to the top.
 Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 Note: Given n will be a positive integer.

 Example 1:
 Input: 2
 Output: 2
 Explanation: There are two ways to climb to the top.
 1. 1 step + 1 step
 2. 2 steps

 Example 2:
 Input: 3
 Output: 3
 Explanation: There are three ways to climb to the top.
 1. 1 step + 1 step + 1 step
 2. 1 step + 2 steps
 3. 2 steps + 1 step
*/
int climbStairs(int n) {
    return 0;
}
