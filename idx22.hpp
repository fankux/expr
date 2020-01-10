#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex22 {

/**
 ///////////// 221. Maximal Square
Given a 2D binary matrix filled with 0's and 1's,
 find the largest square containing only 1's and return its area.

Example:
Input:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
 */
int maximalSquare(std::vector<std::vector<char>>& matrix) {
    return 0;
}

/**
 ///////////// 222. Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Note:
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled,
 and all nodes in the last level are as far left as possible.
 It can have between 1 and 2h nodes inclusive at the last level h.

Example:
Input:
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
 */
int countNodes(TreeNode* root) {
    return 0;
}

/**
 ///////////// 223. Rectangle Area
Find the total area covered by two rectilinear rectangles in a 2D plane.
Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
TODO... figure
Rectangle Area

Example:
Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
Output: 45

Note:
Assume that the total area is never beyond the maximum possible value of int.
 */
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    return 0;
}

/**
 ///////////// 224. Basic Calculator
Implement a basic calculator to evaluate a simple expression string.
The expression string may contain open ( and closing parentheses ),
 the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:
Input: "1 + 1"
Output: 2

Example 2:
Input: " 2-1 + 2 "
Output: 3

Example 3:
Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23

Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
 */
int basicCalculator(std::string s) {
    return 0;
}

/**
 ///////////// 225. Implement Stack using Queues
Implement the following operations of a stack using queues.
 - push(x) -- Push element x onto stack.
 - pop() -- Removes the element on top of the stack.
 - top() -- Get the top element.
 - empty() -- Return whether the stack is empty.

Example:
MyStack stack = new MyStack();
stack.push(1);
stack.push(2);
stack.top();   // returns 2
stack.pop();   // returns 2
stack.empty(); // returns false

Notes:
You must use only standard operations of a queue -- which means only push to back,
 peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively.
 You may simulate a queue by using a list or deque (double-ended queue),
 as long as you use only standard operations of a queue.
You may assume that all operations are valid
 (for example, no pop or top operations will be called on an empty stack).
 **
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
    }

    /** Push element x onto stack. */
    void push(int x) {
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        return 0;
    }

    /** Get the top element. */
    int top() {
        return 0;
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return true;
    }
};

/**
 ///////////// 226. Invert Binary Tree
Invert a binary tree.

Example:
Input:
     4
   /   \
  2     7
 / \   / \
1   3 6   9

Output:
     4
   /   \
  7     2
 / \   / \
9   6 3   1

Trivia:
This problem was inspired by this original tweet by Max Howell:
Google: 90% of our engineers use the software you wrote (Homebrew),
 but you can’t invert a binary tree on a whiteboard so f*** off.
 */
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
        return root;
    }
    std::swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

FTEST(test_invertTree) {
    auto t = [&](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        LOG(INFO) << "\n" << print_tree(tree);
        auto re = invertTree(tree);
        LOG(INFO) << "reverse:\n " << print_tree(tree);
        return re;
    };

    t({1});
    t({1, 2});
    t({1, nullptr, 2});
    t({1, 2, nullptr});
    t({1, 2, 3});
    t({4, 2, 7, 1, 3, 6, 9});
}

/**
 ///////////// 227. Basic Calculator II
Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces .
 The integer division should truncate toward zero.

Example 1:
Input: "3+2*2"
Output: 7

Example 2:
Input: " 3/2 "
Output: 1

Example 3:
Input: " 3+5 / 2 "
Output: 5

Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
 */
int basicCalculatorII(std::string s) {
    std::stack<int> ss;
    char last_op = '+';
    int num = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        }
        if ((!isspace(c) && !isdigit(c)) || i == s.size() - 1) {
            if (last_op == '+') {
                ss.push(num);
            } else if (last_op == '-') {
                ss.push(-num);
            } else if (last_op == '*' || last_op == '/') {
                ss.top() = last_op == '*' ? ss.top() * num : ss.top() / num;
            }
            last_op = c;
            num = 0;
        }
    }
    int res = 0;
    while (!ss.empty()) {
        res += ss.top();
        ss.pop();
    }
    return res;
}

FTEST(test_basicCalculatorII) {
    auto t = [&](const std::string& expr) {
        auto re = basicCalculatorII(expr);
        LOG(INFO) << expr << " = " << re;
        return re;
    };

    FEXP(t("1+1"), 1 + 1);
    FEXP(t("1+2"), 1 + 2);
    FEXP(t("3+2*2"), 3 + 2 * 2);
    FEXP(t("3/2"), 3 / 2);
    FEXP(t(" 3+5 / 2 "), 3 + 5 / 2);
}

/**
 ///////////// 228. Summary Ranges
Given a sorted integer array without duplicates, return the summary of its ranges.

Example 1:
Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.

Example 2:
Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
 */
std::vector<std::string> summaryRanges(std::vector<int>& nums) {
    return {};
}

/**
 ///////////// 229. Majority Element II
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
Note: The algorithm should run in linear time and in O(1) space.

Example 1:
Input: [3,2,3]
Output: [3]

Example 2:
Input: [1,1,1,3,3,2,2,2]
Output: [1,2]
 */
std::vector<int> majorityElementII(std::vector<int>& nums) {
    return {};
}

/**
 ///////////// 230. Kth Smallest Element in a BST
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Example 1:
Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

Follow up:
What if the BST is modified (insert/delete operations) often and you need to
 find the kth smallest frequently? How would you optimize the kthSmallest routine?
 */
int kthSmallestTree(TreeNode* root, int k) {
    int count = 0;
    auto morris_method = [&] {
        int res = -1;
        while (root) {
            if (root->left == nullptr) {
                if (++count == k) {
                    res = root->val;
                }
                root = root->right;
                continue;
            }
            TreeNode* pre = root->left;
            while (pre->right && pre->right != root) {
                pre = pre->right;
            }
            if (pre->right == nullptr) {
                pre->right = root;
                root = root->left;
            } else { // p->right == root
                pre->right = nullptr;
                if (++count == k) {
                    res = root->val;
                }
                root = root->right; // back to parent
            }
        }
        return res;
    };
    auto stack_method = [&] {
        std::stack<TreeNode*> ss;
        while (root || !ss.empty()) {
            if (root != nullptr) {
                ss.emplace(root);
                root = root->left;
            } else {
                assert(!ss.empty());
                root = ss.top();
                ss.pop();

                if (++count >= k) {
                    return root->val;
                }
                root = root->right;
            }
        }
        return -1;
    };
    return stack_method();
}

FTEST(test_kthSmallestTree) {
    auto t = [&](const std::vector<TreeNodeStub>& nums, int k) {
        TreeNode* tree = create_tree(nums);
        auto re = kthSmallestTree(tree, k);
        LOG(INFO) << nums << " " << k << "th smallest: " << re;
        return re;
    };

    FEXP(t({}, 0), -1);
    FEXP(t({}, 1), -1);
    FEXP(t({1}, 1), 1);
    FEXP(t({2, 1, 3}, 1), 1);
    FEXP(t({2, 1, 3}, 2), 2);
    FEXP(t({2, 1, 3}, 3), 3);
    FEXP(t({1, nullptr, 2}, 1), 1);
    FEXP(t({1, nullptr, 2}, 2), 2);
    FEXP(t({3, 1, 4, nullptr, 2}, 1), 1);
    FEXP(t({5, 3, 6, 2, 4, nullptr, nullptr, 1}, 3), 3);
}

}