#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex41 {

/**
 ///////////// 411.

 */

/**
 ///////////// 412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.
But for multiples of three it should output “Fizz” instead of the number
 and for the multiples of five output “Buzz”.
 For numbers which are multiples of both three and five output “FizzBuzz”.

Example:
n = 15,
Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
 */
std::vector<std::string> fizzBuzz(int n) {
    std::vector<std::string> res;
    int three = 3;
    int five = 5;
    for (int i = 1; i <= n; ++i) {
        if (i == three && i == five) {
            res.emplace_back("FizzBuzz");
            three += 3;
            five += 5;
        } else if (i == three) {
            res.emplace_back("Fizz");
            three += 3;
        } else if (i == five) {
            res.emplace_back("Buzz");
            five += 5;
        } else {
            res.emplace_back(std::to_string(i));
        }
    }
    return res;
}

FTEST(test_fizzBuzz) {
    auto t = [&](int n) {
        auto re = fizzBuzz(n);
        LOG(INFO) << n << " Fizz Buzz: " << re;
        return re;
    };

    t(1);
    t(2);
    t(3);
    t(4);
    t(5);
    t(6);
    t(7);
    t(8);
    t(9);
    t(10);
    t(20);
}

/**
 ///////////// 413.

 */


/**
 ///////////// 414.

 */


/**
 ///////////// 415.

 */


/**
 ///////////// 416. Partition Equal Subset Sum
Given a non-empty array containing only positive integers,
 find if the array can be partitioned into two subsets such that the sum of elements
 in both subsets is equal.

Note:
 - Each of the array element will not exceed 100.
 - The array size will not exceed 200.

Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

THOUGHTS:
 dp[i][j] means if there exist a subset from 0~i sum to j, the target is dp[len][sum/2]

                dp[i-1][j] || dp[i-1][j - nums[i-1]]    (j >= nums[i-1])
 dp[i][j] =  /
             \  dp[i-1][j]                              (j < nums[i-1])

 dp[i-1][j - nums[i-1]]: now there is exist subset could sum to j-nums[i-1], then
                         add a nums[i-1] make new subset sum to j.

 */
bool canPartition(std::vector<int>& nums) {
    size_t len = nums.size();
    uint32_t total = 0;
    auto sort_count_method = [&] {
        int mm[101] = {0};
        for (int num : nums) {
            ++mm[num];
            total += num;
        }
        if (nums.size() < 2 || (total & 1)) {
            return false;
        }
        total /= 2;
        if (total <= 100 && mm[total] > 0) {
            --mm[total];
        } else {
            std::sort(nums.begin(), nums.end());

            int sum = 0;
            for (int i = nums.size() - 1; i >= 0 && sum + nums[i] < total; --i) {
                sum += nums[i];
                --mm[nums[i]];
                if (total - sum <= 100 && mm[total - sum] > 0) {
                    --mm[total - sum];
                    sum = total;
                    break;
                }
            }
            for (int i = 0; i < nums.size() && sum + nums[i] < total; ++i) {
                sum += nums[i];
                --mm[nums[i]];
                if (total - sum <= 100 && mm[total - sum] > 0) {
                    --mm[total - sum];
                    sum = total;
                    break;
                }
            }
        }
        for (size_t i = 0; i < 101; ++i) {
            total -= i * mm[i];
        }
        return total == 0;
    };

    auto dp_method = [&]() -> bool {
        for (int num : nums) {
            total += num;
        }
        if (nums.size() < 2 || (total & 1)) {
            return false;
        }
        total /= 2;
        std::vector<bool> state(total + 1, false);
        state[0] = true;
        for (int num : nums) {
            for (int j = total; j >= num; --j) {
                state[j] = state[j] || state[j - num];
            }
        }
        return state.back();
    };
    return dp_method();
}

FTEST(test_canPartition) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = canPartition(nns);
        LOG(INFO) << nums << " can partition: " << re;
        return re;
    };

    FEXP(t({}), false);
    FEXP(t({1}), false);
    FEXP(t({1, 2}), false);
    FEXP(t({1, 1}), true);
    FEXP(t({1, 2, 5}), false);
    FEXP(t({1, 2, 3, 5}), false);
    FEXP(t({1, 5, 11, 5}), true);
    FEXP(t({100, 100, 100, 100, 100, 100, 100, 100}), true);
}

/**
 ///////////// 417.

 */


/**
 ///////////// 418.

 */


/**
 ///////////// 419.

 */


/**
 ///////////// 420.

 */



}