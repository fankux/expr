#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

namespace LCIndex3 {

typedef LCListNode ListNode;

/**
 ///////////// 31. Next Permutation
 Implement next permutation, which rearranges numbers into the lexicographically
 next greater permutation of numbers.
 If such arrangement is not possible, it must rearrange it as the lowest
 possible order (ie, sorted in ascending order).

 The replacement must be in-place and use only constant extra memory.
 Here are some examples. Inputs are in the left-hand column and its corresponding
 outputs are in the right-hand column.

 1,2,3 → 1,3,2
 3,2,1 → 1,2,3
 1,1,5 → 1,5,1

 THOUGHTS:
 1,2,3 => 1,3,2 => 2,1,3 => 2,3,1 => 3,1,2 => 3,2,1
 AS general:
 1　　2　　7　　4　　3　　1
     |   { desc order } section
    IDX
 RULE 1. Section that DESC order means the last group, next arrangement must be ordered ASC.
 RULE 2. To do so, switch two member between the member just before section(IDX) and
    centain one in sections. But which one? We always switch in ASC order one by one,
    so the centain member in section must be the first one that larger-equal than IDX.
  1　　3　　7　　4　　2　　1
      |   { desc order } section
      |           |
      ---switch----
 Then reverse section to meet rule 1. Result: 1 3 1 2 4 7

 specially, two corner case:
    1  2        3
       |   {desc order}
      IDX       |
       |-swtich-|

           3      2     1
   IDX=-1  { desc order }
*/
void nextPermutation(std::vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        --i;
    }
    if (i >= 0) {
        int j = nums.size() - 1;
        while (nums[j] <= nums[i]) { // there must be a j exist
            --j;
        }
        std::swap(nums[i], nums[j]);
    }
    std::reverse(nums.begin() + i + 1, nums.end());
}

FTEST(test_nextPermutation) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> n = nums;
        nextPermutation(n);
        LOG(INFO) << nums << " next permutation: " << n;
        return n;
    };

    t({1, 2, 7, 4, 3, 1});
}

/**
 ///////////// 32. Longest Valid Parentheses
 Given a string containing just the characters '(' and ')',
 find the length of the longest valid (well-formed) parentheses substring.

 Example 1:
 Input: "(()"
 Output: 2
 Explanation: The longest valid parentheses substring is "()"

 Example 2:
 Input: ")()())"
 Output: 4
 Explanation: The longest valid parentheses substring is "()()"

 THOUGHTS(stack):
 (  (  (  )  )  )  )
 0  1  2  3  4  5  6
 s        |            [2,1,0]
          *            [1,0],  len: 3-1=2, current idx as right border
             |
             *         [0]     len: 4-0=4, current idx as right border
                |
                *      []      len: 5-0+1=6, stack empty,current idx as left border
    s              |   []      stack empty, start idx move right.

    TODO... DP method
*/
int longestValidParentheses(std::string s) {
    size_t max_len = 0;
    size_t start = 0;
    std::stack<int> ss;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '(') {
            ss.push(i);
        } else if (c == ')') {
            if (!ss.empty()) {
                ss.pop();
                max_len = ss.empty() ? std::max(max_len, i - start + 1) :
                        std::max(max_len, i - ss.top());
            } else {
                start = i + 1;
            }
        } else {
            return -1;
        }
    }
    return max_len;
}

FTEST(test_longestValidParentheses) {
    auto t = [](const std::string& str) {
        int n = longestValidParentheses(str);
        LOG(INFO) << str << " max valid parentheses: " << n;
        return n;
    };

    t("");
    t("dafd");
    t("afd()");
    t("()dafd");
    t("(dafd)");
    t("(");
    t(")");
    t("()");
    t("(()");
    t("())");
    t(")()())");
    t(")(((((()())()()))()(()))(");
}

