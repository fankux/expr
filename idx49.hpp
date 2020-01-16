#pragma once

#include <queue>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex49 {

/**
 ///////////// 491.

 */

/**
 ///////////// 492.

 */


/**
 ///////////// 493.

 */


/**
 ///////////// 494. Target Sum
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have
 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
There are 5 ways to assign symbols to make the sum of nums be target 3.

Note:
 1. The length of the given array is positive and will not exceed 20.
 2. The sum of elements in the given array will not exceed 1000.
 3. Your output answer is guaranteed to be fitted in a 32-bit integer.
 */
int findTargetSumWays(std::vector<int>& nums, int S) {
    size_t len = nums.size();
    auto dp_iterate_method = [&] {
        std::unordered_map<int, int> vv;
        vv[0] = 1;
        for (int num : nums) {
            std::unordered_map<int, int> t;
            for (auto& v : vv) {
                int sum = v.first;
                int cnt = v.second;
                t[sum + num] += cnt;
                t[sum - num] += cnt;
            }
            vv.swap(t);
        }
        return vv[S];
    };
    auto dfs_method = [&] {
        std::vector<std::map<int, int>> mm(len);
        std::function<uint32_t(int, uint32_t)> rfunc;
        rfunc = [&](int start, uint32_t sum) -> uint32_t {
            if (start >= len) {
                return sum == 0 ? 1 : 0;
            }
            auto entry = mm[start].find(sum);
            if (entry != mm[start].end()) {
                return entry->second;
            }
            uint32_t ret = 0;
            ret += rfunc(start + 1, sum + nums[start]);
            ret += rfunc(start + 1, sum - nums[start]);
            mm[start].emplace(sum, ret);
            return ret;
        };
        return rfunc(0, S);
    };
    return dp_iterate_method();
}

FTEST(test_findTargetSumWays) {
    auto t = [](const std::vector<int>& nums, int s) {
        std::vector<int> nns = nums;
        auto re = findTargetSumWays(nns, s);
        LOG(INFO) << nns << " sum to " << s << ", count: " << re;
        return re;
    };

    FEXP(t({}, 0), 1);
    FEXP(t({}, 1), 0);
    FEXP(t({1}, 0), 0);
    FEXP(t({1}, 2), 0);
    FEXP(t({1}, 1), 1);
    FEXP(t({1, 1}, 0), 2);
    FEXP(t({1, 1}, 1), 0);
    FEXP(t({1, 1}, 2), 1);
    FEXP(t({1, 1, 1}, 0), 0);
    FEXP(t({1, 1, 1}, 1), 3);
    FEXP(t({1, 1, 1}, -1), 3);
    FEXP(t({1, 1, 1}, 2), 0);
    FEXP(t({1, 1, 1}, 3), 1);
    FEXP(t({1, 1, 1, 1, 1}, 3), 5);
    FEXP(t({47, 23, 38, 38, 3, 37, 18, 29, 27, 39,
            29, 25, 4, 2, 0, 47, 10, 39, 23, 17}, 15), 6348);
    FEXP(t({40, 19, 30, 48, 8, 50, 13, 31, 29, 38,
            35, 31, 40, 47, 7, 16, 31, 33, 45, 6}, 49), 5305);
    FEXP(t({2, 107, 109, 113, 127, 131, 137, 3, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 47, 53},
            2147483647), 0);
}

/**
 ///////////// 495.

 */


/**
 ///////////// 496.

 */


/**
 ///////////// 497.

 */


/**
 ///////////// 498.

 */


/**
 ///////////// 499.

 */


/**
 ///////////// 500.

 */



}