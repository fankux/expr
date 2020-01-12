#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex58 {

/**
 ///////////// 581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray
 that if you only sort this subarray in ascending order,
 then the whole array will be sorted in ascending order, too.
You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the
 whole array sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

 THOUGHTS:

 */
int findUnsortedSubarray(std::vector<int>& nums) {
    size_t len = nums.size();
    if (len == 0) {
        return 0;
    }
    int start = 1;
    int end = 0;
    int min = nums.back();
    int max = nums.front();
    for (size_t i = 1; i < len; ++i) {
        max = std::max(max, nums[i]);
        min = std::min(min, nums[len - i - 1]);
        if (nums[i] < max) {
            end = i;
        }
        if (min < nums[len - i - 1]) {
            start = len - i - 1;
        }
    }
    return end - start + 1;
}

FTEST(test_findUnsortedSubarray) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = findUnsortedSubarray(nns);
        LOG(INFO) << nums << " unsorted sub array length: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 0);
    FEXP(t({1, 2}), 0);
    FEXP(t({1, 2, 3}), 0);
    FEXP(t({1, 2, 3, 4}), 0);
    FEXP(t({1, 2, 3, 5}), 0);
    FEXP(t({2, 1}), 2);
    FEXP(t({3, 2, 1}), 3);
    FEXP(t({4, 3, 2, 1}), 4);
    FEXP(t({5, 4, 3, 2, 1}), 5);
    FEXP(t({1, 3, 2}), 2);
    FEXP(t({1, 3, 2, 4}), 2);
    FEXP(t({1, 4, 2, 3}), 3);
    FEXP(t({1, 2, 4, 3, 5}), 2);
    FEXP(t({1, 4, 2, 3, 5}), 3);
    FEXP(t({1, 5, 2, 3, 4}), 4);
    FEXP(t({2, 6, 4, 8, 10, 9, 15}), 5);
}

/**
 ///////////// 582.

 */


/**
 ///////////// 583.

 */


/**
 ///////////// 584.

 */


/**
 ///////////// 585.

 */


/**
 ///////////// 586.

 */


/**
 ///////////// 587.

 */


/**
 ///////////// 588.

 */


/**
 ///////////// 589.

 */


/**
 ///////////// 590.

 */



}