/**
 ///////////// 33. Search in Rotated Sorted Array
 Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

 You are given a target value to search. If found in the array return its index, otherwise return -1.
 You may assume no duplicate exists in the array.
 Your algorithm's runtime complexity must be in the order of O(log n).

 Example 1:
 Input: nums = [4,5,6,7,0,1,2], target = 0
 Output: 4

 Example 2:
 Input: nums = [4,5,6,7,0,1,2], target = 3
 Output: -1

 THOUTGHTS:
    1 2 3 4 5
    5 1 2 3 4
    4 5 1 2 3
    3 4 5 1 2
    2 3 4 5 1
  If we use lower bound of mid (l+h)/2 (while (l+h+1)/2 is higher bound),
  we must use nums[l] <= nums[mid], notice the <=, which make more possible to left half.
*/
int searchRotate(std::vector<int>& nums, int target) {
    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = l + (h - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && target < nums[mid]) { // left half sorted
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[h]) { // right half sorted
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
    }
    return -1;
}

FTEST(test_searchRotate) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nns = nums;
        int n = searchRotate(nns, target);
        LOG(INFO) << nums << " find " << target << ": " << n;
        return n;
    };

    FEXP(t({}, 1), -1);
    FEXP(t({1}, 1), 0);
    FEXP(t({1}, 2), -1);
    FEXP(t({3, 1}, 1), 1);
    FEXP(t({3, 1}, 3), 0);
    FEXP(t({3, 1}, 2), -1);
    FEXP(t({4, 5, 6, 7, 0, 1, 2}, 0), 4);
    FEXP(t({4, 5, 6, 7, 0, 1, 2}, -3), -1);
}

/**
 ///////////// 34. Find First and Last Position of Element in Sorted Array
 Given an array of integers nums sorted in ascending order, find the
 starting and ending position of a given target value.
 Your algorithm's runtime complexity must be in the order of O(log n).
 If the target is not found in the array, return [-1, -1].

 Example 1:
 Input: nums = [5,7,7,8,8,10], target = 8
 Output: [3,4]

 Example 2:
 Input: nums = [5,7,7,8,8,10], target = 6
 Output: [-1,-1]
*/
std::vector<int> searchRange(std::vector<int>& nums, int target) {
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            l = mid;
            while (l >= 0 && nums[l] == nums[mid]) {
                --l;
            }
            h = mid;
            while (h < nums.size() && nums[h] == nums[mid]) {
                ++h;
            }
            return {l + 1, h - 1};
        }
        if (target < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return {-1, -1};
}

FTEST(test_searchRange) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nns = nums;
        auto n = searchRange(nns, target);
        LOG(INFO) << nums << " find " << target << ": " << n;
        return n;
    };

    t({5, 7, 7, 8, 8, 10}, 5);
    t({5, 7, 7, 8, 8, 10}, 7);
    t({5, 7, 7, 8, 8, 10}, 8);
    t({5, 7, 7, 8, 8, 10}, 10);
    t({5, 7, 7, 8, 8, 10}, 6);
}

/**
 ///////////// 35. Search Insert Position
 Given a sorted array and a target value, return the index if the target is found.
 If not, return the index where it would be if it were inserted in order.
 You may assume no duplicates in the array.

 Example 1:
 Input: [1,3,5,6], 5
 Output: 2

 Example 2:
 Input: [1,3,5,6], 2
 Output: 1

 Example 3:
 Input: [1,3,5,6], 7
 Output: 4

 Example 4:
 Input: [1,3,5,6], 0
 Output: 0
*/
int searchInsert(std::vector<int>& nums, int target) {
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (target < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

FTEST(test_searchInsert) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nns = nums;
        auto n = searchInsert(nns, target);
        LOG(INFO) << nums << " find " << target << ": " << n;
        return n;
    };

    t({1, 3, 5, 6}, 5);
    t({1, 3, 5, 6}, 2);
    t({1, 3, 5, 6}, 7);
    t({1, 3, 5, 6}, 0);
}

