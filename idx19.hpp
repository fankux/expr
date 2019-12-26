#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex19 {

/**
 ///////////// 191. Number of 1 Bits
Write a function that takes an unsigned integer and return the number of '1' bits it has
 (also known as the Hamming weight).

Example 1:
Input: 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

Example 2:
Input: 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

Example 3:
Input: 11111111111111111111111111111101
Output: 31
Explanation:
 The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.

Note:
Note that in some languages such as Java, there is no unsigned integer type.
 In this case, the input will be given as signed integer type and should not affect
 your implementation, as the internal binary representation of the integer is the
 same whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation.
 Therefore, in Example 3 above the input represents the signed integer -3.

Follow up:
If this function is called many times, how would you optimize it?
 */
int hammingWeight(uint32_t n) {
    return 0;
}

/**
 ///////////// 192. IGNORE SHELL
 ///////////// 193. IGNORE SHELL
 ///////////// 194. IGNORE SHELL
 ///////////// 195. IGNORE SHELL
 ///////////// 196. IGNORE SQL
 ///////////// 197. IGNORE SQL
 */

/**
 ///////////// 198. House Robber
You are a professional robber planning to rob houses along a street.
 Each house has a certain amount of money stashed,
 the only constraint stopping you from robbing each of them is
 that adjacent houses have security system connected and it will automatically
 contact the police if two adjacent houses were broken into  on the same night.

Given a list of non-negative integers representing the amount of money of each house,
 determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
 */
int rob(std::vector<int>& nums) {
    return 0;
}

/**
 ///////////// 199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it,
 return the values of the nodes you can see ordered from top to bottom.

Example:
Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

 */
std::vector<int> rightSideView(TreeNode* root) {
    return {};
}

/**
 ///////////// 200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water),
 count the number of islands. An island is surrounded by water
 and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input:
11110
11010
11000
00000

Output: 1

Example 2:
Input:
11000
11000
00100
00011

Output: 3
 */
int numIslands(std::vector<std::vector<char>>& grid) {
    return 0;
}

}