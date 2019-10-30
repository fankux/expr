#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

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
 RULE 1. section that DESC order means the last group, next arrangement must be ordered ASC.
 RULE 2. to do so, switch two member between the memeber just before section(IDX) and
    centain one in sections. but which one? we always switch in ASC order one by one,
    so the centain member in section must be the first one that larger-equal than IDX.
  1　　3　　7　　4　　2　　1
      |   { desc order } section
      |           |
      ---switch----
 then reverse section to meet rule 1.
 specially, two corner case:
    1  2        3
       |   {desc order}
      IDX       |
       |-swtich-|

           3      2     1
   NO-IDX  { desc order }
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
*/
int longestValidParentheses(std::string s) {

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
*/
int search(std::vector<int>& nums, int target) {

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
std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {

}