/**
 ///////////// 36. Valid Sudoku
 Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be
 validated according to the following rules:
 Each row must contain the digits 1-9 without repetition.
 Each column must contain the digits 1-9 without repetition.
 Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

 A partially filled sudoku which is valid.
 The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

 Example 1:
 Input:
 [
   ["5","3",".",".","7",".",".",".","."],
   ["6",".",".","1","9","5",".",".","."],
   [".","9","8",".",".",".",".","6","."],
   ["8",".",".",".","6",".",".",".","3"],
   ["4",".",".","8",".","3",".",".","1"],
   ["7",".",".",".","2",".",".",".","6"],
   [".","6",".",".",".",".","2","8","."],
   [".",".",".","4","1","9",".",".","5"],
   [".",".",".",".","8",".",".","7","9"]
 ]
 Output: true

 Example 2:
 Input:
 [
   ["8","3",".",".","7",".",".",".","."],
   ["6",".",".","1","9","5",".",".","."],
   [".","9","8",".",".",".",".","6","."],
   ["8",".",".",".","6",".",".",".","3"],
   ["4",".",".","8",".","3",".",".","1"],
   ["7",".",".",".","2",".",".",".","6"],
   [".","6",".",".",".",".","2","8","."],
   [".",".",".","4","1","9",".",".","5"],
   [".",".",".",".","8",".",".","7","9"]
 ]
 Output: false
 Explanation: Same as Example 1, except with the 5 in the top left corner being
     modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

 Note:
 A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 Only the filled cells need to be validated according to the mentioned rules.
 The given board contain only digits 1-9 and the character '.'.
 The given board size is always 9x9.
*/
bool isValidSudoku(std::vector<std::vector<char>>& board) {
    uint16_t col_bits[9]{0};
    uint16_t sub_bits[9]{0};
    for (size_t i = 0; i < board.size(); ++i) {
        uint16_t row_bits = 0;
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (!isdigit(board[i][j])) {
                continue;
            }
            int mask = 1 << (board[i][j] - '0');    // row
            if ((row_bits & mask) != 0) {
                return false;
            }
            row_bits |= mask;
            if ((col_bits[j] & mask) != 0) {        // col
                return false;
            }
            col_bits[j] |= mask;
            int sub_idx = (i / 3) * 3 + j / 3;      // sub
            if ((sub_bits[sub_idx] & mask) != 0) {
                return false;
            }
            sub_bits[sub_idx] |= mask;
        }
    }
    return true;
}

FTEST(test_isValidSudoku) {
    auto t = [](const std::vector<std::vector<char>>& board) {
        std::vector<std::vector<char>> nns = board;
        auto n = isValidSudoku(nns);
        LOG(INFO) << board << " valid: " << n;
        return n;
    };

    t({
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    });

    t({
            {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    });
}

/**
 ///////////// 37. Sudoku Solver
 Write a program to solve a Sudoku puzzle by filling the empty cells.
 A sudoku solution must satisfy all of the following rules:

 Each of the digits 1-9 must occur exactly once in each row.
 Each of the digits 1-9 must occur exactly once in each column.
 Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 Empty cells are indicated by the character '.'.

 A sudoku puzzle...
 ...and its solution numbers marked in red.

 Note:
 The given board contain only digits 1-9 and the character '.'.
 You may assume that the given Sudoku puzzle will have a single unique solution.
 The given board size is always 9x9.
*/
void solveSudoku(std::vector<std::vector<char>>& board) {
    auto valid = [&board](int i, int j, char c) {
        for (int x = 0; x < 9; ++x) {
            if (board[x][j] == c) {
                return false;
            }
        }
        for (int y = 0; y < 9; ++y) {
            if (board[i][y] == c) {
                return false;
            }
        }
        int row = i - i % 3, col = j - j % 3;
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                if (board[x + row][y + col] == c) {
                    return false;
                }
            }
        }
        return true;
    };
    std::function<bool(int, int)> r;
    r = [&board, &r, &valid](int i, int j) {
        if (i == 9) {
            return true;
        }
        if (j >= 9) {
            return r(i + 1, 0);
        }
        if (board[i][j] != '.') {
            return r(i, j + 1);
        }
        for (char c = '1'; c <= '9'; ++c) {
            if (!valid(i, j, c)) {
                continue;
            }
            board[i][j] = c;
            if (r(i, j + 1)) {
                return true;
            }
            board[i][j] = '.';
        }
        return false;
    };
    r(0, 0);
}

FTEST(test_solveSudoku) {
    auto t = [](const std::vector<std::vector<char>>& board) {
        std::vector<std::vector<char>> nns = board;
        solveSudoku(nns);
        LOG(INFO) << board << " valid: " << nns;
    };
    t({
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    });
}

