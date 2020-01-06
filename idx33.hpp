#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex33 {

/**
 ///////////// 331.

 */

/**
 ///////////// 332.

 */


/**
 ///////////// 333.

 */


/**
 ///////////// 334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of length 3 exists
 or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:
Input: [1,2,3,4,5]
Output: true

Example 2:
Input: [5,4,3,2,1]
Output: false
 */
bool increasingTriplet(std::vector<int>& nums) {
    std::vector<int> vv;
    for (auto num : nums) {
        size_t l = 0;
        size_t r = vv.size();
        while (l < r) {
            size_t mid = l + (r - l) / 2;
            if (vv[mid] < num) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        if (l >= vv.size()) {
            vv.emplace_back(num);
            if (vv.size() >= 3) {
                return true;
            }
        } else {
            vv[l] = num;
        }
    }
    return false;
}

FTEST(test_increasingTriplet) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = increasingTriplet(nns);
        LOG(INFO) << nums << " exist length of 3 LIS: " << re;
        return re;
    };

    FEXP(t({}), false);
    FEXP(t({1}), false);
    FEXP(t({2, 1}), false);
    FEXP(t({2, 1, 1}), false);
    FEXP(t({2, 1, 2}), false);
    FEXP(t({2, 1, 5, 3}), false);
    FEXP(t({2, 1, 10, 4, 5}), true);
    FEXP(t({10, 9, 2, 5, 3, 7, 101, 18}), true);
    FEXP(t({4, 10, 4, 3, 8, 9}), true);
    FEXP(t({1, 3, 6, 7, 9, 4, 10, 5, 6}), true);
}

/**
 ///////////// 335.

 */


/**
 ///////////// 336.

 */


/**
 ///////////// 337.

 */


/**
 ///////////// 338.

 */


/**
 ///////////// 339.

 */


/**
 ///////////// 340.

 */



}