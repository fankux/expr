#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex32 {

/**
 ///////////// 321.

 */

/**
 ///////////// 322. Coin Change
You are given coins of different denominations and a total amount of money amount.
 Write a function to compute the fewest number of coins that you need to make up that amount.
 If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1

Note:
You may assume that you have an infinite number of each kind of coin.
 */
int coinChange(std::vector<int>& coins, int amount) {
    auto recursive_method = [&] {
        std::unordered_map<int, int> mm;
        std::function<int(int)> r_func;
        r_func = [&](int n) {
            if (n <= 0) {
                return n == 0 ? 0 : -1;
            }
            auto entry = mm.find(n);
            if (entry != mm.end()) {
                return entry->second;
            }
            int found = false;
            int res = INT_MAX;
            for (int coin : coins) {
                int re = r_func(n - coin);
                if (re != -1) {
                    found = true;
                    res = std::min(res, re + 1);
                }
            }
            mm.emplace(n, found ? res : -1);
            return found ? res : -1;
        };
        return r_func(amount);
    };
    auto dp_method = [&] {
        std::vector<int> state(amount + 1, amount + 1);
        state[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (coin <= i) {
                    state[i] = std::min(state[i], 1 + state[i - coin]);
                }
            }
        }
        return state.empty() ? 0 : (state.back() == amount + 1 ? -1 : state.back());
    };
    auto sorted_find = [&] {
        if (amount == 0) {
            return 0;
        }
        int res = INT_MAX;
        std::sort(coins.begin(), coins.end());
        std::function<void(int, int, int)> r_func;
        r_func = [&](int start, int target, int cur) {
            if (start < 0) {
                return;
            }
            int quotient = target / coins[start];
            if (target % coins[start] == 0) {
                res = std::min(res, cur + quotient);
                return;
            }
            for (int i = quotient; i >= 0; --i) {
                if (cur + i >= res - 1) {   // TODO.. do not understand
                    break;
                }
                r_func(start - 1, target - i * coins[start], cur + i);
            }
        };
        r_func(coins.size() - 1, amount, 0);
        return res == INT_MAX ? -1 : res;
    };
    return sorted_find();
}

FTEST(test_coinChange) {
    auto t = [](const std::vector<int>& nums, int n) {
        std::vector<int> nns = nums;
        auto re = coinChange(nns, n);
        LOG(INFO) << nums << " coin change " << n << ": " << re;
        return re;
    };

    FEXP(t({}, 0), 0);
    FEXP(t({}, 1), -1);
    FEXP(t({2}, 3), -1);
    FEXP(t({1}, 1), 1);
    FEXP(t({1}, 2), 2);
    FEXP(t({1}, 3), 3);
    FEXP(t({2}, 2), 1);
    FEXP(t({1, 2}, 2), 1);
    FEXP(t({1, 2}, 3), 2);
    FEXP(t({1, 2, 5}, 11), 3);
    FEXP(t({1, 2, 5}, 100), 20);
}

/**
 ///////////// 323.

 */


/**
 ///////////// 324. Wiggle Sort II
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:
Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].

Example 2:
Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].

Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

 THOUGHTS:
    Sort first, split to two half at the middle, get a number from back to begin
        (only this way can ensure the foward number is greater than previous) of each half.
 */
void wiggleSort(std::vector<int>& nums) {
    std::vector<int> nn = nums;
    std::sort(nn.begin(), nn.end());
    int i = nn.size() - 1;
    int j = (nn.size() - 1) / 2;
    for (size_t k = 0; k < nn.size(); ++k) {
        nums[k] = (k & 1) ? nn[i--] : nn[j--];
    }
}

FTEST(test_wiggleSort) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        wiggleSort(nns);
        LOG(INFO) << nums << " wiggle sort: " << nns;
    };

    t({});
    t({1});
    t({1, 2});
    t({2, 1});
    t({2, 1});
    t({2, 1, 3});
    t({2, 1, 3, 4});
    t({2, 1, 5, 3, 4});
}

/**
 ///////////// 325.

 */


/**
 ///////////// 326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Example 1:
Input: 27
Output: true

Example 2:
Input: 0
Output: false

Example 3:
Input: 9
Output: true

Example 4:
Input: 45
Output: false

 Follow up:
Could you do it without using any loop / recursion?
 */
bool isPowerOfThree(int n) {
    return (n > 0 && 1162261467 % n == 0);
}

/**
 ///////////// 327.

 */


/**
 ///////////// 328.

 */


/**
 ///////////// 329.

 */


/**
 ///////////// 330.

 */



}