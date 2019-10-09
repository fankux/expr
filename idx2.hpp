#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;

/**
 ///////////// 21. Merge Two Sorted Lists
 Merge two sorted linked lists and return it as a new list.
 The new list should be made by splicing together the nodes of the first two lists.

 Example:
 Input: 1->2->4, 1->3->4
 Output: 1->1->2->3->4->4
 */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* h = l1 != nullptr ? l1 : l2;
    ListNode* p = nullptr;
    ListNode* prev = nullptr;
    while (l1 && l2) {
        if (l1->val > l2->val) {
            p = l2;
            l2 = l2->next;
        } else {
            p = l1;
            l1 = l1->next;
        }
        if (prev != nullptr) {
            prev->next = p;
        } else {
            h = p;
        }
        prev = p;
    }
    if (prev) {
        prev->next = l1 == nullptr ? l2 : l1;
    }
    return h;
}

FTEST(test_mergeTwoLists) {
    auto t = [](const std::vector<int>& nums1, const std::vector<int>& nums2) {
        std::vector<int> n = nums1;
        std::sort(n.begin(), n.end());
        ListNode* l1 = list_convert_leetcode(create_list(n));
        n = nums2;
        std::sort(n.begin(), n.end());
        ListNode* l2 = list_convert_leetcode(create_list(n));
        LOG(INFO) << "merge two: ";
        print_list(l1);
        print_list(l2);
        print_list(mergeTwoLists(l1, l2));
    };

    t({}, {});
    t({1}, {});
    t({}, {1});
    t({1}, {1});
    t({2}, {1});
    t({1, 2, 4}, {1, 3, 4});
    t({2}, {1, 3, 4});
}

/**
 ///////////// 22. Generate Parentheses
 Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 For example, given n = 3, a solution set is:
 [
   "((()))",
   "(()())",
   "(())()",
   "()(())",
   "()()()"
 ]
 */
std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::string> res;
    std::function<void(int, int, std::string&)> rf;
    rf = [&rf, &res](int l, int r, std::string& s) {
        if (l > r) {
            return;
        }

        if (l == 0 && r == 0) {
            res.emplace_back(s);
            return;
        }

        if (l > 0) {
            s += '(';
            rf(l - 1, r, s);
            s.pop_back();
        }
        if (r > 0) {
            s += ')';
            rf(l, r - 1, s);
            s.pop_back();
        }
    };

    std::string s;
    rf(n, n, s);
    return res;
}

FTEST(test_generateParenthesis) {
    auto t = [](int n) {
        auto c = generateParenthesis(n);
        LOG(INFO) << n << " pair: " << c;
        return c;
    };

    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
}

/**
 ///////////// 23. Merge k Sorted Lists
 Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

 Example:
 Input:
 [
   1->4->5,
   1->3->4,
   2->6
 ]
 Output: 1->1->2->3->4->4->5->6
*/
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    size_t len = lists.size();
    while (len > 1) {
        size_t m_upper = (len + 1) / 2;
        size_t m_lower = len / 2;
        for (size_t i = 0; i < m_lower; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[i + m_upper]);
        }
        len = m_upper;
    }
    return lists.empty() ? nullptr : lists.front();
}

FTEST(test_mergeKLists) {
    auto t = [](const std::vector<std::vector<int>>& num_lists) {
        std::vector<ListNode*> lists;
        for (auto& nums : num_lists) {
            std::vector<int> n = nums;
            std::sort(n.begin(), n.end());
            lists.emplace_back(list_convert_leetcode(create_list(n)));
        }
        LOG(INFO) << "merge sorted lists: " << num_lists;
        print_list(mergeKLists(lists));
    };

    t({{}});
    t({{},
       {}});
    t({{0}});
    t({{0},
       {}});
    t({{0},
       {1}});
    t({{0, 1},
       {1, 2}});
    t({{0},
       {1},
       {}});
    t({{0, 5},
       {1, 3},
       {}});
    t({{0},
       {1},
       {2}});
    t({{0, 0},
       {1, 1},
       {2, 2}});
    t({{0},
       {1},
       {1, 2}});
    t({{0, 0},
       {1, 2},
       {1, 2, 3}});
    t({{0},
       {1, 2},
       {1, 2, 3}});
    t({{0, 5},
       {1, 2, 7},
       {1, 2, 3, 10}});
}

