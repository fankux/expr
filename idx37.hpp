#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex37 {

/**
 ///////////// 371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = -2, b = 3
Output: 1
 */
int getSum(int a, int b) {
    int res = 0;
    bool carry = false;
    for (int i = 0; i < 32; ++i) {
        int mask = 1 << i;
        int count = 0;
        count += (a & mask) != 0 ? 1 : 0;
        count += (b & mask) != 0 ? 1 : 0;
        count += carry ? 1 : 0;
        carry = count > 1;
        res |= count % 2 == 1 ? mask : 0;
    }
    return res;
}

FTEST(test_getSum) {
    auto t = [&](int a, int b) {
        auto re = getSum(a, b);
        LOG(INFO) << a << " + " << b << " = " << re;
        return re;
    };

    FEXP(t(0, 0), 0);
    FEXP(t(0, 1), 1);
    FEXP(t(1, 0), 1);
    FEXP(t(1, 1), 2);
    FEXP(t(1, 2), 3);
    FEXP(t(0, INT_MIN), INT_MIN);
    FEXP(t(0, INT_MAX), INT_MAX);
    FEXP(t(INT_MIN, INT_MAX), -1);
    FEXP(t(-2, 3), 1);
}

/**
 ///////////// 372.

 */


/**
 ///////////// 373.

 */


/**
 ///////////// 374.

 */


/**
 ///////////// 375.

 */


/**
 ///////////// 376.

 */


/**
 ///////////// 377.

 */


/**
 ///////////// 378.

 */


/**
 ///////////// 379.

 */


/**
 ///////////// 380.

 */



}