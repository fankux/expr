#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex26 {

/**
 ///////////// 261.

 */

/**
 ///////////// 262.

 */


/**
 ///////////// 263.

 */


/**
 ///////////// 264.

 */


/**
 ///////////// 265.

 */


/**
 ///////////// 266.

 */


/**
 ///////////// 267.

 */


/**
 ///////////// 268. Missing Number
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
 find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity.
 Could you implement it using only constant extra space complexity?
 */
int missingNumber(std::vector<int>& nums) {
    int res = 0;
    size_t len = nums.size();
    auto bit_manipulation = [&] {
        for (size_t i = 0; i < len; ++i) {
            res ^= (i + 1) ^ nums[i];
        }
        return res;
    };
    auto formula_method = [&] {
        for (auto num : nums) {
            res += num;
        }
        return (1 + len) * len / 2 - res;
    };
    return formula_method();
}

FTEST(test_missingNumber) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = missingNumber(nns);
        LOG(INFO) << nums << " missing: " << re;
        return re;
    };

    FEXP(t({0, 2}), 1);
    FEXP(t({0, 1, 3}), 2);
    FEXP(t({3, 0, 1}), 2);
    FEXP(t({2, 0, 1}), 3);
    FEXP(t({9, 6, 4, 2, 3, 5, 7, 0, 1}), 8);
    FEXP(t({9, 6, 4, 2, 3, 5, 7, 8, 1}), 0);
    FEXP(t({9, 6, 4, 2, 3, 5, 7, 8, 0}), 1);

}

/**
 ///////////// 269.

 */


/**
 ///////////// 270.

 */



}