#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex15 {

/**
 ///////////// 151. Reverse Words in a String
Given an input string, reverse the string word by word.

Example 1:
Input: "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

Note:
A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces.
 However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.

Follow up:
For C programmers, try to solve it in-place in O(1) extra space.
 */
std::string reverseWords(std::string s) {
    return "";
}

/**
 ///////////// 152. Maximum Product Subarray
Given an integer array nums, find the contiguous subarray within an array
 (containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */
int maxProduct(std::vector<int>& nums) {
    return 0;
}

/**
 ///////////// 153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
Find the minimum element.
You may assume no duplicate exists in the array.

Example 1:
Input: [3,4,5,1,2]
Output: 1

Example 2:
Input: [4,5,6,7,0,1,2]
Output: 0
 */
int findMinRotate(std::vector<int>& nums) {
    return 0;
}

/**
 ///////////// 154. Find Minimum in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
Find the minimum element.
The array may contain duplicates.

Example 1:
Input: [1,3,5]
Output: 1

Example 2:
Input: [2,2,2,0,1]
Output: 0

Note:
This is a follow up problem to Find Minimum in Rotated Sorted Array.
Would allow duplicates affect the run-time complexity? How and why?
 */
int findMinRotateII(std::vector<int>& nums) {
    return 0;
}

/**
 ///////////// 155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }

    void push(int x) {
    }

    void pop() {
    }

    int top() {
    }

    int getMin() {
    }
};

/**
 ///////////// 156. Binary Tree Upside Down
Given a binary tree where all the right nodes are either leaf nodes with a sibling
 (a left node that shares the same parent node) or empty,
 flip it upside down and turn it into a tree where the original
 right nodes turned into left leaf nodes. Return the new root.

Example:
Input: [1,2,3,4,5]
    1
   / \
  2   3
 / \
4   5

Output: return the root of the binary tree [4,5,2,#,#,3,1]
   4
  / \
 5   2
    / \
   3   1
Clarification:
Confused what [4,5,2,#,#,3,1] means? Read more below on how binary tree is serialized on OJ.

The serialization of a binary tree follows a level order traversal,
 where '#' signifies a path terminator where no node exists below.

Here's an example:
   1
  / \
 2   3
    /
   4
    \
     5
The above binary tree is serialized as [1,2,3,#,#,4,#,#,5].
 */
TreeNode* upsideDownBinaryTree(TreeNode* root) {
    return nullptr;
}

/**
 ///////////// 157. Read N Characters Given Read4
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example,
 it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n)
 that reads n characters from the file.
Note:
The read function will only be called once for each test case.
 */
int readNChar(char* buf, int n) {
    return 0;
}

/**
 ///////////// 158. Read N Characters Given Read4 II - Call multiple times
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example,
 it returns 3 if there is only 3 characters left in the file.

By using the read4 API,
 implement the function int read(char *buf, int n) that reads n characters from the file.
Note:
The read function may be called multiple times.
 */
int readNCharII(char* buf, int n) {
    return 0;
}

/**
 ///////////// 159. Longest Substring with At Most Two Distinct Characters
Given a string s , find the length of the longest substring t
 that contains at most 2 distinct characters.

Example 1:
Input: "eceba"
Output: 3
Explanation: tis "ece" which its length is 3.

Example 2:
Input: "ccaabbb"
Output: 5
Explanation: tis "aabbb" which its length is 5.
 */
int lengthOfLongestSubstringTwoDistinct(std::string s) {
    return 0;
}

/**
 ///////////// 160. Intersection of Two Linked Lists
Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:
TODO.. graph

begin to intersect at node c1.

Example 1:
TODO.. graph

Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
Output: Reference of the node with value = 8
Input Explanation: The intersected node's value is 8
 (note that this must not be 0 if the two lists intersect).
 From the head of A, it reads as [4,1,8,4,5]. From the head of B,
 it reads as [5,0,1,8,4,5]. There are 2 nodes before the intersected node in A;
 There are 3 nodes before the intersected node in B.

Example 2:
TODO.. graph

Input: intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Reference of the node with value = 2
Input Explanation: The intersected node's value is 2
 (note that this must not be 0 if the two lists intersect).
 From the head of A, it reads as [0,9,1,2,4]. From the head of B,
 it reads as [3,2,4]. There are 3 nodes before the intersected node in A;
 There are 1 node before the intersected node in B.


Example 3:
TODO.. graph

Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: null
Input Explanation: From the head of A, it reads as [2,6,4].
 From the head of B, it reads as [1,5]. Since the two lists do not intersect,
 intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.

Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
 */
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    return nullptr;
}

}