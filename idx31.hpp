#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex31 {

/**
 ///////////// 311.

 */

/**
 ///////////// 312.

 */


/**
 ///////////// 313.

 */


/**
 ///////////// 314.

 */


/**
 ///////////// 315. Count of Smaller Numbers After Self
You are given an integer array nums and you have to return a new counts array.
 The counts array has the property where counts[i] is the number of smaller elements
 to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

 THOUGHTS:
    iterate from end to begin, construct sorted array.
 */
std::vector<int> countSmaller(std::vector<int>& nums) {
    size_t len = nums.size();
    std::vector<int> res(len);
    std::vector<int> mm;
    for (int i = len - 1; i >= 0; --i) {
        size_t l = 0;
        size_t r = mm.size();
        while (l < r) {
            size_t mid = l + (r - l) / 2;
            if (mm[mid] < nums[i]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        res[i] = l;
        mm.insert(mm.begin() + l, nums[i]);
    }
    return res;
}

FTEST(test_countSmaller) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = countSmaller(nns);
        LOG(INFO) << nums << " smaller number after: " << re;
        return re;
    };

    t({});
    t({1});
    t({1, 1});
    t({1, 2});
    t({2, 1});
    t({2, 2});
    t({1, 1, 1});
    t({1, 1, 2});
    t({1, 2, 1});
    t({2, 1, 1});
    t({1, 2, 2});
    t({2, 1, 2});
    t({2, 2, 1});
    t({2, 2, 2});
    t({1, 2, 3});
    t({1, 3, 2});
    t({2, 1, 3});
    t({2, 3, 1});
    t({3, 1, 2});
    t({3, 2, 1});
    t({5, 2, 6, 1});
    t({5, 2, 1, 6});
}

/**
 ///////////// 316.

 */


/**
 ///////////// 317.

 */


/**
 ///////////// 318.

 */


/**
 ///////////// 319.

 */


/**
 ///////////// 320.

 */



}