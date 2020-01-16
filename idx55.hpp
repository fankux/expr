#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex55 {

/**
 ///////////// 551.

 */

/**
 ///////////// 552.

 */


/**
 ///////////// 553. 
 
 */


/**
 ///////////// 554.

 */


/**
 ///////////// 555.

 */


/**
 ///////////// 556.

 */


/**
 ///////////// 557.

 */


/**
 ///////////// 558.

 */


/**
 ///////////// 559.

 */


/**
 ///////////// 560. Subarray Sum Equals K
Given an array of integers and an integer k,
 you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2

Note:
 1. The length of the array is in range [1, 20,000].
 2. The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

THOUGHTS(hashmap_method) :
    sum[cur] = sum[r] + t (r<=cur)
    if "sum[cur] - k" exist, means there was sum[r] happend, t==k, result added.

    k: 7
                   cur
                    ↓
    3       4       7   2   -3   1   4   2
    ├───┬───┘    └─┬─┤
    │   r          t │
    └───── sum ──────┘
                                cur
                                 ↓
    3   4   7   2   -3   1   4   2
    ├────────┬───────┘   └───┬───┤
    │        r               t   │
    └──────────── sum ───────────┘

 */
int subarraySum(std::vector<int>& nums, int k) {
    size_t len = nums.size();
    int res = 0;
    auto iterate_method = [&] {
        std::vector<int> state(len, 0);
        for (size_t i = 0; i < len; ++i) {
            if ((state[i] = nums[i]) == k) {
                ++res;
            }
            for (size_t j = i + 1; j < len; ++j) {
                if ((state[j] = state[j - 1] + nums[j]) == k) {
                    ++res;
                }
            }
        }
        return res;
    };
    auto hashmap_method = [&] {
        int sum = 0;
        std::unordered_map<int, int> mm{{0, 1}};
        for (size_t i = 0; i < len; ++i) {
            sum += nums[i];
            res += mm[sum - k];
            ++mm[sum];
        }
        return res;
    };
    return hashmap_method();
}

FTEST(test_subarraySum) {
    auto t = [](const std::vector<int>& nums, int k) {
        std::vector<int> nns = nums;
        auto re = subarraySum(nns, k);
        LOG(INFO) << nns << " sum to " << k << ", count: " << re;
        return re;
    };

    FEXP(t({}, 0), 0);
    FEXP(t({}, 1), 0);
    FEXP(t({1}, 0), 0);
    FEXP(t({1}, 2), 0);
    FEXP(t({1}, 1), 1);
    FEXP(t({1, 1}, 0), 0);
    FEXP(t({1, 1}, 1), 2);
    FEXP(t({1, 1}, 2), 1);
    FEXP(t({1, 1, 1}, 0), 0);
    FEXP(t({1, 1, 1}, 1), 3);
    FEXP(t({1, 1, 1}, 2), 2);
    FEXP(t({1, 1, 1}, 3), 1);
    FEXP(t({1, 2}, 1), 1);
    FEXP(t({1, 2}, 2), 1);
    FEXP(t({1, 2}, 3), 1);
    FEXP(t({1, 2, 3}, 1), 1);
    FEXP(t({1, 2, 3}, 2), 1);
    FEXP(t({1, 2, 3}, 3), 2);
    FEXP(t({1, 2, 3}, 4), 0);
    FEXP(t({1, 2, 3}, 5), 1);
    FEXP(t({1, 2, 3}, 6), 1);
}

}