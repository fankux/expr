#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively
*/
bool isSymmetric(TreeNode* root) {
    std::vector<int> list;
    std::function<void(TreeNode*)> r_func;
    r_func = [&](TreeNode* p) {
        if (p == nullptr) {
            return;
        }
        list.emplace_back(p->val);
        r_func(p->left);
        r_func(p->right);
    };
    int idx = 0;
    std::function<bool(TreeNode*)> r_func_post_order;
    r_func_post_order = [&](TreeNode* p) {
        if (p == nullptr) {
            return true;
        }
        r_func(p->left);
        r_func(p->right);
        if (idx >= list.size()) {
            if (p->val != list[idx++]) {
                return false;
            }
        }
        return true;
    };
    r_func(root);
    return r_func_post_order(root);
}

FTEST(test_isSymmetric) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = isSymmetric(tree);
        LOG(INFO) << nodes << " is symmetric: " << re;
        return re;
    };

    FEXP(t({}), true);
    FEXP(t({1}), true);
    FEXP(t({1, 2, 2, 3, 4, 4, 3}), true);
    FEXP(t({1, 2, 2, nullptr, 3, nullptr, 3}), false);
}

/**
 ///////////// 102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values.
 (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    return {};
}

/**
 ///////////// 103. Binary Tree Zigzag Level Order Traversal
Given a binary tree, return the zigzag level order traversal of its nodes' values.
 (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
*/
std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    return {};
}

/**
 ///////////// 104. Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down
 to the farthest leaf node.
Note: A leaf is a node with no children.

Example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
*/
int maxDepth(TreeNode* root) {
    return 0;
}

/**
 ///////////// 105. Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:
    3
   / \
  9  20
    /  \
   15   7
*/
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    return nullptr;
}

/**
 ///////////// 106.

*/

/**
 ///////////// 107.

*/

/**
 ///////////// 108. Convert Sorted Array to Binary Search Tree
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth
 of the two subtrees of every node never differ by more than 1.

Example:
Given the sorted array: [-10,-3,0,5,9],
One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
      0
     / \
   -3   9
   /   /
 -10  5
*/
TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    return nullptr;
}

/**
 ///////////// 109.

*/

/**
 ///////////// 110.

*/

