#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

namespace LCIndex10 {

typedef LCListNode ListNode;

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
    std::function<bool(TreeNode*, TreeNode*)> r_func;
    r_func = [&](TreeNode* l, TreeNode* r) {
        if (l == nullptr && r == nullptr) {
            return true;
        }
        if (l == nullptr || r == nullptr) {
            return false;
        }
        return l->val == r->val && r_func(l->left, r->right) && r_func(l->right, r->left);
    };
    auto iter_func = [&] {
        std::deque<TreeNode*> qq;
        qq.emplace_back(root->left);
        qq.emplace_back(root->right);
        while (!qq.empty()) {
            size_t len = qq.size();
            if (len % 2 != 0) {
                return false;
            }
            for (size_t i = 0; i < len / 2; ++i) {
                TreeNode* l = qq.front();
                TreeNode* r = qq.back();
                qq.pop_front();
                qq.pop_back();
                if (l == nullptr && r == nullptr) {
                    continue;
                }
                if (l == nullptr || r == nullptr) {
                    return false;
                }
                if (l->val != r->val) {
                    return false;
                }
                qq.push_front(l->left);
                qq.push_front(l->right);
                qq.push_back(r->right);
                qq.push_back(r->left);
            }
        }
        return true;
    };
    return root == nullptr || iter_func();
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
    std::vector<std::vector<int>> res;
    std::deque<TreeNode*> qq;
    qq.emplace_back(root);
    while (!qq.empty()) {
        std::vector<int> levels;
        for (size_t i = qq.size(); i > 0; --i) {
            TreeNode* p = qq.front();
            qq.pop_front();
            if (p == nullptr) {
                continue;
            }
            levels.emplace_back(p->val);
            qq.push_back(p->left);
            qq.push_back(p->right);
        }
        if (!levels.empty()) {
            res.emplace_back(levels);
        }
    }
    return res;
}

FTEST(test_levelOrder) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = levelOrder(tree);
        LOG(INFO) << nodes << " level order: " << re;
        return re;
    };

    t({});
    t({nullptr});
    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, 2, 3});
    t({1, nullptr, 2, nullptr, 3});
    t({3, 9, 20, nullptr, nullptr, 15, 7});
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
    std::vector<std::vector<int>> res;
    std::deque<TreeNode*> qq;
    qq.emplace_back(root);
    bool flag = true;
    while (!qq.empty()) {
        std::vector<int> levels;
        for (size_t i = qq.size(); i > 0; --i) {
            TreeNode* p = flag ? qq.front() : qq.back();
            flag ? qq.pop_front() : qq.pop_back();
            if (p == nullptr) {
                continue;
            }
            levels.emplace_back(p->val);
            if (flag) {
                qq.push_back(p->left);
                qq.push_back(p->right);
            } else {
                qq.push_front(p->right);
                qq.push_front(p->left);
            }
        }
        flag = !flag;
        if (!levels.empty()) {
            res.emplace_back(levels);
        }
    }
    return res;
}

FTEST(test_zigzagLevelOrder) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = zigzagLevelOrder(tree);
        LOG(INFO) << nodes << " zigzag level order: " << re;
        return re;
    };

    t({});
    t({nullptr});
    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, nullptr, 2, nullptr, 3});
    t({1, 2, 3});
    t({1, 2, 3, 4, 5, 6, 7});
    t({3, 9, 20, nullptr, nullptr, 15, 7});
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
    return root == nullptr ? 0 : std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

