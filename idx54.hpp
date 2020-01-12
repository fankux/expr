#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex54 {

/**
 ///////////// 541.

 */

/**
 ///////////// 542.

 */


/**
 ///////////// 543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree.
 The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
 This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
 */
int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    std::function<int(TreeNode*)> rfunc;
    rfunc = [&](TreeNode* p) {
        if (p == nullptr) {
            return 0;
        }
        int lh = rfunc(p->left);
        int rh = rfunc(p->right);
        res = std::max(res, lh + rh);
        return 1 + std::max(lh, rh);
    };
    rfunc(root);
    return res;
}

FTEST(test_diameterOfBinaryTree) {
    auto t = [&](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = diameterOfBinaryTree(tree);
        LOG(INFO) << "diameter " << re << " of tree\n" << print_tree(tree);
        return re;
    };

    FEXP(t({1, 2, 3}), 2);
    FEXP(t({1, nullptr, 2}), 1);
    FEXP(t({1, 2, nullptr}), 1);
    FEXP(t({1, 2, 3, 4}), 3);
    FEXP(t({1, 2, 3, 4, 5}), 3);
    FEXP(t({1, 2, 3, nullptr, 4, nullptr, nullptr}), 3);
    FEXP(t({1, 2, 3, nullptr, nullptr, 4, nullptr}), 3);
    FEXP(t({1, 2, 3, nullptr, nullptr, nullptr, 4}), 3);
    FEXP(t({1, 2, 3, 4, nullptr, 5}), 4);
    FEXP(t({1, 2, 3, 4, nullptr, nullptr, 5}), 4);
    FEXP(t({1, 2, 3, 4, nullptr, nullptr, 5, 6}), 5);
}

/**
 ///////////// 544.

 */


/**
 ///////////// 545.

 */


/**
 ///////////// 546.

 */


/**
 ///////////// 547.

 */


/**
 ///////////// 548.

 */


/**
 ///////////// 549.

 */


/**
 ///////////// 550.

 */



}