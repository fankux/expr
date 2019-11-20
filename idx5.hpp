#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 51. N-Queens
 The n-queens puzzle is the problem of placing n queens on an n×n chessboard such
 that no two queens attack each other.

 Given an integer n, return all distinct solutions to the n-queens puzzle.

 Each solution contains a distinct board configuration of the n-queens' placement, where 'Q'
 and '.' both indicate a queen and an empty space respectively.

 Example:
 Input: 4
 Output: [
  [".Q..",  // Solution 1
   "...Q",
   "Q...",
   "..Q."],

  ["..Q.",  // Solution 2
   "Q...",
   "...Q",
   ".Q.."]
 ]

 [
 "Q..",
 "..Q",
 ".Q."
 ]
 Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.

 THOUGHTS:
    if two point locate at same diagonal, abs(x-x') = abs(y-y')
*/
std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<size_t> pos(n);
    std::vector<std::vector<std::string>> res;
    auto valid = [&](size_t row, size_t col) {
        for (size_t i = 0; i < row; ++i) {
            if (pos[i] == col || llabs(row - i) == llabs(col - pos[i])) {
                return false;
            }
        }
        return true;
    };
    std::function<void(int)> r;
    r = [&](size_t cur_row) {
        if (cur_row >= n) {
            std::vector<std::string> re(n, std::string(n, '.'));
            for (size_t i = 0; i < n; ++i) {
                re[i][pos[i]] = 'Q';
            }
            res.emplace_back(re);
            return;
        }
        for (size_t i = 0; i < n; ++i) {
            if (valid(cur_row, i)) {
                pos[cur_row] = i;
                r(cur_row + 1);
                pos[cur_row] = SIZE_MAX;
            }
        }
    };
    r(0);
    return res;
}

FTEST(test_solveNQueens) {
    auto t = [](int n) {
        auto re = solveNQueens(n);
        LOG(INFO) << n << " Queen: " << re;
        return re;
    };
    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
}

/**
 ///////////// 52. N-Queens II
 The n-queens puzzle is the problem of placing n queens on an n×n chessboard such
 that no two queens attack each other.

 Given an integer n, return the number of distinct solutions to the n-queens puzzle.

 Example:
 Input: 4
 Output: 2
 Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
 [
  [".Q..",  // Solution 1
   "...Q",
   "Q...",
   "..Q."],

  ["..Q.",  // Solution 2
   "Q...",
   "...Q",
   ".Q.."]
 ]
*/
int totalNQueens(int n) {
    int res = 0;
    std::vector<size_t> pos(n);
    auto valid = [&](size_t row, size_t col) {
        for (size_t i = 0; i < row; ++i) {
            if (pos[i] == col || llabs(row - i) == llabs(col - pos[i])) {
                return false;
            }
        }
        return true;
    };
    std::function<void(int)> r;
    r = [&](size_t cur_row) {
        if (cur_row >= n && n != 0) {
            ++res;
            return;
        }
        for (size_t i = 0; i < n; ++i) {
            if (valid(cur_row, i)) {
                pos[cur_row] = i;
                r(cur_row + 1);
                pos[cur_row] = SIZE_MAX;
            }
        }
    };
    r(0);
    return res;
}

FTEST(test_totalNQueens) {
    auto t = [](int n) {
        auto re = totalNQueens(n);
        LOG(INFO) << n << " Queen count: " << re;
        return re;
    };
    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
}

/**
 ///////////// 53. Maximum Subarray
 Given an integer array nums, find the contiguous subarray (containing at least one number)
 which has the largest sum and return its sum.

 Example:
 Input: [-2,1,-3,4,-1,2,1,-5,4],
 Output: 6
 Explanation: [4,-1,2,1] has the largest sum = 6.

 Follow up:
 If you have figured out the O(n) solution, try coding another solution using the divide
 and conquer approach, which is more subtle.

 THOUGHTS:
 if maxsum + num < num, means the max subarray restart,
 however, this still got an regional max value.

*/
#define VERBOSE
int maxSubArray(std::vector<int>& nums
#ifdef VERBOSE
        , std::vector<int>& range
#endif
) {
    size_t len = nums.size();
    int max = INT_MIN;
    int regional_max = 0;
#ifdef VERBOSE
    size_t l = 0;
    size_t r = 0;
#endif
    for (size_t i = 0; i < len; ++i) {
        if (regional_max + nums[i] > nums[i]) {
            regional_max += nums[i];
        } else {
            regional_max = nums[i];
#ifdef VERBOSE
            if (regional_max > max) {
                l = i;
            }
        }
        if (regional_max > max) {
            max = regional_max;
            r = i;
        }
    }
    while (l <= r) {
        range.emplace_back(nums[l++]);
    }
#else
        }
        max = std::max(max, regional_max);
    }
