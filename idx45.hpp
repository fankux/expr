#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex45 {

/**
 ///////////// 451.

 */

/**
 ///////////// 452.

 */


/**
 ///////////// 453.

 */


/**
 ///////////// 454. 4Sum II
Given four lists A, B, C, D of integer values,
 compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.
To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500.
 All integers are in the range of -2^28 to 2^28 - 1
 and the result is guaranteed to be at most 2^31 - 1.

Example:
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 */
int fourSumCount(std::vector<int>& A, std::vector<int>& B,
        std::vector<int>& C, std::vector<int>& D) {
    int res = 0;
    size_t len = A.size();
    auto loop_bin_search_method = [&] {
        std::sort(A.begin(), A.end());
        std::sort(B.begin(), B.end());
        std::sort(C.begin(), C.end());
        std::sort(D.begin(), D.end());
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < len; ++j) {
                int target = 0 - A[i];
                if (target < 0 && C[0] > 0 && D[0] > 0) {
                    continue;
                }
                int l = 0;
                int r = len - 1;
                while (l < len && r >= 0) {
                    int sum = B[j] + C[l] + D[r];
                    if (sum == target) {
                        int left_dup = 1;
                        while (r > 0 && D[r] == D[r - 1]) {
                            ++left_dup;
                            --r;
                        }
                        int right_dup = 1;
                        while (l < len - 1 && C[l] == C[l + 1]) {
                            ++right_dup;
                            ++l;
                        }
                        res += left_dup * right_dup;
                        ++l;
                        --r;
                    } else if (sum < target) {
                        ++l;
                    } else {
                        --r;
                    }
                }
            }
        }
        return res;
    };
    auto hash_method = [&] {
        std::unordered_map<int, int> mm;
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < len; ++j) {
                mm[A[i] + B[j]]++;
            }
        }
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < len; ++j) {
                res += mm[-1 * (C[i] + D[j])];
            }
        }
        return res;
    };
    return hash_method();
}

FTEST(test_fourSumCount) {
    auto t = [](const std::vector<int>& a, const std::vector<int>& b,
            const std::vector<int>& c, const std::vector<int>& d) {
        std::vector<int> nna = a;
        std::vector<int> nnb = b;
        std::vector<int> nnc = c;
        std::vector<int> nnd = d;
        auto re = fourSumCount(nna, nnb, nnc, nnd);
        LOG(INFO) << a << ", " << b << ", " << c << ", " << d << " sum 0 count: " << re;
        return re;
    };

    FEXP(t({}, {}, {}, {}), 0);
    FEXP(t({1}, {1}, {1}, {1}), 0);
    FEXP(t({1}, {-1}, {1}, {-1}), 1);
    FEXP(t({-1}, {1}, {-1}, {1}), 1);
    FEXP(t({-1}, {2}, {-1}, {0}), 1);
    FEXP(t({1, -1}, {1, -1}, {1, -1}, {1, -1}), 6);
    FEXP(t({-1, -1}, {-1, 1}, {-1, 1}, {1, -1}), 6);
    FEXP(t({1, 2}, {-1, -2}, {2, -1}, {0, 2}), 2);
    FEXP(t({0, 1, -1}, {-1, 1, 0}, {0, 0, 1}, {-1, 1, 1}), 17);
}

/**
 ///////////// 455.

 */


/**
 ///////////// 456.

 */


/**
 ///////////// 457.

 */


/**
 ///////////// 458.

 */


/**
 ///////////// 459.

 */


/**
 ///////////// 460.

 */



}