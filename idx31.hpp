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
 ///////////// 312. Burst Balloons
Given n balloons, indexed from 0 to n-1.
 Each balloon is painted with a number on it represented by array nums.
 You are asked to burst all the balloons.
 If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
 Here left and right are adjacent indices of i. After the burst,
 the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:
Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

THOUGHTS:
    dp[i][j] means from i to j, max coins.

    dp[i][j] = std::max(dp[i][j], nums[i-1] * nums[k]* nums[j+1] + dp[i][k-1]+dp[k+1][j]
    Here k is the last balloon to be brusted in range i to j,
    now all the balloons in range i to j is brokens, nums[i-1] is left and nums[j+1] is right

    Note that we must iterate range from small to large
 */
int maxBurstBalloons(std::vector<int>& nums) {
    size_t len = nums.size();
    nums.insert(nums.begin(), 1);
    nums.emplace_back(1);
    std::vector<std::vector<int>> state(len + 2, std::vector<int>(len + 2, 0));
    for (size_t range = 1; range <= len; ++range) {
        for (size_t i = 1; i <= len - range + 1; ++i) {
            size_t j = i + range - 1;
            for (size_t k = i; k <= j; ++k) {
                state[i][j] = std::max(state[i][j],
                        nums[i - 1] * nums[k] * nums[j + 1] + state[i][k - 1] + state[k + 1][j]);
            }
        }
    }
    return state[1][len];
}

FTEST(test_maxBurstBalloons) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = maxBurstBalloons(nns);
        LOG(INFO) << nums << " max burst balloons: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 1);
    FEXP(t({2}), 2);
    FEXP(t({1, 1}), 2);
    FEXP(t({1, 2}), 4);
    FEXP(t({2, 1}), 4);
    FEXP(t({1, 2, 3}), 12);
    FEXP(t({3, 1, 5, 8}), 167);
    FEXP(t({7, 9, 8, 0, 7}), 1001);
    FEXP(t({7, 9, 8, 0, 7, 1, 3, 5, 5, 2}), 1582);
}

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