FTEST(test_maxDepth) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = maxDepth(tree);
        LOG(INFO) << nodes << " tree max depth: " << re;
        return re;
    };

    t({});
    t({nullptr});
    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, nullptr, 2, nullptr});
    t({1, nullptr, 2, nullptr, 3});
    t({1, 2, 3, nullptr});
    t({1, 2, 3, 4});
    t({1, 2, 3, nullptr, 4});
    t({1, 2, 3, 4, nullptr});
    t({1, 2, 3, 4, nullptr, nullptr});
    t({1, 2, 3, 4, nullptr, nullptr, 7});
    t({1, 2, 3, 4, nullptr, nullptr, 7, 8});
    t({3, 9, 20, nullptr, nullptr, 15, 7});
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
TreeNode* buildTreePreIn(std::vector<int>& preorder, std::vector<int>& inorder) {
    TreeNode* root = nullptr;
    if (preorder.size() != inorder.size()) {
        return root;
    }
    std::function<TreeNode*(int, int, int)> r_func;
    r_func = [&](int i, int m, int len) -> TreeNode* {
        if (i < 0 || m < 0 || len <= 0) {
            return nullptr;
        }
        int k = m;
        for (; k < m + len; ++k) {
            if (preorder[i] == inorder[k]) {
                break;
            }
        }
        if (k >= m + len) {
            return nullptr;
        }
        int left_len = k - m;
        int right_len = m + len - k - 1;
        TreeNode* p = new TreeNode(preorder[i]);
        p->left = r_func(i + 1, k - left_len, left_len);
        p->right = r_func(i + 1 + left_len, k + 1, right_len);
        return p;
    };
    return r_func(0, 0, preorder.size());
}

FTEST(test_buildTreePreIn) {
    auto t = [](const std::vector<int>& preorder, const std::vector<int>& inorder) {
        std::vector<int> nns1 = preorder;
        std::vector<int> nns2 = inorder;
        TreeNode* re = buildTreePreIn(nns1, nns2);
        LOG(INFO) << "preorder:" << preorder << ", inorder:" << inorder << " build tree: \n" <<
                  print_tree(re);
        return re;
    };
    t({}, {});
    t({}, {1});
    t({1}, {});
    t({1}, {1});
    t({1, 2}, {1, 2});
    t({1, 2}, {2, 1});
    t({2, 1}, {1, 2});
    t({1, 2, 3}, {2, 1, 3});
    t({20, 15, 7}, {15, 20, 7});
    t({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
}

/**
 ///////////// 106. Construct Binary Tree from Inorder and Postorder Traversal
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
For example, given
inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:
    3
   / \
  9  20
    /  \
   15   7
*/
TreeNode* buildTreeInPost(std::vector<int>& inorder, std::vector<int>& postorder) {
    TreeNode* root = nullptr;
    if (postorder.size() != inorder.size()) {
        return root;
    }
    std::function<TreeNode*(int, int, int)> r_func;
    r_func = [&](int i, int m, int len) -> TreeNode* {
        if (i < 0 || m < 0 || len <= 0) {
            return nullptr;
        }
        int k = m;
        for (; k < m + len; ++k) {
            if (postorder[i] == inorder[k]) {
                break;
            }
        }
        if (k >= m + len) {
            return nullptr;
        }
        int left_len = k - m;
        int right_len = m + len - k - 1;
        TreeNode* p = new TreeNode(postorder[i]);
        p->left = r_func(i - 1 - right_len, k - left_len, left_len);
        p->right = r_func(i - 1, k + 1, right_len);
        return p;
    };
    return r_func(postorder.size() - 1, 0, postorder.size());
}

FTEST(test_buildTreeInPost) {
    auto t = [](const std::vector<int>& inorder, const std::vector<int>& postorder) {
        std::vector<int> nns1 = inorder;
        std::vector<int> nns2 = postorder;
        TreeNode* re = buildTreeInPost(nns1, nns2);
        LOG(INFO) << "inorder:" << inorder << ", postorder:" << postorder << " build tree: \n" <<
                  print_tree(re);
        return re;
    };
    t({}, {});
    t({}, {1});
    t({1}, {});
    t({1}, {1});
    t({2, 1}, {2, 1});
    t({1, 2}, {2, 1});
    t({2, 1, 3}, {2, 3, 1});
    t({15, 20, 7}, {7, 20, 3});
    t({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3});
}

/**
 ///////////// 107. Binary Tree Level Order Traversal II
Given a binary tree, return the bottom-up level order traversal of its nodes' values.
 (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
*/
std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
    std::vector<std::vector<int>> res;
    std::deque<TreeNode*> qq;
    qq.emplace_back(root);
    while (!qq.empty()) {
        std::vector<int> levels;
        for (size_t i = qq.size(); i > 0; --i) {
            TreeNode* p = qq.front();
            qq.pop_front();
            if (p == nullptr) {
                continue;
            }
            levels.emplace_back(p->val);
            qq.push_back(p->left);
            qq.push_back(p->right);
        }
        if (!levels.empty()) {
            res.insert(res.begin(), levels);
        }
    }
    return res;
}

FTEST(test_levelOrderBottom) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = levelOrderBottom(tree);
        LOG(INFO) << nodes << " level order: " << re;
        return re;
    };

    t({});
    t({nullptr});
    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, 2, 3});
    t({1, nullptr, 2, nullptr, 3});
    t({3, 9, 20, nullptr, nullptr, 15, 7});
}

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
    std::function<TreeNode*(int, int)> r_func;
    r_func = [&](int l, int h) -> TreeNode* {
        if (l >= h) {
            return nullptr;
        }
        int mid = l + (h - l) / 2;
        TreeNode* p = new TreeNode(nums[mid]);
        p->left = r_func(l, mid);
        p->right = r_func(mid + 1, h);
        return p;
    };
    return r_func(0, nums.size());
}

