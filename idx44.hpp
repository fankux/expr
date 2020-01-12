#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex44 {

/**
 ///////////// 441.

 */

/**
 ///////////// 442.

 */


/**
 ///////////// 443.

 */


/**
 ///////////// 444.

 */


/**
 ///////////// 445.

 */


/**
 ///////////// 446.

 */


/**
 ///////////// 447.

 */


/**
 ///////////// 448.
Find All Numbers Disappeared in an Array
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array),
 some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime?
 You may assume the returned list does not count as extra space.

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]

 THOUGHTS:
    For each number as index to a number and make it to negative,
        then iterate list, if a number not negative,
        means index of it not present in array because not number point to it.
 */
std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] > 0) {
            nums[idx] *= -1;
        }
    }
    std::vector<int> res;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            res.emplace_back(i + 1);
        }
    }
    return res;
}

FTEST(test_findDisappearedNumbers) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = findDisappearedNumbers(nns);
        LOG(INFO) << nums << " disappered number: " << re;
        return re;
    };

    t({4, 3, 2, 7, 8, 2, 3, 1});
}

/**
 ///////////// 449.

 */


/**
 ///////////// 450.

 */



}