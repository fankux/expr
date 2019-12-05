#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 81. Search in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
You are given a target value to search. If found in the array return true, otherwise return false.

Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Follow up:
This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
Would this affect the run-time complexity? How and why?
*/
bool searchRotateII(std::vector<int>& nums, int target) {
    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        ssize_t mid = l + (h - l) / 2;
        if (nums[mid] == target) {
            return true;
        }
        if (nums[l] < nums[mid]) {
            if (nums[l] <= target && target < nums[mid]) { // left half sorted
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        } else if (nums[l] > nums[mid]) {
            if (nums[mid] < target && target <= nums[h]) { // right half sorted
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        } else {
            ++l;
        }
    }
    return false;
}

FTEST(test_searchRotateII) {
    auto t = [](const std::vector<int>& nums, int target) {
        std::vector<int> nns = nums;
        int n = searchRotateII(nns, target);
        LOG(INFO) << nums << " find " << target << ": " << n;
        return n;
    };

    FEXP(t({}, 1), false);
    FEXP(t({1}, 1), true);
    FEXP(t({1}, 2), false);
    FEXP(t({3, 1}, 1), true);
    FEXP(t({3, 1}, 3), true);
    FEXP(t({3, 1}, 2), false);
    FEXP(t({4, 5, 6, 7, 0, 1, 2}, 0), true);
    FEXP(t({4, 5, 6, 7, 0, 1, 2}, -3), false);
    FEXP(t({2, 5, 6, 0, 0, 1, 2}, 0), true);
    FEXP(t({2, 5, 6, 0, 0, 1, 2}, 3), false);
    FEXP(t({2, 5, 6, 1, 1, 1, 1}, 1), true);
    FEXP(t({2, 5, 6, 1, 1, 1, 1}, 2), true);
    FEXP(t({1, 3, 1, 1, 1}, 3), true);
    FEXP(t({1, 3, 1, 1, 1}, 1), true);
    FEXP(t({3, 3, 3, 1, 3}, 1), true);
    FEXP(t({3, 3, 3, 1, 3}, 3), true);
}


/**
 ///////////// 82. Remove Duplicates from Sorted List II
Given a sorted linked list, delete all nodes that have duplicate numbers,
 leaving only distinct numbers from the original list.

Example 1:
Input: 1->2->3->3->4->4->5
Output: 1->2->5

Example 2:
Input: 1->1->1->2->3
Output: 2->3
*/
ListNode* deleteDuplicatesII(ListNode* head) {
    ListNode* p = head;
    ListNode* prev = nullptr;
    while (p) {
        bool flag = false;
        while (p->next && p->val == p->next->val) {
            p->next = p->next->next;
            flag = true;
        }
        if (flag) {
            (prev ? prev->next : head) = p->next;
        } else {
            prev = p;
        }
        p = p->next;
    }
    return head;
}

FTEST(test_deleteDuplicatesII) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        print_list(list);
        ListNode* re = deleteDuplicatesII(list);
        LOG(INFO) << "delete duplica:";
        print_list(re);
    };

    t({});
    t({1});
    t({1, 1});
    t({1, 1, 1});
    t({1, 2});
    t({1, 1, 2});
    t({1, 2, 2});
    t({1, 1, 1, 2});
    t({1, 2, 2, 2});
    t({1, 1, 2, 2});
    t({1, 1, 1, 2, 2, 2});
    t({1, 1, 2, 3, 3});
    t({1, 1, 1, 2, 3, 3, 3});
}

/**
 ///////////// 83. Remove Duplicates from Sorted List
Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:
Input: 1->1->2
Output: 1->2

Example 2:
Input: 1->1->2->3->3
Output: 1->2->3
*/
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* p = head;
    while (p && p->next) {
        if (p->val == p->next->val) {
            p->next = p->next->next;
        } else {
            p = p->next;
        }
    }
    return head;
}

