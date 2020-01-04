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
 ///////////// 324.

 */


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