/**
 ///////////// 24. Swap Nodes in Pairs
 Given a linked list, swap every two adjacent nodes and return its head.
 You may not modify the values in the list's nodes, only nodes itself may be changed.

 Example:
 Given 1->2->3->4, you should return the list as 2->1->4->3.
       ^  ^
       |  |
       p  r
*/
ListNode* swapPairs(ListNode* head) {
    ListNode* p = head;
    head = head && head->next ? head->next : head;
    ListNode* prev = nullptr;
    ListNode* r;
    while (p && p->next) {
        r = p->next;
        if (prev != nullptr) {
            prev->next = r;
        }
        p->next = r->next;
        r->next = p;
        prev = p;
        p = p->next;
    }
    return head;
}

FTEST(test_swapPairs) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* l1 = list_convert_leetcode(create_list(nums));
        LOG(INFO) << "swapPairs two: " << nums;
        print_list(swapPairs(l1));
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({1, 2, 3, 4, 5});
    t({1, 2, 3, 4, 5, 6});
    t({1, 2, 3, 4, 5, 6, 7});
    t({1, 2, 3, 4, 5, 6, 7, 8});
}

/**
 ///////////// 25. Reverse Nodes in k-Group
 Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
 k is a positive integer and is less than or equal to the length of the linked list.
 If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

 Example:
 Given this linked list: 1->2->3->4->5

 For k = 2, you should return: 2->1->4->3->5
 For k = 3, you should return: 3->2->1->4->5

 Note:
 Only constant extra memory is allowed.
 You may not alter the values in the list's nodes, only nodes itself may be changed.
 */
ListNode* reverseKGroup(ListNode* head, int k) {
    if (k <= 1) {
        return head;
    }
    ListNode* h = nullptr;
    ListNode* pre = nullptr;
    while (head) {
        ListNode* t = head;
        ListNode* p = nullptr;
        int i = 0;
        while (head && i < k) {
            ListNode* next = head->next;
            head->next = p;
            p = head;
            head = next;
            ++i;
        }
        if (i < k) {
            t = reverseKGroup(p, i);
            if (pre) {
                pre->next = t;
            }
            return h ? h : t;
        }
        if (h == nullptr) {
            h = p;
        }
        if (pre) {
            pre->next = p;
        }
        pre = t;
    }
    return h;
}

FTEST(test_reverseKGroup) {
    auto t = [](const std::vector<int>& nums, int k) {
        ListNode* l1 = list_convert_leetcode(create_list(nums));
        LOG(INFO) << "swap " << k << ": " << nums;
        print_list(reverseKGroup(l1, k));
    };

//    t({}, 0);
//    t({}, 1);
//    t({}, 2);
    t({1}, 0);
    t({1}, 1);
    t({1}, 2);
    t({1, 2}, 0);
    t({1, 2}, 1);
    t({1, 2}, 2);
    t({1, 2}, 3);

    t({1, 2, 3, 4, 5, 6, 7, 8}, 0);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 1);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 2);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 3);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 4);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 5);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 6);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 7);
    t({1, 2, 3, 4, 5, 6, 7, 8}, 8);
}

/**
 ///////////// 26. Remove Duplicates from Sorted Array
 Given a sorted array nums, remove the duplicates in-place such that each element appear
 only once and return the new length.
 Do not allocate extra space for another array, you must do this by modifying the
 input array in-place with O(1) extra memory.

 Example 1:
 Given nums = [1,1,2],

 Your function should return length = 2, with the first two elements of
 nums being 1 and 2 respectively.
 It doesn't matter what you leave beyond the returned length.

 Example 2:
 Given nums = [0,0,1,1,1,2,2,3,3,4],
 Your function should return length = 5, with the first five elements of nums being
 modified to 0, 1, 2, 3, and 4 respectively.
 It doesn't matter what values are set beyond the returned length.

 Clarification:
 Confused why the returned value is an integer but your answer is an array?
 Note that the input array is passed in by reference, which means modification
 to the input array will be known to the caller as well.

 Internally you can think of this:

 // nums is passed in by reference. (i.e., without making a copy)
 int len = removeDuplicates(nums);

 // any modification to nums in your function would be known by the caller.
 // using the length returned by your function, it prints the first len elements.
 for (int i = 0; i < len; i++) {
     print(nums[i]);
 }
 */