#endif
    return max;
}

FTEST(test_maxSubArray) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        std::vector<int> range;
#ifdef VERBOSE
        auto re = maxSubArray(nns, range);
#else
        auto re = maxSubArray(nns);
#endif
        LOG(INFO) << nums << " max subarray: " << range << ", sum: " << re;
        return re;
    };

    t({-2, 1, -3, 4, -1, 2, 1, -5, 4});
}

/**
 ///////////// 54. Spiral Matrix
 Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

 Example 1:
 Input:
 [
  [ 1, 2, 3 ],
  [ 4, 5, 6 ],
  [ 7, 8, 9 ]
 ]
 Output: [1,2,3,6,9,8,7,4,5]

 Example 2:
 Input:
 [
   [1, 2, 3, 4],
   [5, 6, 7, 8],
   [9,10,11,12]
 ]
 Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    return {};
}

/**
 ///////////// 55. Jump Game
 Given an array of non-negative integers, you are initially positioned at the first index of the array.
 Each element in the array represents your maximum jump length at that position.
 Determine if you are able to reach the last index.

 Example 1:
 Input: [2,3,1,1,4]
 Output: true
 Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

 Example 2:
 Input: [3,2,1,0,4]
 Output: false
 Explanation: You will always arrive at index 3 no matter what. Its maximum
              jump length is 0, which makes it impossible to reach the last index.
*/
bool canJump(std::vector<int>& nums) {
    return false;
}

/**
 ///////////// 56. Merge Intervals
 Given a collection of intervals, merge all overlapping intervals.

 Example 1:
 Input: [[1,3],[2,6],[8,10],[15,18]]
 Output: [[1,6],[8,10],[15,18]]
 Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

 Example 2:
 Input: [[1,4],[4,5]]
 Output: [[1,5]]
 Explanation: Intervals [1,4] and [4,5] are considered overlapping.

 NOTE: input types have been changed on April 15, 2019. Please reset to default code definition
 to get new method signature.
*/
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    return {};
}

/**
 ///////////// 57. Insert Interval
 Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 You may assume that the intervals were initially sorted according to their start times.

 Example 1:
 Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 Output: [[1,5],[6,9]]

 Example 2:
 Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 Output: [[1,2],[3,10],[12,16]]
 Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

 NOTE: input types have been changed on April 15, 2019. Please reset to default code definition
 to get new method signature.
*/
std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals,
        std::vector<int>& newInterval) {
    return {};
}


/**
 ///////////// 58. Length of Last Word
 Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
 return the length of last word in the string.
 If the last word does not exist, return 0.

 Note: A word is defined as a character sequence consists of non-space characters only.

 Example:
 Input: "Hello World"
 Output: 5
*/
int lengthOfLastWord(std::string s) {
    return 0;
}

/**
 ///////////// 59. Spiral Matrix II
 Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

 Example:
 Input: 3
 Output:
 [
  [ 1, 2, 3 ],
  [ 8, 9, 4 ],
  [ 7, 6, 5 ]
 ]
*/
std::vector<std::vector<int>> generateMatrix(int n) {
    return {};
}

/**
 ///////////// 60. Permutation Sequence
 The set [1,2,3,...,n] contains a total of n! unique permutations.
 By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

 "123"
 "132"
 "213"
 "231"
 "312"
 "321"
 Given n and k, return the kth permutation sequence.

 Note:
 Given n will be between 1 and 9 inclusive.
 Given k will be between 1 and n! inclusive.

 Example 1:
 Input: n = 3, k = 3
 Output: "213"

 Example 2:
 Input: n = 4, k = 9
 Output: "2314"
*/
std::string getPermutation(int n, int k) {
    return "";
}