#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex23 {

typedef LCListNode ListNode;

/**
 ///////////// 231.

 */


/**
 ///////////// 232.

 */


/**
 ///////////// 233.

 */


/**
 ///////////// 234. Palindrome Linked List
Given a singly linked list, determine if it is a palindrome.

Example 1:
Input: 1->2
Output: false

Example 2:
Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?
 */
bool isPalindromeLink(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    auto stack_method = [&] {
        std::stack<int> ss;
        ListNode* fast = head;
        while (fast && fast->next) {
            ss.emplace(head->val);
            head = head->next;
            fast = fast->next->next;
        }
        if (fast != nullptr) {      // link list number is odd, head current as middle
            head = head->next;
        }
        while (head) {
            if (head->val != ss.top()) {
                return false;
            }
            ss.pop();
            head = head->next;
        }
        return ss.empty();
    };
    auto reverse_method = [&] {
        ListNode* pre = nullptr;
        ListNode* n = nullptr;
        ListNode* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;

            n = head->next;
            head->next = pre;
            pre = head;
            head = n;
        }

        assert(pre != nullptr);
        if (fast != nullptr) {
            n = n->next;
        }
        while (n) {
            assert(pre != nullptr);
            if (n->val != pre->val) {
                return false;
            }
            n = n->next;
            pre = pre->next;
        }
        return true;
    };
    return reverse_method();
}

FTEST(test_isPalindromeLink) {
    auto t = [&](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        auto re = isPalindromeLink(list);
        LOG(INFO) << nums << "" << " is palindrome: " << re;
        return re;
    };

    FEXP(t({}), true);
    FEXP(t({1}), true);
    FEXP(t({1, 1}), true);
    FEXP(t({1, 2}), false);
    FEXP(t({1, 2, 2}), false);
    FEXP(t({1, 2, 1}), true);
    FEXP(t({1, 2, 2, 1}), true);
    FEXP(t({1, 2, 2, 3}), false);
    FEXP(t({1, 2, 2, 3, 4}), false);
    FEXP(t({1, 2, 3, 2, 1}), true);
}

/**
 ///////////// 235.

 */


/**
 ///////////// 236. Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
According to the definition of LCA on Wikipedia:
 “The lowest common ancestor is defined between two nodes p and q as the lowest node in T
 that has both p and q as descendants (where we allow a node to be a descendant of itself).”
Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

      3
     / \
    5   1
   / \ / \
  6  2 0 8
    / \
   7   4

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5,
 since a node can be a descendant of itself according to the LCA definition.

Note:
All of the nodes' values will be unique.
p and q are different and both values will exist in the binary tree.

 THOUGHTS:
    if root of p,q is p or q, once this happend, return p or q directly.

 */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root->val == p->val || root->val == q->val) {
        return root;
    }
    TreeNode* l = lowestCommonAncestor(root->left, p, q);
    if (l != nullptr && l->val != p->val && l->val != q->val) {
        return l;
    }
    TreeNode* r = lowestCommonAncestor(root->right, p, q);
    if (r != nullptr && r->val != p->val && r->val != q->val) {
        return r;
    }
    if (l != nullptr && r != nullptr) {
        return root;
    }
    return l ? l : r;
}

FTEST(test_lowestCommonAncestor) {
    auto t = [&](const std::vector<TreeNodeStub>& nums, int p, int q) {
        TreeNode* tree = create_tree(nums);
        TreeNode a(p);
        TreeNode b(q);
        auto re = lowestCommonAncestor(tree, &a, &b);
        LOG(INFO) << nums << " " << p << "," << q << " parent: " <<
                  (re == nullptr ? "null" : std::to_string(re->val));
        return re;
    };

    t({1, 2, 3}, 2, 3);
    t({1, 2, 3}, 2, 1);
    t({3, 5, 1, 6, 2, 0, 8, nullptr, nullptr, 7, 4}, 5, 1);
    t({3, 5, 1, 6, 2, 0, 8, nullptr, nullptr, 7, 4}, 5, 4);
}

/**
 ///////////// 237. Delete Node in a Linked List
Write a function to delete a node (except the tail) in a singly linked list,
 given only access to that node.
Given linked list -- head = [4,5,1,9], which looks like following:
    4 -> 5 -> 1 -> 9

Example 1:
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5,
 the linked list should become 4 -> 1 -> 9 after calling your function.

Example 2:
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1,
 the linked list should become 4 -> 5 -> 9 after calling your function.

Note:
The linked list will have at least two elements.
All of the nodes' values will be unique.
The given node will not be the tail and it will always be a valid node of the linked list.
Do not return anything from your function.
 */
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

/**
 ///////////// 238. Product of Array Except Self
Given an array nums of n integers where n > 1,
 return an array output such that output[i] is equal to the product of
 all the elements of nums except nums[i].

Example:
Input:  [1,2,3,4]
Output: [24,12,8,6]

Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity?
 (The output array does not count as extra space for the purpose of space complexity analysis.)
 */
std::vector<int> productExceptSelf(std::vector<int>& nums) {
    size_t len = nums.size();
    std::vector<int> res(len, 1);
    for (size_t i = 0; i < len; ++i) {
        res[len - i - 1] = i == 0 ? nums[len - i - 1] : res[len - i] * nums[len - i - 1];
    }
    int foward = 1;
    for (size_t i = 0; i < len; ++i) {
        res[i] = foward * (i == len - 1 ? 1 : res[i + 1]);
        foward *= nums[i];
    }
    return res;
}

FTEST(test_productExceptSelf) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = productExceptSelf(nns);
        LOG(INFO) << nums << "" << " product except self: " << re;
        return re;
    };

    t({1, 1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({4, 3, 2, 1});
    t({3, 4, 2, 1});
}

/**
 ///////////// 239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is moving
 from the very left of the array to the very right. You can only see the k numbers in the window.
 Each time the sliding window moves right by one position. Return the max sliding window.

Example:
Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Note:
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
 */
std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    return {};
}

/**
 ///////////// 240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix.
 This matrix has the following properties:
Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Example:
Consider the following matrix:
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.
Given target = 20, return false.
 */
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    return true;
}

}