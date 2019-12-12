#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;
typedef LCNode Node;

/**
 ///////////// 111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the
 root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.
*/
int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr) {
        return minDepth(root->right) + 1;
    } // avoid mid node without left to be calculated
    if (root->right == nullptr) {
        return minDepth(root->left) + 1;
    } // avoid mid node without right to be calculated
    return std::min(minDepth(root->left), minDepth(root->right)) + 1;
}

FTEST(test_minDepth) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = minDepth(tree);
        LOG(INFO) << nodes << " min tree depth: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({nullptr}), 0);
    FEXP(t({1}), 1);
    FEXP(t({1, 2}), 2);
    FEXP(t({1, nullptr, 2}), 2);
    FEXP(t({1, nullptr, 2}), 2);
    FEXP(t({3, 9, 20, nullptr, nullptr, 15, 7}), 2);
}

/**
 ///////////// 112. Path Sum
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that
 adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/
bool hasPathSum(TreeNode* root, int sum) {
    auto r_func = [&] {
        if (root == nullptr) {
            return false;
        }
        if (root->left == nullptr && root->right == nullptr && root->val == sum) {
            return true;
        }
        sum -= root->val;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    };
    auto iter_func = [&] {
        std::stack<std::pair<TreeNode*, int>> ss;
        while (root || !ss.empty()) {
            while (root) {
                ss.emplace(root, sum);
                sum -= root->val;
                root = root->left;
            }

            root = ss.top().first;
            sum = ss.top().second;
            ss.pop();

            if (root->left == nullptr && root->right == nullptr && root->val == sum) {
                return true;
            }
            sum -= root->val;
            root = root->right;
        }
        return false;
    };
    return iter_func();
}

FTEST(test_hasPathSum) {
    auto t = [](const std::vector<TreeNodeStub>& nodes, int sum) {
        TreeNode* tree = create_tree(nodes);
        auto re = hasPathSum(tree, sum);
        LOG(INFO) << nodes << " has sum " << sum << ": " << re;
        return re;
    };

    FEXP(t({}, 0), false);
    FEXP(t({}, 1), false);
    FEXP(t({nullptr}, 1), false);
    FEXP(t({1}, 1), true);
    FEXP(t({1}, 2), false);
    FEXP(t({1, 2}, 1), false);
    FEXP(t({1, 2}, 3), true);
    FEXP(t({1, nullptr, 2}, 2), false);
    FEXP(t({1, nullptr, 2}, 3), true);
    FEXP(t({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1}, 27), true);
    FEXP(t({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1}, 22), true);
    FEXP(t({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1}, 26), true);
    FEXP(t({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1}, 18), true);
    FEXP(t({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1}, 17), false);
}

/**
 ///////////// 113. Path Sum II
Given a binary tree and a sum,
 find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1

Return:
[
   [5,4,11,2],
   [5,8,4,5]
]
*/
std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) {
    return {};
}

/**
 ///////////// 114. Flatten Binary Tree to Linked List
Given a binary tree, flatten it to a linked list in-place.
For example, given the following tree:
    1
   / \
  2   5
 / \   \
3   4   6

The flattened tree should look like:
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
THOUGHTS:
 rotate right at first node
    1          1         1
   / \          \         \
  2   5          2         2
 / \   \  ->   /  \    ->   \
3   4   6     3    5         3
               \    \         \
                4    6         4
                                \
                                 5
                                  \
                                   6
*/
void flattenBinaryTree(TreeNode* root) {
    while (root) {
        TreeNode* left = root->left;
        TreeNode* p = left;
        while (p && p->right) {
            p = p->right;
        }
        if (p) {
            p->right = root->right;
            root->right = left;
            root->left = nullptr;
        }
        root = root->right;
    }
}

FTEST(test_flattenBinaryTree) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        flattenBinaryTree(tree);
        LOG(INFO) << nodes << " flatten: \n" << print_tree(tree, 100);
    };

    t({});
    t({nullptr});
    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, 2, 3});
    t({1, nullptr, 2, nullptr, 3});
    t({3, 9, 20, nullptr, nullptr, 15, 7});
    t({1, 2, 3, 4, 5, 6, 7});
    t({1, 2, 5, 3, 4, nullptr, 6});
}

