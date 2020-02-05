#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

namespace LCIndex5 {

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

THOUGHTS:
    if two point locate at same diagonal, abs(x-x') = abs(y-y')
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

 THOUGHTS:


 j=x to row:

 i=y to col:

 j=row to x:

 i=col to y:


*/
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        return {};
    }

    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    size_t count = matrix.size() * matrix.front().size();
    size_t xsize = matrix.front().size();
    size_t ysize = matrix.size();
    std::vector<int> res;
    while (res.size() < count) {
        int xend = xsize - x / 2;
        for (; j < xend; ++j) {
            res.emplace_back(matrix[i][j]);
        }
        if (++y >= ysize) { break; }

        int yend = ysize - y / 2;
        for (++i, --j; i < yend; ++i) {
            res.emplace_back(matrix[i][j]);
        }
        if (++x >= xsize) { break; }

        xend = x / 2;
        for (--i, --j; j >= xend; --j) {
            res.emplace_back(matrix[i][j]);
        }
        if (++y >= ysize) { break; }

        yend = y / 2;
        for (--i, ++j; i >= yend; --i) {
            res.emplace_back(matrix[i][j]);
        }
        ++x;
        ++i;
        ++j;
    }
    return res;
}

FTEST(test_spiralOrder) {
    auto t = [](const std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> nns = matrix;
        auto re = spiralOrder(nns);

        LOG(INFO) << matrix << " spiralOrder: " << re;
        return re;
    };

    t({});
    t({{1}});
    t({{1, 2}});
    t({{1}, {2}});
    t({{1, 2}, {3, 4}});
    t({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    t({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
}

/**
 ///////////// 55. Jump Game
 Given an array of non-negative integers,
 you are initially positioned at the first index of the array.
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
    int len = nums.size();
    int cur = 0;
    while (cur < len - 1) {
        int max = cur;
        for (int i = 0; i <= nums[cur]; ++i) {
            int idx = cur + i;
            if (idx >= len - 1) {
                return true;
            }
            if (idx + nums[idx] > max + nums[max]) {
                max = idx;
            }
        }
        if (max == cur) {
            return false;
        }
        cur = max;
    }
    return true;
}

FTEST(test_canJump) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> ns = nums;
        auto n = canJump(ns);
        LOG(INFO) << nums << " can jump: " << n;
        return n;
    };

    t({1});
    t({1, 2});
    t({2, 3, 1, 1, 4});
    t({3, 2, 1, 0, 4});
    t({1, 1, 2, 2, 0, 1, 1});
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

THOUGTHS:
  after sort, a.left <= b.left, right right border has two conditions:
     cond1                cond2
  a: ┌     ┐           ┌            ┐
  b:    ┌        ┐        ┌      ┐
     1  2  3  4  5  6  7  8  9  10 11

  cond1: partial overlap (a.right < b.right)
    left=a.left, right=b.right
  cond2: total overlap ( a.right > b.right)
    left=a.left, right=a.right
  merge two condition:
    left=a.left, right=max(a.right, b.right)

*/
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    std::vector<std::vector<int>> res;
    if (intervals.empty()) {
        return res;
    }
    std::sort(intervals.begin(), intervals.end());
    int l = intervals.front().front();
    int r = intervals.front().back();       // last right border
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].front() > r) {
            res.emplace_back(std::vector<int>{l, r});
            l = intervals[i].front();
            r = intervals[i].back();
        } else {
            r = std::max(r, intervals[i].back());
        }
    }
    res.emplace_back(std::vector<int>{l, r});
    return res;
}

FTEST(test_merge) {
    auto t = [](const std::vector<std::vector<int>>& nums) {
        std::vector<std::vector<int>> ns = nums;
        auto n = merge(ns);
        LOG(INFO) << nums << " merge intervals: " << n;
        return n;
    };

    t({});
    t({{1, 1}});
    t({{1, 3}});
    t({{1, 1}, {1, 1}});
    t({{1, 4}, {2, 3}});
    t({{1, 4}, {4, 5}});
    t({{1, 3}, {2, 6}, {8, 10}, {15, 18}});
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

    std::vector<std::vector<int>> res;
    int l = newInterval.front();
    int r = newInterval.back();
    size_t i = 0;
    for (; i < intervals.size(); ++i) {
        if (intervals[i].back() < newInterval.front()) {
            res.emplace_back(intervals[i]);
            continue;
        }
        l = std::min(intervals[i].front(), newInterval.front());
        break;
    }
    for (; i < intervals.size(); ++i) {
        if (intervals[i].front() > newInterval.back()) {
            break;
        }
        r = std::max(intervals[i].back(), newInterval.back());
    }
    res.emplace_back(std::vector<int>{l, r});
    for (; i < intervals.size(); ++i) {
        res.emplace_back(intervals[i]);
    }
    return res;
}

