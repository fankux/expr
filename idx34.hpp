#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex34 {

/**
 ///////////// 341.

 */

/**
 ///////////// 342.

 */


/**
 ///////////// 343.

 */


/**
 ///////////// 344. Reverse String
Write a function that reverses a string. The input string is given as an array of characters char[].
Do not allocate extra space for another array,
 you must do this by modifying the input array in-place with O(1) extra memory.

You may assume all the characters consist of printable ascii characters.

Example 1:
Input: ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:
Input: ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
 */
void reverseString(std::vector<char>& s) {
    int l = 0;
    int r = s.size() - 1;
    while (l < r) {
        std::swap(s[l++], s[r--]);
    }
}

/**
 ///////////// 345.

 */


/**
 ///////////// 346.

 */


/**
 ///////////// 347.

 */


/**
 ///////////// 348.

 */


/**
 ///////////// 349.

 */


/**
 ///////////// 350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.

Follow up:
 - What if the given array is already sorted? How would you optimize your algorithm?
 - What if nums1's size is small compared to nums2's size? Which algorithm is better?
 - What if elements of nums2 are stored on disk,
    and the memory is limited such that you cannot load all elements into the memory at once?
 */
std::vector<int> intersectTwoArray(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::unordered_map<int, int> mm;
    for (int num : nums1) {
        ++mm[num];
    }
    std::vector<int> res;
    for (int num : nums2) {
        if (--mm[num] >= 0) {
            res.emplace_back(num);
        }
    }
    return res;
}


}