/**
 ///////////// 115. Distinct Subsequences
Given a string S and a string T, count the number of distinct subsequences of S which equals T.
A subsequence of a string is a new string which is formed from the original string by deleting
 some (can be none) of the characters without disturbing the relative positions of the remaining
 characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Example 1:
Input: S = "rabbbit", T = "rabbit"
Output: 3

Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

 rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

Example 2:
Input: S = "babgbag", T = "bag"
Output: 5

Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
*/
int numDistinct(std::string s, std::string t) {
    return 0;
}

/**
 ///////////// 116. Populating Next Right Pointers in Each Node
You are given a perfect binary tree where all leaves are on the same level,
 and every parent has two children. The binary tree has the following definition:
```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```
Populate each next pointer to point to its next right node.
 If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.

Follow up:
You may only use constant extra space.Recursive approach is fine,
 you may assume implicit stack space does not count as extra space for this problem.

Example 1:
     1                     1 → NULL
   /  \                  /  \
  2    3                2 -→ 3 → NULL
 / \  / \              / \  / \
4  5 6   7            4 →5→6 → 7 → NULL

Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A),
 your function should populate each next pointer to point to its next right node,
 just like in Figure B. The serialized output is in level order as connected by the next pointers,
 with '#' signifying the end of each level.

Constraints:
The number of nodes in the given tree is less than 4096.
-1000 <= node.val <= 1000

*/
Node* connectBinaryTree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    auto r_func = [&] {
        if (root->left) {
            root->left->next = root->right;
        }
        if (root->right) {
            root->right->next = root->next ? root->next->left : nullptr;
        }
        connectBinaryTree(root->left);
        connectBinaryTree(root->right);
    };
    auto iter_func = [&] {
        Node* p = root;
        while (p->left) {
            Node* start = p->left;
            while (p) {
                p->left->next = p->right;
                p->right->next = p->next ? p->next->left : nullptr;
                p = p->next;
            }
            p = start;
        }
    };
    iter_func();
    return root;
}

FTEST(test_connectBinaryTree) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        Node* tree = create_tree<Node>(nodes);
        auto re = connectBinaryTree(tree);
        LOG(INFO) << nodes << " connect: \n" << print_tree(re);
        return re;
    };

    t({});
    t({1});
    t({1, 2, 3});
    t({1, 2, 3, 4, 5, 6, 7});
}

/**
 ///////////// 117. Populating Next Right Pointers in Each Node II
Given a binary tree
```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```
Populate each next pointer to point to its next right node. If there is no next right node,
 the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.

Follow up:
You may only use constant extra space. Recursive approach is fine,
 you may assume implicit stack space does not count as extra space for this problem.

Example 1:
     1                     1 → NULL
   /  \                  /  \
  2    3                2 -→ 3 → NULL
 / \    \              / \    \
4  5     7            4 →5 --→ 7 → NULL

Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A),
 your function should populate each next pointer to point to its next right node,
 just like in Figure B. The serialized output is in level order as connected by the next pointers,
 with '#' signifying the end of each level.

Constraints:
The number of nodes in the given tree is less than 6000.
-100 <= node.val <= 100
*/
Node* connectBinaryTreeII(Node* root) {
    return nullptr;
}

/**
 ///////////// 118. Pascal's Triangle
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:
Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
std::vector<std::vector<int>> pascalGenerate(int numRows) {
    std::vector<std::vector<int>> res;
    for (int i = 0; i < numRows; ++i) {
        std::vector<int> line(i + 1, 0);
        line[0] = 1;
        line[i] = 1;
        for (int j = 1; j < i; ++j) {
            line[j] = res.back()[j - 1] + res.back()[j];
        }
        res.emplace_back(line);
    }
    return res;
}

FTEST(test_pascalGenerate) {
    auto t = [](int numRows) {
        auto re = pascalGenerate(numRows);
        LOG(INFO) << numRows << " pascal: \n" << re;
        return re;
    };

    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
    t(5);
}

/**
 ///////////// 119. Pascal's Triangle II
Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
Note that the row index starts from 0.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:
Input: 3
Output: [1,3,3,1]

Follow up:
Could you optimize your algorithm to use only O(k) extra space?
*/
std::vector<int> PascalGetRow(int rowIndex) {
    return {};
}

/**
 ///////////// 120. Triangle
Given a triangle, find the minimum path sum from top to bottom.
 Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space,
 where n is the total number of rows in the triangle.
*/
int minimumTotal(std::vector<std::vector<int>>& triangle) {
    return 0;
}