int removeDuplicates(std::vector<int>& nums) {
    bool swap = false;
    size_t len = nums.size();
    int start = 0;
    for (int i = 1; start < len && i < len;) {
        if (start == i) {
            ++i;
        } else if (nums[start] == nums[i]) {
            while (i < len && nums[start] == nums[i]) {
                ++i;
            }
            if (i < len) {
                nums[start + 1] = nums[i];
            }
            swap = true;
            ++start;
        } else {
            ++start;
            ++i;
        }
    }
    return swap ? start : len;
}

FTEST(test_removeDuplicates) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> n = nums;
        int len = removeDuplicates(n);
        std::stringstream ss;
        for (int i = 0; i < len; ++i) {
            ss << n[i] << ",";
        }
        LOG(INFO) << "remove duplicates: " << nums << ", result: " << ss.str();
    };

//    t({});
    t({1});
    t({1, 1});
    t({1, 2});
    t({1, 1, 2, 2});
    t({1, 2, 3});
    t({1, 1, 2, 2, 3, 3});
    t({1, 1, 2, 2, 3, 3, 4});
    t({1, 2, 3, 4, 5, 6, 7});
}

/**
 ///////////// 27. Remove Element
 Given an array nums and a value val, remove all instances of that value in-place
 and return the new length.
 Do not allocate extra space for another array, you must do this by modifying
 the input array in-place with O(1) extra memory.
 The order of elements can be changed. It doesn't matter what you leave beyond the new length.

 Example 1:
 Given nums = [3,2,2,3], val = 3,

 Your function should return length = 2, with the first two elements of nums being 2.
 It doesn't matter what you leave beyond the returned length.

 Example 2:
 Given nums = [0,1,2,2,3,0,4,2], val = 2,
 Your function should return length = 5, with the first five elements of nums
 containing 0, 1, 3, 0, and 4.

 Note that the order of those five elements can be arbitrary.
 It doesn't matter what values are set beyond the returned length.

 Clarification:
 Confused why the returned value is an integer but your answer is an array?
 Note that the input array is passed in by reference, which means modification to
 the input array will be known to the caller as well.

 Internally you can think of this:
 // nums is passed in by reference. (i.e., without making a copy)
 int len = removeElement(nums, val);

 // any modification to nums in your function would be known by the caller.
 // using the length returned by your function, it prints the first len elements.
 for (int i = 0; i < len; i++) {
     print(nums[i]);
 }
 */
int removeElement(std::vector<int>& nums, int val) {
    int res = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) {
            nums[res++] = nums[i];
        }
    }
    return res;
}

FTEST(test_removeElement) {
    auto t = [](const std::vector<int>& nums, int v) {
        std::vector<int> n = nums;
        int len = removeElement(n, v);
        std::stringstream ss;
        for (int i = 0; i < len; ++i) {
            ss << n[i] << ",";
        }
        LOG(INFO) << "remove element " << v << " in: " << nums << ", result: " << ss.str();
    };

//    t({}, 0);
//    t({1}, 1);
//    t({1}, 2);
//    t({1, 1}, 1);
//    t({1, 1}, 2);
    t({1, 2}, 1);
    t({1, 2}, 2);
    t({1, 2}, 3);
    t({1, 1, 2, 2}, 1);
    t({1, 1, 2, 2}, 2);
    t({1, 1, 2, 2}, 3);
    t({1, 2, 3}, 1);
    t({1, 2, 3}, 2);
    t({1, 2, 3}, 3);
    t({1, 2, 3}, 4);
    t({1, 1, 2, 2, 3, 3}, 1);
    t({1, 1, 2, 2, 3, 3}, 2);
    t({1, 1, 2, 2, 3, 3}, 3);
    t({1, 1, 2, 2, 3, 3}, 4);
    t({1, 1, 2, 2, 3, 3, 4}, 1);
    t({1, 1, 2, 2, 3, 3, 4}, 2);
    t({1, 1, 2, 2, 3, 3, 4}, 3);
    t({1, 1, 2, 2, 3, 3, 4}, 4);
    t({1, 1, 2, 2, 3, 3, 4}, 5);
    t({1, 2, 3, 4, 5, 6, 7}, 1);
    t({1, 2, 3, 4, 5, 6, 7}, 2);
    t({1, 2, 3, 4, 5, 6, 7}, 3);
    t({1, 2, 3, 4, 5, 6, 7}, 4);
    t({1, 2, 3, 4, 5, 6, 7}, 5);
    t({1, 2, 3, 4, 5, 6, 7}, 6);
    t({1, 2, 3, 4, 5, 6, 7}, 7);
    t({1, 2, 3, 4, 5, 6, 7}, 8);
}