/**
 ///////////// 38. Count and Say
 The count-and-say sequence is the sequence of integers with the first five terms as following:
 1.     1
 2.     11
 3.     21
 4.     1211
 5.     111221
 1 is read off as "one 1" or 11.
 11 is read off as "two 1s" or 21.
 21 is read off as "one 2, then one 1" or 1211.

 Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the count-and-say sequence.
 Note: Each term of the sequence of integers will be represented as a string.

 Example 1:
 Input: 1
 Output: "1"

 Example 2:
 Input: 4
 Output: "1211"
*/
std::string countAndSay(int n) {
    if (n == 1) {
        return "1";
    }
    std::string re;
    std::string lre = "1";
    int idx = 2;
    while (idx <= n) {
        int count = 0;
        char last = '\0';
        for (char c : lre) {
            if (last == '\0') {
                ++count;
                last = c;
                continue;
            }
            if (c == last) {
                ++count;
                continue;
            }
            re += std::to_string(count) + last;
            last = c;
            count = 1;
        }
        re += std::to_string(count) + last;
        lre = std::move(re);
        ++idx;
    }
    return lre;
}

FTEST(test_countAndSay) {
    LOG(INFO) << 4 << ":" << countAndSay(4);
    for (int i = 1; i <= 10; ++i) {
        LOG(INFO) << i << ":" << countAndSay(i);
    }
}

/**
 ///////////// 39. Combination Sum
 Given a set of candidate numbers (candidates) (without duplicates) and a target number (target),
 find all unique combinations in candidates where the candidate numbers sums to target.
 The same repeated number may be chosen from candidates unlimited number of times.

 Note:
 All numbers (including target) will be positive integers.
 The solution set must not contain duplicate combinations.
 Example 1:

 Input: candidates = [2,3,6,7], target = 7,
 A solution set is:
 [
   [7],
   [2,2,3]
 ]

 Example 2:
 Input: candidates = [2,3,5], target = 8,
 A solution set is:
 [
   [2,2,2,2],
   [2,3,3],
   [3,5]
 ]
*/
std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<int> re;
    std::vector<std::vector<int>> res;
    std::function<void(int, int)> r;
    r = [&](int start, int t) {
        if (t <= 0) {
            if (t == 0) {
                res.emplace_back(re);
            }
            return;
        }
        for (size_t i = start; i < candidates.size(); ++i) {
            re.emplace_back(candidates[i]);
            r(i, t - candidates[i]);
            re.pop_back();
        }
    };
    r(0, target);
    return res;
}

FTEST(test_combinationSum) {
    auto t = [](const std::vector<int>& candidates, int target) {
        std::vector<int> nns = candidates;
        auto n = combinationSum(nns, target);
        LOG(INFO) << candidates << " find " << target << ": " << n;
        return n;
    };

    t({2, 3, 6, 7}, 7);
    t({2, 3, 5}, 8);
}

/**
 ///////////// 40. Combination Sum II
 Given a collection of candidate numbers (candidates) and a target number (target),
 find all unique combinations in candidates where the candidate numbers sums to target.
 Each number in candidates may only be used once in the combination.

 Note:
 All numbers (including target) will be positive integers.
 The solution set must not contain duplicate combinations.

 Example 1:
 Input: candidates = [10,1,2,7,6,1,5], target = 8,
 A solution set is:
 [
   [1, 7],
   [1, 2, 5],
   [2, 6],
   [1, 1, 6]
 ]

 Example 2:
 Input: candidates = [2,5,2,1,2], target = 5,
 A solution set is:
 [
   [1,2,2],
   [5]
 ]
*/
std::vector<std::vector<int>> combinationSumII(std::vector<int>& candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    std::vector<std::vector<int>> res;
    std::vector<int> re;
    std::function<void(int, int)> r;
    r = [&](int start, int t) {
        if (t <= 0) {
            if (t == 0) {
                res.emplace_back(re);
            }
            return;
        }
        for (size_t i = start; i < candidates.size(); ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            re.emplace_back(candidates[i]);
            r(i + 1, t - candidates[i]);
            re.pop_back();
        }
    };
    r(0, target);
    return res;
}

FTEST(test_combinationSumII) {
    auto t = [](const std::vector<int>& candidates, int target) {
        std::vector<int> nns = candidates;
        auto n = combinationSumII(nns, target);
        LOG(INFO) << candidates << " find " << target << ": " << n;
        return n;
    };

    t({2, 3, 6, 7}, 7);
    t({2, 3, 5}, 8);
    t({10, 1, 2, 7, 6, 1, 5}, 8);
    t({2, 5, 2, 1, 2}, 5);
}

}