FTEST(test_deleteDuplicates) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        print_list(list);
        ListNode* re = deleteDuplicates(list);
        LOG(INFO) << "delete duplica:";
        print_list(re);
    };

    t({});
    t({1});
    t({1, 1});
    t({1, 1, 1});
    t({1, 2});
    t({1, 1, 2});
    t({1, 2, 2});
    t({1, 1, 1, 2});
    t({1, 2, 2, 2});
    t({1, 1, 2, 2});
    t({1, 1, 1, 2, 2, 2});
    t({1, 1, 2, 3, 3});
    t({1, 1, 1, 2, 3, 3, 3});
}

/**
 ///////////// 84. Largest Rectangle in Histogram
Given n non-negative integers representing the histogram's bar height
 where the width of each bar is 1, find the area of largest rectangle in the histogram.

                6
            5  ____
           ___|   |
          |   |   |     3
    2     |   |   | 2  ____
   ____ 1 |   |   |___|   |
  |   |___|   |   |   |   |
  |__ |__ |___|___|___|___|

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

                 6
            5  ____
           ___|___|
          |xxxxxxx|     3
    2     |xxxxxxx| 2  ____
   ____ 1 |xxxxxxx|___|   |
  |   |___|xxxxxxx|   |   |
  |__ |__ |xxxxxxx|___|___|

The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:
Input: [2,1,5,6,2,3]
Output: 10
*/
#ifdef VERBOSE
#define VERBOSE_FLAG
#undef VERBOSE
#endif

int largestRectangleArea(std::vector<int>& heights
#ifdef VERBOSE
        , std::pair<int, int>& idexs
#endif
) {
    heights.emplace_back(0);
    int res = 0;
    std::stack<int> ss;
    for (int i = 0; i < heights.size();) {
        if (ss.empty() || heights[i] >= heights[ss.top()]) {
            ss.push(i++);
        } else {
            int idx = ss.top();
            ss.pop();
            int sum = (ss.empty() ? i : (i - ss.top() - 1)) * heights[idx];
#ifdef VERBOSE
            if (sum > res) {
                res = sum;
                idexs.first = ss.empty() ? 0 : ss.top() + 1;
                idexs.second = i - 1;
            }
#else
            res = std::max(res, sum);
#endif
        }
    }
    return res;
}

FTEST(test_largestRectangleArea) {
    auto t = [](const std::vector<int>& heights) {
        std::vector<int> nns = heights;
#ifdef VERBOSE
        std::pair<int, int> idexs;
        auto re = largestRectangleArea(nns, idexs);
        LOG(INFO) << heights << " largest reactangle size: " << re << idexs;
#else
        auto re = largestRectangleArea(nns);
        LOG(INFO) << heights << " largest reactangle size: " << re;
#endif
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({0}), 0);
    FEXP(t({1}), 1);
    FEXP(t({0, 1}), 1);
    FEXP(t({1, 0}), 1);
    FEXP(t({1, 2}), 2);
    FEXP(t({2, 1}), 2);
    FEXP(t({1, 1}), 2);
    FEXP(t({2, 2}), 4);
    FEXP(t({1, 2, 3}), 4);
    FEXP(t({2, 1, 2}), 3);
    FEXP(t({1, 2, 3, 3}), 6);
    FEXP(t({1, 2, 3, 2}), 6);
    FEXP(t({1, 2, 3, 1}), 4);
    FEXP(t({1, 2, 3, 1, 1}), 5);
    FEXP(t({2, 1, 5, 6, 2, 3}), 10);
}

/**
 ///////////// 85. Maximal Rectangle
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
 containing only 1's and return its area.

Example:
Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
*/
int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    int res = 0;
    if (matrix.empty() || matrix.front().empty()) {
        return res;
    }
    size_t m = matrix.front().size();
    size_t n = matrix.size();
    std::vector<int> heights(m, 0);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            heights[j] = matrix[i][j] == '0' ? 0 : heights[j] + 1;
        }
        res = std::max(res, largestRectangleArea(heights));
    }
    return res;
}