FTEST(test_sortedArrayToBST) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        TreeNode* re = sortedArrayToBST(nns);
        LOG(INFO) << nums << " converted tree: \n" << print_tree(re);
        return re;
    };

    t({});
    t({0});
    t({1});
    t({-1});
    t({1, 2});
    t({1, 2, 3});
    t({-1, 0, 1});
    t({-10, -3, 0, 5, 9});
}

/**
 ///////////// 109. Convert Sorted List to Binary Search Tree
Given a singly linked list where elements are sorted in ascending order,
 convert it to a height balanced BST.
For this problem, a height-balanced binary tree is defined as a binary tree in which the
 depth of the two subtrees of every node never differ by more than 1.

Example:
Given the sorted linked list: [-10,-3,0,5,9],
One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
      0
     / \
   -3   9
   /   /
 -10  5
*/
TreeNode* sortedListToBST(ListNode* head) {
    std::function<TreeNode*(ListNode* head)> r_func;
    r_func = [&](ListNode* head) -> TreeNode* {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* pre = nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            pre = slow;
            slow = slow->next;
        }
        if (pre) {
            pre->next = nullptr;
        }
        TreeNode* p = new TreeNode(slow->val);
        if (fast != slow) {
            p->left = r_func(head);
            p->right = r_func(slow->next);
        }
        return p;
    };
    return r_func(head);
}

FTEST(test_sortedListToBST) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        TreeNode* re = sortedListToBST(list);
        LOG(INFO) << nums << " converted tree: \n" << print_tree(re);
        return re;
    };

    t({});
    t({0});
    t({1});
    t({-1});
    t({1, 2});
    t({1, 2, 3});
    t({-1, 0, 1});
    t({-10, -3, 0, 5, 9});
}

/**
 ///////////// 110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as:
a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

Example 1:
Given the following tree [3,9,20,null,null,15,7]:
    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:
Given the following tree [1,2,2,3,3,null,null,4,4]:
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.
*/
bool isTreeBalanced(TreeNode* root) {
    std::function<int(TreeNode*)> r_func;
    r_func = [&](TreeNode* p) {
        if (p == nullptr) {
            return 0;
        }
        int lheight = r_func(p->left);
        int rheight = r_func(p->right);
        if (lheight == -1 || rheight == -1) {
            return -1;
        }
        return abs(lheight - rheight) <= 1 ? std::max(lheight, rheight) + 1 : -1;
    };
    return r_func(root) != -1;
}

FTEST(test_isTreeBalanced) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = isTreeBalanced(tree);
        LOG(INFO) << (re ? "" : "NOT") << " balanced tree: \n" << print_tree(tree);
        return re;
    };

    FEXP(t({}), true);
    FEXP(t({nullptr}), true);
    FEXP(t({1}), true);
    FEXP(t({1, 2}), true);
    FEXP(t({1, nullptr, 2}), true);
    FEXP(t({1, 2, 3}), true);
    FEXP(t({1, nullptr, 2, nullptr, 3}), false);
    FEXP(t({3, 9, 20, nullptr, nullptr, 15, 7}), true);
    FEXP(t({3, 9, 20, nullptr, nullptr, 15, 7}), true);
    FEXP(t({1, 2, 2, 3, 3, nullptr, nullptr, 4, 4}), false);
    FEXP(t({1, 2, 2, 3, nullptr, nullptr, 3, 4, nullptr, nullptr, 4}), false);
}

}