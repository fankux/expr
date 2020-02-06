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

THOUGHTS(swap index):
 k=2, start=0
 ┌───┐
 1 2 1 4 5    t=3
     ┌───┐
 1 2 1 4 3    t=5
 ──┐     ┌─
 1 5 1 4 3    t=2
   ┌───┐
 1 5 1 2 3    t=4
 ┐     ┌───
 4 5 1 2 3    pos=start, ++pos

 */
void rotateArray(std::vector<int>& nums, int k) {
    size_t len = nums.size();
    if (len == 0) {
        return;
    }
    auto swap_two_end = [&] {
        k %= len;
        for (int l = 0, r = len - k - 1; l < r; l++, r--) {
            std::swap(nums[l], nums[r]);
        }
        for (int l = len - k, r = len - 1; l < r; l++, r--) {
            std::swap(nums[l], nums[r]);
        }
        for (int l = 0, r = len - 1; l < r; l++, r--) {
            std::swap(nums[l], nums[r]);
        }
    };
    auto swap_index = [&] {
        int start = 0;
        int pos = 0;
        int t = nums[pos];
        for (size_t i = 0; i < len; ++i) {
            pos = (pos + k) % len;
            std::swap(nums[pos], t);
            if (pos == start) {
                pos = ++start;
                t = nums[pos % len];
            }
        }
    };
    swap_index();
}

FTEST(test_rotateArray) {
    auto t = [](const std::vector<int>& nums, int k) {
        std::vector<int> nns = nums;
        rotateArray(nns, k);
        LOG(INFO) << nums << " rotate " << k << ": " << nns;
    };

    t({}, 0);
    t({1}, 0);
    t({1}, 1);
    t({1}, 2);
    t({1}, 3);
    t({1, 2}, 1);
    t({1, 2}, 2);
    t({1, 2}, 3);
    t({1, 2, 3}, 1);
    t({1, 2, 3}, 2);
    t({1, 2, 3}, 3);
    t({1, 2, 3, 4, 5, 6}, 2);
    t({1, 2, 3, 4, 5, 6, 7}, 3);
    t({-1, -100, 3, 99}, 3);
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

 THOUGHTS:

 bit patter method:
Step 0.
abcd efgh ijkl mnop qrst uvwx yzAB CDEF <-- n

Step 1.
                    abcd efgh ijkl mnop <-- n >> 16, same as (n & 0xffff0000) >> 16
qrst uvwx yzAB CDEF                     <-- n << 16, same as (n & 0x0000ffff) << 16
qrst uvwx yzAB CDEF abcd efgh ijkl mnop <-- after OR

Step 2.
          qrst uvwx           abcd efgh <-- (n & 0xff00ff00) >> 8
yzAB CDEF           ijkl mnop           <-- (n & 0x00ff00ff) << 8
yzAB CDEF qrst uvwx ijkl mnop abcd efgh <-- after OR

Step 3.
     yzAB      qrst      ijkl      abcd <-- (n & 0xf0f0f0f0) >> 4
CDEF      uvwx      mnop      efgh      <-- (n & 0x0f0f0f0f) << 4
CDEF yzAB uvwx qrst mnop ijkl efgh abcd <-- after OR

Step 4.
  CD   yz   uv   qr   mn   ij   ef   ab <-- (n & 0xcccccccc) >> 2
EF   AB   wx   st   op   kl   gh   cd   <-- (n & 0x33333333) << 2
EFCD AByz wxuv stqr opmn klij ghef cdab <-- after OR

Step 5.
 E C  A y  w u  s q  o m  k i  g e  c a <-- (n & 0xaaaaaaaa) >> 1
F D  B z  x v  t r  p n  l j  h f  d b  <-- (n & 0x55555555) << 1
FEDC BAzy xwvu tsrq ponm lkji hgfe dcba <-- after OR

 */
uint32_t reverseBits(uint32_t n) {
    auto common_func = [&] {
        uint32_t res = 0;
        for (int i = 0; i < 32; ++i) {
            res = (res << 1) + ((n >> i) & 1);
        }
        return res;
    };
    auto bit_pattern = [&] {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    };
    return common_func();
}

FTEST(bit_pattern) {
    auto t = [](uint32_t n) {
        uint32_t re = reverseBits(n);
        LOG(INFO) << n << " reverse " << re;
        return re;
    };

    FEXP(t(UINT32_MAX), UINT32_MAX);
    FEXP(t(43261596), 964176192);
    FEXP(t(4294967293), 3221225471);
}

}