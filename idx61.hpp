#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex61 {

/**
 ///////////// 611.

 */

/**
 ///////////// 612.

 */


/**
 ///////////// 613.

 */


/**
 ///////////// 614.

 */


/**
 ///////////// 615.

 */


/**
 ///////////// 616.

 */


/**
 ///////////// 617. Merge Two Binary Trees
Given two binary trees and imagine that when you put one of them to cover the other,
 some nodes of the two trees are overlapped while the others are not.
You need to merge them into a new binary tree. The merge rule is that if two nodes overlap,
 then sum node values up as the new value of the merged node. Otherwise,
 the NOT null node will be used as the node of new tree.

Example 1:
Input:
	Tree 1                     Tree 2
          1                         2
         / \                       / \
        3   2                     1   3
       /                           \   \
      5                             4   7
Output:
Merged tree:
	     3
	    / \
	   4   5
	  / \   \
	 5   4   7

Note: The merging process must start from the root nodes of both trees.
 */
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    std::function<TreeNode*(TreeNode*&, TreeNode*, TreeNode*)> rfunc;
    rfunc = [&](TreeNode*& p, TreeNode* l, TreeNode* r) {
        if (l == nullptr || r == nullptr) {
            p = l == nullptr ? r : l;
            return p;
        }
        p->val = l->val + r->val;
        rfunc(p->left, l->left, r->left);
        rfunc(p->right, l->right, r->right);
        return p;
    };
    return rfunc(t1 != nullptr ? t1 : t2, t1, t2);
}

FTEST(test_mergeTrees) {
    auto t = [&](const std::vector<TreeNodeStub>& nums1, const std::vector<TreeNodeStub>& nums2) {
        TreeNode* t1 = create_tree(nums1);
        TreeNode* t2 = create_tree(nums2);
        LOG(INFO) << "tree1:\n" << print_tree(t1) << ", tree2:\n" << print_tree(t2);
        auto re = mergeTrees(t1, t2);
        LOG(INFO) << " to:\n" << print_tree(re);
        return re;
    };
    t({1, 3, nullptr, 5}, {2, 1, 3, nullptr, 4, nullptr, 7});
    t({1, 3, 2, 5}, {2, 1, 3, nullptr, 4, nullptr, 7});
}

/**
 ///////////// 618.

 */


/**
 ///////////// 619.

 */


/**
 ///////////// 620.

 */



}