/**
 ///////////// 28. Implement strStr()
 Return the index of the first occurrence of needle in haystack,
 or -1 if needle is not part of haystack.

 Example 1:
 Input: haystack = "hello", needle = "ll"
 Output: 2

 Example 2:
 Input: haystack = "aaaaa", needle = "bba"
 Output: -1

 Clarification:
 What should we return when needle is an empty string?
 This is a great question to ask during an interview.
 For the purpose of this problem, we will return 0 when needle is an empty string.
 This is consistent to C's strstr() and Java's indexOf().
 */
int strStr(std::string haystack, std::string needle) {

    /**
      abcdbcbcbebce
      bce               pos=0
          bce           pos=4, skip=4 (not exist)
            bce         pos=6, skip=2, idx=1
             bce        pos=7, skip=1, idx=2
                bce     pos=10, skip=3, idx=0
     */
    size_t slen = haystack.size();
    size_t len = needle.size();
    if (slen < len) {
        return -1;
    }
    if (slen == 0 || len == 0) {
        return len == 0 ? 0 : -1;
    }
    size_t vv[128];
    for (size_t i = 0; i < 128; ++i) {
        vv[i] = len + 1;
    }
    for (size_t i = 0; i < len; ++i) {
        vv[needle[i]] = len - i;
    }
    size_t pos = 0;
    while (pos <= slen - len) {
        size_t i = 0;
        while (haystack[pos + i] == needle[i]) {
            ++i;
            if (i >= len) {
                return pos;
            }
        }
        pos += vv[haystack[pos + len]];
    }
    return -1;
}

FTEST(test_strStr) {
    auto t = [](const std::string& str, const std::string& find) {
        int idx = strStr(str, find);
        LOG(INFO) << "strstr " << str << ", " << find << ", result: " << idx;
        return idx;
    };

//    FEXP(t("", "aa"), -1);
//    FEXP(t("hello", ""), 0);
//    FEXP(t("hello", "ll"), 2);
//    FEXP(t("aaaaa", "bba"), -1);
//    FEXP(t("aaaaa", "aaaaa"), 0);
//    FEXP(t("aaa", "aaaa"), -1);
    FEXP(t("mississippi", "a"), 0);
}

/**
 ///////////// 29. Divide Two Integers
 Given two integers dividend and divisor, divide two integers without using multiplication,
 division and mod operator. Return the quotient after dividing dividend by divisor.

 The integer division should truncate toward zero.

 Example 1:
 Input: dividend = 10, divisor = 3
 Output: 3

 Example 2:
 Input: dividend = 7, divisor = -3
 Output: -2

 Note:
 Both dividend and divisor will be 32-bit signed integers.
 The divisor will never be 0.
 Assume we are dealing with an environment which could only store integers within
 the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem,
 assume that your function returns 231 − 1 when the division result overflows.
 */
int divide(int dividend, int divisor) {
    return 0;
}

/**
 ///////////// 30. Substring with Concatenation of All Words
 You are given a string, s, and a list of words, words, that are all of the same length.
 Find all starting indices of substring(s) in s that is a concatenation of each
 word in words exactly once and without any intervening characters.

 Example 1:
 Input:
   s = "barfoothefoobarman",
   words = ["foo","bar"]
 Output: [0,9]

 Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
 The output order does not matter, returning [9,0] is fine too.

 Example 2:
 Input:
   s = "wordgoodgoodgoodbestword",
   words = ["word","good","best","word"]
 Output: []
 */
std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
    return {};
}
