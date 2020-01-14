#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex33 {

/**
 ///////////// 331.

 */

/**
 ///////////// 332.

 */


/**
 ///////////// 333.

 */


/**
 ///////////// 334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of length 3 exists
 or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:
Input: [1,2,3,4,5]
Output: true

Example 2:
Input: [5,4,3,2,1]
Output: false
 */
bool increasingTriplet(std::vector<int>& nums) {
    std::vector<int> vv;
    for (auto num : nums) {
        size_t l = 0;
        size_t r = vv.size();
        while (l < r) {
            size_t mid = l + (r - l) / 2;
            if (vv[mid] < num) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        if (l >= vv.size()) {
            vv.emplace_back(num);
            if (vv.size() >= 3) {
                return true;
            }
        } else {
            vv[l] = num;
        }
    }
    return false;
}

FTEST(test_increasingTriplet) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = increasingTriplet(nns);
        LOG(INFO) << nums << " exist length of 3 LIS: " << re;
        return re;
    };

    FEXP(t({}), false);
    FEXP(t({1}), false);
    FEXP(t({2, 1}), false);
    FEXP(t({2, 1, 1}), false);
    FEXP(t({2, 1, 2}), false);
    FEXP(t({2, 1, 5, 3}), false);
    FEXP(t({2, 1, 10, 4, 5}), true);
    FEXP(t({10, 9, 2, 5, 3, 7, 101, 18}), true);
    FEXP(t({4, 10, 4, 3, 8, 9}), true);
    FEXP(t({1, 3, 6, 7, 9, 4, 10, 5, 6}), true);
}

/**
 ///////////// 335.

 */


/**
 ///////////// 336.

 */


/**
 ///////////// 337. House Robber III
The thief has found himself a new place for his thievery again.
 There is only one entrance to this area, called the "root."
 Besides the root, each house has one and only one parent house.
 After a tour, the smart thief realized that "all houses in this place forms a binary tree".
 It will automatically contact the police if two directly-linked houses were broken into
 on the same night.
Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
Input: [3,2,3,null,3,null,1]
     3
    / \
   2   3
    \   \
     3   1

Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:
Input: [3,4,5,1,3,null,1]
     3
    / \
   4   5
  / \   \
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 */
int robIII(TreeNode* root) {
    std::function<int(TreeNode*, int&, int&)> rfunc;
    rfunc = [&rfunc](TreeNode* p, int& l, int& r) {
        if (p == nullptr) {
            return 0;
        }
        int ll = 0;
        int lr = 0;
        int rl = 0;
        int rr = 0;
        l = rfunc(p->left, ll, lr);
        r = rfunc(p->right, rl, rr);
        return std::max(p->val + ll + lr + rl + rr, l + r);
    };
    int l = 0;
    int r = 0;
    return rfunc(root, l, r);
}

FTEST(test_robIII) {
    auto t = [&](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = robIII(tree);
        LOG(INFO) << " max profit : " << re << " of tree:\n" << print_tree(tree);
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 1);
    FEXP(t({1, 2, 3}), 5);
    FEXP(t({6, 2, 3}), 6);
    FEXP(t({3, 2, 3, nullptr, 3, nullptr, 1}), 7);
    FEXP(t({3, 4, 5, 1, 3, nullptr, 1}), 9);
    FEXP(t({4, 1, nullptr, 2, nullptr, 3}), 7);
    FEXP(t({4, nullptr, 1, nullptr, 2, nullptr, 3}), 7);
}

/**
 ///////////// 338. Counting Bits
Given a non negative integer number num.
 For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's
 in their binary representation and return them as an array.

Example 1:
Input: 2
Output: [0,1,1]

Example 2:
Input: 5
Output: [0,1,1,2,1,2]

Follow up:
It is very easy to come up with a solution with run time O(n*sizeof(integer)).
 But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like
 __builtin_popcount in c++ or in any other language.
 */
std::vector<int> countBits(int num) {
    std::vector<int> res(num + 1, 0);
    uint32_t p = 1;
    for (int i = 1; i <= num;) {
        for (uint32_t j = 0; j < p && i <= num; ++j) {
            res[p + j] = res[j] + 1;
            ++i;
        }
        p = p << 1;
    }
    return res;
}

FTEST(test_countBits) {
    auto t = [&](int num) {
        auto re = countBits(num);
        LOG(INFO) << " 0~" << num << " bits count : " << re;
        return re;
    };

    t(0);
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
    t(50);
}

/**
 ///////////// 339.

 */


/**
 ///////////// 340.

 */



}