FTEST(test_insert) {
    auto t = [](const std::vector<std::vector<int>>& nums, const std::vector<int>& newInterval) {
        std::vector<std::vector<int>> ns = nums;
        std::vector<int> ni = newInterval;
        auto n = insert(ns, ni);
        LOG(INFO) << nums << " insert interval " << newInterval << " : " << n;
        return n;
    };

    t({}, {1, 2});
    t({{1, 1}}, {1, 1});
    t({{1, 3}}, {1, 1});
    t({{1, 3}}, {1, 2});
    t({{1, 3}}, {1, 3});
    t({{1, 1}, {1, 1}}, {1, 1});
    t({{1, 1}, {1, 1}}, {1, 2});
    t({{1, 3}, {6, 9}}, {2, 5});
    t({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8});
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
    int count = 0;
    int i = s.size() - 1;
    while (i >= 0 && s[i] == ' ') {
        --i;
    }
    while (i >= 0 && s[i--] != ' ') {
        ++count;
    }
    return count;
}

/**
 ///////////// 59. Spiral Matrix II
Given a positive integer n,
 generate a square matrix filled with elements from 1 to n2 in spiral order.

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
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    size_t count = n * n;
    std::vector<int> res;
    int idx = 1;
    while (res.size() < count) {
        int xend = n - x / 2;
        for (; j < xend; ++j) {
            matrix[i][j] = idx++;
        }
        if (++y >= n) { break; }

        int yend = n - y / 2;
        for (++i, --j; i < yend; ++i) {
            matrix[i][j] = idx++;
        }
        if (++x >= n) { break; }

        xend = x / 2;
        for (--i, --j; j >= xend; --j) {
            matrix[i][j] = idx++;
        }
        if (++y >= n) { break; }

        yend = y / 2;
        for (--i, ++j; i >= yend; --i) {
            matrix[i][j] = idx++;
        }
        ++x;
        ++i;
        ++j;
    }
    return matrix;
}

FTEST(test_generateMatrix) {
    auto t = [](int n) {
        auto re = generateMatrix(n);
        LOG(INFO) << n << " spiral matrix: " << re;
        return re;
    };

    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
    t(5);
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

THOUGHTS:
 n=3, k=4(start from 0)
 Count of permutations is factorial=n!, we could group then by numerical order.
     1 2 3
     1 3 2

     2 1 3
     2 3 1

     3 1 2
     3 2 1

     idx=0, count of each group is factory=factory/n
     res[idx]=nums[k/factory]
     res[0]=nums[4/(6/3)]=nums[2]='3', we picked 3rd group:
     3 1 2
     3 2 1

     idx=1(++idx), k=0(k%=factorial), factorial=1(factorial / (i - 1)?1),
     res[1]=nums[0/1]=nums[0]='1', we picked:
     3 1 2
*/
std::string getPermutation(int n, int k) {
    std::string nums = "123456789";
    int factorial = 1;
    for (int i = 1; i < n; ++i) {
        factorial *= i;
    }
    --k;
    std::string res;
    for (int i = n; i > 0; --i) {
        int idx = k / factorial;
        k %= factorial;
        factorial = i == 1 ? 1 : factorial / (i - 1);
        res.push_back(nums[idx]);
        nums.erase(idx, 1);
    }
    return res;
}

FTEST(test_getPermutation) {
    auto t = [](int n, int k) {
        auto re = getPermutation(n, k);
        LOG(INFO) << k << "th premutation of " << n << " : " << re;
        return re;
    };

    t(0, 0);
    t(1, 1);
    t(2, 1);
    t(2, 2);
    t(3, 1);
    t(3, 2);
    t(3, 3);
    t(3, 4);
    t(3, 5);
    t(3, 6);
    t(4, 1);
    t(4, 2);
    t(4, 9);

}

}