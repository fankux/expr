#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex28 {

/**
 ///////////// 281.

 */

/**
 ///////////// 282.

 */


/**
 ///////////// 283. Move Zeroes
Given an array nums, write a function to move all 0's to the end of it
 while maintaining the relative order of the non-zero elements.

Example:
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Note:
 - You must do this in-place without making a copy of the array.
 - Minimize the total number of operations.

THOUGHTS:
    i is the index of last found 0
    j is the index of last found not 0

    condition 1: if i, j adjucent, after swap, i++ still at the index of 0
    0 1 2   =>    0 1 2
    i j           i j

    condition 2: if i, j not adjucent, the gap between must be all 0 or i, j must be adjucent.
        so i++ still at the index of 0 too.
    0 0 2 4   =>   0 0 2 4
    i   j            i   j

    condition 3: if i==j≠0, next number is not 0, there still at condition 3 after swap(do nothing)
    1 1 2 4   =>   1 1 2 4
   i,j              i,j

    condition 4: if i==j≠0, next number is 0, after swap(do nothing),
        things change to condition 1 or condition 2
    1 0 2 4   =>   1 0 2 4   =>   1 0 2 4
   i,j              i,j             i j

 */
void moveZeroes(std::vector<int>& nums) {
    for (size_t i = 0, j = 0; j < nums.size(); ++j) {
        if (nums[j] != 0) {
            std::swap(nums[i++], nums[j]);
        }
    }
}

FTEST(test_moveZeroes) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        moveZeroes(nns);
        LOG(INFO) << nums << " move zeros: " << nns;
    };

    t({});
    t({0});
    t({1});
    t({0, 0});
    t({0, 1});
    t({1, 0});
    t({1, 1});
    t({0, 0, 0});
    t({1, 0, 0});
    t({0, 1, 0});
    t({0, 0, 1});
    t({0, 1, 1});
    t({1, 0, 1});
    t({1, 1, 0});
    t({1, 1, 1});
    t({0, 1, 0, 3, 12});
}

/**
 ///////////// 284.

 */


/**
 ///////////// 285.

 */


/**
 ///////////// 286.

 */


/**
 ///////////// 287.

 */


/**
 ///////////// 288.

 */


/**
 ///////////// 289.

 */


/**
 ///////////// 290.

 */



}