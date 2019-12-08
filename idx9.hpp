#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:
Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
int numDecodings(std::string s) {
    if (s.empty() || s[0] == '0') {
        return 0;
    }
    std::function<int(size_t)> recursive_func;
    recursive_func = [&](size_t start) {
        if (start >= s.size()) {
            return 1;
        }
        if (s[start] == '0') {
            return 0;
        }
        int res = 0;
        if (start + 1 < s.size()) {
            int code = std::strtoul(s.substr(start, 2).c_str(), nullptr, 10);
            if (code > 0 && code <= 26) {
                res += recursive_func(start + 2);
            }
        }
        return res + recursive_func(start + 1);
    };
    auto dp_func = [&] {
        size_t len = s.size();
        std::vector<int> dp(len + 1, 0); // len+1 for end state handle
        dp[0] = 1;
        for (size_t i = 1; i < len + 1; ++i) {
            dp[i] = s[i - 1] == '0' ? 0 : dp[i - 1];
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] += dp[i - 2];
            }
        }
        return dp.back();
    };
    return dp_func();
}

FTEST(test_numDecodings) {
    auto t = [](const std::string& s) {
        auto re = numDecodings(s);
        LOG(INFO) << s << " decode ways: " << re;
        return re;
    };
    FEXP(t(""), 0);
    FEXP(t("01"), 0);
    FEXP(t("1"), 1);
    FEXP(t("10"), 1);
    FEXP(t("11"), 2);
    FEXP(t("20"), 1);
    FEXP(t("25"), 2);
    FEXP(t("26"), 2);
    FEXP(t("27"), 1);
    FEXP(t("225"), 3);
    FEXP(t("226"), 3);
    FEXP(t("227"), 2);
    FEXP(t("026"), 0);
    FEXP(t("206"), 1);
    FEXP(t("1226"), 5);
    FEXP(t("1227"), 3);
    FEXP(t("1787897759966261825913315262377298132516969578441236833255596967132573482281598412163216914566534565"),
            3);
}

/**
 ///////////// 92. Reverse Linked List II
Reverse a linked list from position m to n. Do it in one-pass.
Note: 1 ≤ m ≤ n ≤ length of list.

Example:
Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

THOUGHTS:
    1  → [2  →  3  →  4] →  5  →  NULL, m=2, n=4
    f     p                             i=1
       1 ↘   pre↘
 null  ← [2  ←  3  →  4] →  5  →  NULL
  pre     p   next
        pre ↘-→ p                       i=2
       1 ↘
 null  ← [2  ←  3  ←  4] →  5  →  NULL
         pre    p   next
              pre ↘-→ p                 i=3
 null  ← [2  ←  3  ←  4] →  5  →  NULL
               pre    p   next
                    pre ↘-→ p           i=4
    1  → [4  →  3  →  2] →  5  →  NULL
    f     pre               p

 reverse from head:
   [4  →  3  →  2  →  1] →  5  →  NULL
 f  pre             head    p

 reverse all:
   [1  ←  2  ←  3  ←  4  →  5] →  NULL
                     pre    p   next
                          pre ↘-→ p     i=5
   [5  →  4  →  3  →  2  →  1] →  NULL
 f  p               pre   head    next

*/
ListNode* reverseBetween(ListNode* head, int m, int n) {
    int i = 1;
    ListNode* p = head;
    ListNode* pre = nullptr;
    while (p && i < m) {
        pre = p;
        p = p->next;
        ++i;
    }
    while (p && p->next && i < n) {
        ListNode* next = p->next;
        p->next = next->next;
        next->next = (pre ? pre->next : head);
        (pre ? pre->next : head) = next;
        ++i;
    }
    return head;
}

FTEST(test_reverseBetween) {
    auto t = [](const std::vector<int>& nums, int m, int n) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        ListNode* re = reverseBetween(list, m, n);
        LOG(INFO) << nums << " reverse between " << m << ", " << n << ": ";
        print_list(re);
    };

    t({}, 0, 0);
    t({1}, 0, 1);
    t({1}, 1, 1);
    t({1, 2}, 1, 1);
    t({1, 2}, 2, 2);
    t({1, 2}, 1, 2);
    t({1, 2, 3}, 1, 1);
    t({1, 2, 3}, 2, 2);
    t({1, 2, 3}, 3, 3);
    t({1, 2, 3}, 1, 2);
    t({1, 2, 3}, 2, 3);
    t({1, 2, 3}, 1, 3);
    t({1, 2, 3, 4}, 1, 2);
    t({1, 2, 3, 4}, 2, 3);
    t({1, 2, 3, 4}, 1, 3);
    t({1, 2, 3, 4, 5}, 1, 2);
    t({1, 2, 3, 4, 5}, 2, 3);
    t({1, 2, 3, 4, 5}, 1, 3);
}

/**
 ///////////// 93. Restore IP Addresses
Given a string containing only digits,
 restore it by returning all possible valid IP address combinations.

Example:
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
*/
std::vector<std::string> restoreIpAddresses(std::string s) {
    return {};
}

/**
 ///////////// 94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

Example:
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
Follow up: Recursive solution is trivial, could you do it iteratively?
*/
std::vector<int> inorderTraversal(TreeNode* root) {
    return {};
}

/**
 ///////////// 95. Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees) that
 store values 1 ... n.

Example:
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
std::vector<TreeNode*> generateTrees(int n) {
    return {};
}

/**
 ///////////// 96. Unique Binary Search Trees
Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:
Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
int numTrees(int n) {
    return 0;
}

/**
 ///////////// 97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
*/
bool isInterleave(std::string s1, std::string s2, std::string s3) {
    return false;
}

/**
 ///////////// 98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
    2
   / \
  1   3
Input: [2,1,3]
Output: true

Example 2:
    5
   / \
  1   4
     / \
    3   6
Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/
bool isValidBST(TreeNode* root) {
    return false;
}

/**
 ///////////// 99. Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

Example 1:
Input: [1,3,null,null,2]
   1
  /
 3
  \
   2
Output: [3,1,null,null,2]
   3
  /
 1
  \
   2

Example 2:
Input: [3,1,4,null,null,2]
  3
 / \
1   4
   /
  2
Output: [2,1,4,null,null,3]
  2
 / \
1   4
   /
  3

Follow up:
A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
*/
void recoverTree(TreeNode* root) {
}

/**
 ///////////// 100. Same Tree
Given two binary trees, write a function to check if they are the same or not.
Two binary trees are considered the same if they are
 structurally identical and the nodes have the same value.

Example 1:
Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]
Output: true

Example 2:
Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]
Output: false

Example 3:
Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]
Output: false
*/
bool isSameTree(TreeNode* p, TreeNode* q) {
    return false;
}
