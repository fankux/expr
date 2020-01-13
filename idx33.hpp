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
    std::deque<TreeNode*> qq{root};
    int pre = 0;
    int res = 0;
    while (!qq.empty()) {
        int sum = 0;
        for (size_t i = qq.size(); i > 0; --i) {
            TreeNode* p = qq.front();
            qq.pop_front();
            if (p == nullptr) {
                continue;
            }
            sum += p->val;
            qq.push_back(p->left);
            qq.push_back(p->right);
        }
        int t = res;
        res = std::max(res, pre + sum);
        pre = t;
    }
    return res;
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
 ///////////// 338.

 */


/**
 ///////////// 339.

 */


/**
 ///////////// 340.

 */



}