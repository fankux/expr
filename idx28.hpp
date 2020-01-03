#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex28 {

/**
 ///////////// 281.

 */

/**
 ///////////// 282.

 */


/**
 ///////////// 283. Move Zeroes
Given an array nums, write a function to move all 0's to the end of it
 while maintaining the relative order of the non-zero elements.

Example:
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Note:
 - You must do this in-place without making a copy of the array.
 - Minimize the total number of operations.

THOUGHTS:
    i is the index of last found 0
    j is the index of last found not 0

    condition 1: if i, j adjucent, after swap, i++ still at the index of 0
    0 1 2   =>    0 1 2
    i j           i j

    condition 2: if i, j not adjucent, the gap between must be all 0 or i, j must be adjucent.
        so i++ still at the index of 0 too.
    0 0 2 4   =>   0 0 2 4
    i   j            i   j

    condition 3: if i==j≠0, next number is not 0, there still at condition 3 after swap(do nothing)
    1 1 2 4   =>   1 1 2 4
   i,j              i,j

    condition 4: if i==j≠0, next number is 0, after swap(do nothing),
        things change to condition 1 or condition 2
    1 0 2 4   =>   1 0 2 4   =>   1 0 2 4
   i,j              i,j             i j

 */
void moveZeroes(std::vector<int>& nums) {
    for (size_t i = 0, j = 0; j < nums.size(); ++j) {
        if (nums[j] != 0) {
            std::swap(nums[i++], nums[j]);
        }
    }
}

FTEST(test_moveZeroes) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        moveZeroes(nns);
        LOG(INFO) << nums << " move zeros: " << nns;
    };

    t({});
    t({0});
    t({1});
    t({0, 0});
    t({0, 1});
    t({1, 0});
    t({1, 1});
    t({0, 0, 0});
    t({1, 0, 0});
    t({0, 1, 0});
    t({0, 0, 1});
    t({0, 1, 1});
    t({1, 0, 1});
    t({1, 1, 0});
    t({1, 1, 1});
    t({0, 1, 0, 3, 12});
}

/**
 ///////////// 284.

 */


/**
 ///////////// 285.

 */


/**
 ///////////// 286.

 */


/**
 ///////////// 287. Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
 prove that at least one duplicate number must exist.
 Assume that there is only one duplicate number, find the duplicate one.

Example 1:
Input: [1,3,4,2,2]
Output: 2

Example 2:
Input: [3,1,3,4,2]
Output: 3

Note:
 - You must not modify the array (assume the array is read only).
 - You must use only constant, O(1) extra space.
 - Your runtime complexity should be less than O(n^2).
 - There is only one duplicate number in the array, but it could be repeated more than once.

 THOUGHTS:
   BINARY_SEARCH_METHOD:
    - Thought numbers from 1 to n whitout duplicates.
        for each number N, the COUNT of numbers that less equal(<=) to N must be N.
    - Now there are some duplicates exist. We get a MIDDLE[floor(1+n)/2]
        - if duplicates less equal to MIDDLE,
          the COUNT of numbers that less equal to MIDDLE must be greater than(>) MIDDLE
        - if duplicates greater than MIDDLE,
          the COUNT of numbers that less equal to MIDDLE must be less equal to (<=) MIDDLE
    In this way, the binary search driven by the numbers sequence instead of array indices,
    so the order of array dosen't matter.

   LINK_METHOD: Treat it as a linked list with cycles, find the any start point of cycle.

   BIT_MANIPULATION_METHOD:
    - if no duplicate numbers exist, for each bit, nums[0]~nums[n] must equal to 0~n.
    - if dupliates exist, for each bit,
        count of bit 1 of nums[0]~nums[n] larger than 0~n, means duplicate number is 1 at this bit,
        and number could be recovered in this way.

    for example: 3,1,2,3
     0~n     nums[0]~nums[n]
    0  00    3  11
    1  01    1  01    ===>  duplicate number 3 compare to left 0, it's obviously
    2  10    2  10
    3  11    3  11

    for example: 3,1,2,3,3
     0~n     nums[0]~nums[n]
    0  000    3  011
    1  001    1  001
    2  010    2  010
    3  011    3  011
    4  100    3  011

 */
int findDuplicate(std::vector<int>& nums) {
    size_t len = nums.size();
    auto bin_search_method = [&] {
        int l = 1;
        int r = len;
        while (l < r) {
            int mid = l + (r - l) / 2;
            int count = 0;
            for (int num : nums) {
                count += num <= mid ? 1 : 0;
            }
            if (count <= mid) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return r;
    };
    auto link_method = [&] {
        int slow = nums[0];
        int fast = nums[0];
        while (slow < len && fast < len) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) {
                break;
            }
        }
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    };
    auto bit_manipulation_method = [&] {
        int res = 0;
        uint32_t mask = 1;
        for (size_t b = 0; b < 32; ++b) {
            int cnt1 = 0;
            int cnt2 = 0;
            for (size_t i = 0; i < len; ++i) {
                if ((nums[i] & mask) > 0) {
                    ++cnt1;
                }
                if ((i & mask) > 0) {
                    ++cnt2;
                }
            }
            if (cnt1 > cnt2) {
                res |= mask;
            }
            mask = mask << 1;
        }
        return res;
    };
    return bit_manipulation_method();
}

FTEST(test_findDuplicate) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = findDuplicate(nns);
        LOG(INFO) << nums << " duplicate number: " << re;
        return re;
    };
    FEXP(t({0, 0}), 0);
    FEXP(t({0, 0}), 0);
    FEXP(t({1, 1, 1}), 1);
    FEXP(t({1, 2, 1}), 1);
    FEXP(t({1, 2, 1}), 1);
    FEXP(t({1, 2, 2}), 2);
    FEXP(t({2, 2, 1}), 2);
    FEXP(t({2, 1, 2}), 2);
    FEXP(t({1, 3, 4, 2, 2}), 2);
    FEXP(t({3, 1, 3, 4, 2}), 3);
}

/**
 ///////////// 288.

 */


/**
 ///////////// 289.

 */


/**
 ///////////// 290.

 */



}