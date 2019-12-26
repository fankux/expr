#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex18 {

/**
 ///////////// 181. IGNORE SQL
 ///////////// 182. IGNORE SQL
 ///////////// 183. IGNORE SQL
 ///////////// 184. IGNORE SQL
 ///////////// 185. IGNORE SQL
 */

/**
 ///////////// 186. Reverse Words in a String II
Given an input string , reverse the string word by word.
Example:
Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]

Note:
A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces.
The words are always separated by a single space.
Follow up: Could you do it in-place without allocating extra space?
 */
void reverseWords(std::vector<char>& str) {
}

/**
 ///////////// 187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G,
 and T, for example: "ACGAATTCCG". When studying DNA,
 it is sometimes useful to identify repeated sequences within the DNA.
Write a function to find all the 10-letter-long sequences (substrings)
 that occur more than once in a DNA molecule.

Example:
Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 */
std::vector<std::string> findRepeatedDnaSequences(std::string s) {
    return {};
}

/**
 ///////////// 188. Best Time to Buy and Sell Stock IV
Say you have an array for which the i-th element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time
 (ie, you must sell the stock before you buy again).

Example 1:
Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:
Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
             Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 */
int maxProfit(int k, std::vector<int>& prices) {
    return 0;
}

/**
 ///////////// 189. Rotate Array
Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:
Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to
 solve this problem.
Could you do it in-place with O(1) extra space?
 */
void rotate(std::vector<int>& nums, int k) {

}

/**
 ///////////// 190. Reverse Bits
Reverse bits of a given 32 bits unsigned integer.

Example 1:
Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100
 represents the unsigned integer 43261596,
 so return 964176192 which its binary representation is 00111001011110000010100101000000.

Example 2:
Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101
 represents the unsigned integer 4294967293,
 so return 3221225471 which its binary representation is 10111111111111111111111111111111.

Note:
Note that in some languages such as Java, there is no unsigned integer type.
 In this case, both input and output will be given as signed integer type
 and should not affect your implementation,
 as the internal binary representation of the integer is the same whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation.
 Therefore, in Example 2 above the input represents the signed integer -3
 and the output represents the signed integer -1073741825.

Follow up:
If this function is called many times, how would you optimize it?
 */
uint32_t reverseBits(uint32_t n) {
    return 0;
}

}