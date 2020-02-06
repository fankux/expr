#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex27 {

/**
 ///////////// 271.

 */

/**
 ///////////// 272.

 */


/**
 ///////////// 273.

 */


/**
 ///////////// 274.

 */


/**
 ///////////// 275.

 */


/**
 ///////////// 276.

 */


/**
 ///////////// 277.

 */


/**
 ///////////// 278.

 */


/**
 ///////////// 279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers
 (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

 THOUGHTS:
    A number could treat as a plain number plus a square number, so state change formula:
        dp[i + j * j] = min(dp[i] + 1, dp[i + j * j])

 */
int numSquares(int n) {
    while (n > 0 && n % 4 == 0) {
        n /= 4;
    }
    std::vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i <= n; ++i) {  // i from 0 for numbers less than 4
        for (int j = 1; i + j * j <= n; ++j) {
            dp[i + j * j] = std::min(dp[i + j * j], 1 + dp[i]); // 1 means j*j is a square number
        }
    }
    return dp.back();
}

FTEST(test_numSquares) {
    auto t = [&](int n) {
        auto re = numSquares(n);
        LOG(INFO) << n << " minimum square count: " << re;
        return re;
    };

    t(0);
    FEXP(t(1), 1);
    FEXP(t(2), 2);
    FEXP(t(3), 3);
    FEXP(t(4), 1);
    FEXP(t(5), 2);
    FEXP(t(6), 3);
    FEXP(t(7), 4);
    FEXP(t(8), 2);
    FEXP(t(9), 1);
    FEXP(t(10), 2);
    FEXP(t(11), 3);
    FEXP(t(12), 3);
    FEXP(t(13), 2);
    FEXP(t(14), 3);
    FEXP(t(15), 4);
    FEXP(t(16), 1);
    FEXP(t(49), 1);
    FEXP(t(50), 2);
}

/**
 ///////////// 280.

 */



}