FTEST(test_maximalRectangle) {
    auto t = [](const std::vector<std::vector<char>>& matrix) {
        std::vector<std::vector<char>> nns = matrix;
#ifdef VERBOSE
        std::pair<int, int> idexs;
        auto re = maximalRectangle(nns);
        LOG(INFO) << heights << " largest reactangle size: " << re << idexs;
#else
        auto re = maximalRectangle(nns);
        LOG(INFO) << matrix << " largest reactangle size: " << re;
#endif
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({{}}), 0);
    FEXP(t({{'0'}}), 0);
    FEXP(t({{'1'}}), 1);
    FEXP(t({{'1', '1'}}), 2);
    FEXP(t({{'1'}, {'1'}}), 2);
    FEXP(t({{'0', '1'}}), 1);
    FEXP(t({{'1', '0'}}), 1);
    FEXP(t({{'0'}, {'1'}}), 1);
    FEXP(t({{'1'}, {'0'}}), 1);
    FEXP(t({{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'},
            {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}), 6);
}

#ifdef VERBOSE_FLAG
#define VERBOSE
#undef VERBOSE_FLAG
#endif

/**
 ///////////// 86. Partition List
Given a linked list and a value x, partition it such that all nodes less than x come
 before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
*/
ListNode* partitionLinkList(ListNode* head, int x) {
    ListNode* l = nullptr;
    ListNode* h = nullptr;
    ListNode* hhead = nullptr;
    ListNode* p = head;
    while (p) {
        ListNode* q = p;
        p = p->next;
        if (q->val < x) {
            if (l == nullptr) {
                l = q;
                head = l;
            } else {
                l->next = q;
                l = l->next;
            }
            l->next = nullptr;
        } else {
            if (h == nullptr) {
                h = q;
                hhead = h;
            } else {
                h->next = q;
                h = h->next;
            }
            h->next = nullptr;
        }
    }
    if (head && l) {
        l->next = hhead;
    }
    return head ? head : hhead;
}

FTEST(test_partitionLinkList) {
    auto t = [](const std::vector<int>& nums, int x) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        print_list(list);
        ListNode* re = partitionLinkList(list, x);
        LOG(INFO) << "partition by " << x << ": ";
        print_list(re);
    };

    t({}, 0);
    t({0}, 0);
    t({1}, 0);
    t({0, 0}, 0);
    t({1, 1}, 0);
    t({0, 1}, 0);
    t({1, 0}, 0);
    t({0}, 1);
    t({1}, 1);
    t({0, 0}, 1);
    t({1, 1}, 1);
    t({0, 1}, 1);
    t({1, 0}, 1);
    t({0, 1, 2}, 0);
    t({0, 1, 2}, 1);
    t({0, 1, 2}, 2);
    t({3, 2, 1, 0}, 0);
    t({3, 2, 1, 0}, 1);
    t({3, 2, 1, 0}, 2);
    t({1, 4, 3, 2, 5, 2}, 3);
}


/**
 ///////////// 87. Scramble String
Given a string s1, we may represent it as a binary tree by partitioning it to
 two non-empty substrings recursively.
Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children,
 it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at",
 it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

Example 1:
Input: s1 = "great", s2 = "rgeat"
Output: true

Example 2:
Input: s1 = "abcde", s2 = "caebd"
Output: false
*/
bool isScramble(std::string s1, std::string s2) {
    return false;
}

/**
 ///////////// 88. Merge Sorted Array
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold
 additional elements from nums2.

Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
*/
void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
}

/**
 ///////////// 89. Gray Code
The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code,
 print the sequence of gray code. A gray code sequence must begin with 0.

Example 1:
Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2

For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.
00 - 0
10 - 2
11 - 3
01 - 1

Example 2:
Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
             Therefore, for n = 0 the gray code sequence is [0].
*/
std::vector<int> grayCode(int n) {
    return {};
}

/**
 ///////////// 90. Subsets II
Given a collection of integers that might contain duplicates, nums,
 return all possible subsets (the power set).
Note: The solution set must not contain duplicate subsets.

Example:
Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
    return {};
}
