#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex14 {

typedef LCListNode ListNode;

/**
 ///////////// 141. Linked List Cycle
Given a linked list, determine if it has a cycle in it.
To represent a cycle in the given linked list,  we use an integer pos which represents
 the position (0-indexed) in the linked list where tail connects to. If pos is -1,
 then there is no cycle in the linked list.

Example 1:
    3 → 2 → 0 → -4 -|
        ↑___________|

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
    1 → 2 -|
    ↑______|

Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
    1 → NULL

Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.

Follow up:
Can you solve it using O(1) (i.e. constant) memory?
 */
bool hasLinkCycle(ListNode* head) {
    ListNode* fast = head;
    while (head && fast && fast->next) {
        head = head->next;
        fast = fast->next->next;
        if (head == fast) {
            return true;
        }
    }
    return false;
}

FTEST(test_hasLinkCycle) {
    auto t = [](const std::vector<int>& nums, int to) {
        std::vector<ListNode*> nodes;
        ListNode* list = list_convert_leetcode(create_list(nums), nodes);
        if (to != -1) {
            nodes.back()->next = nodes[to];
        }
        auto re = hasLinkCycle(list);
        LOG(INFO) << nums << " has cycle: " << re;
        return re;
    };

    t({3, 2, 0, -4}, 1);
    t({1, 2}, 0);
    t({1}, -1);
}

/**
 ///////////// 142. Linked List Cycle II
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
To represent a cycle in the given linked list, we use an integer pos which
 represents the position (0-indexed) in the linked list where tail connects to.
 If pos is -1, then there is no cycle in the linked list.
Note: Do not modify the linked list.

Example 1:
    3 → 2 → 0 → -4 -|
        ↑___________|

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
    1 → 2 -|
    ↑______|

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
    1 → NULL

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.

Follow-up:
Can you solve it without using extra space?
 */
ListNode* detectLinkCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (slow && fast) {
        if (fast->next == nullptr) {
            return nullptr;
        }
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    slow = head;
    while (slow != fast && fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

FTEST(test_detectLinkCycle) {
    auto t = [](const std::vector<int>& nums, int to) {
        std::vector<ListNode*> nodes;
        ListNode* list = list_convert_leetcode(create_list(nums), nodes);
        if (to != -1) {
            nodes.back()->next = nodes[to];
        }
        auto re = detectLinkCycle(list);
        if (re == nullptr) {
            LOG(INFO) << nums << " not cycle";
        } else {
            LOG(INFO) << nums << " cycle entry: " << re->val;
        }
        return re;
    };

    t({3, 2, 0, -4}, 1);
    t({1, 2}, 0);
    t({1}, -1);
}

/**
 ///////////// 143. Reorder List
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:
Given 1->2->3->4, reorder it to 1->4->2->3.

Example 2:
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 */
void reorderList(ListNode* head) {
}

/**
 ///////////// 144. Binary Tree Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.

Example:
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
Follow up: Recursive solution is trivial, could you do it iteratively?
 */
std::vector<int> preorderTraversal(TreeNode* root) {
    return {};
}

/**
 ///////////// 145. Binary Tree Postorder Traversal
Given a binary tree, return the postorder traversal of its nodes' values.

Example:
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
Follow up: Recursive solution is trivial, could you do it iteratively?
 */
std::vector<int> postorderTraversal(TreeNode* root) {
    return {};
}

/**
 ///////////// 146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache.
 It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache,
 otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present.
 When the cache reached its capacity, it should invalidate the least recently used item
 before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:
LRUCache cache = new LRUCache( 2 / capacity / );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

* Your LRUCache object will be instantiated and called as such:
* LRUCache* obj = new LRUCache(capacity);
* int param_1 = obj->get(key);
* obj->put(key,value);
*/
class LRUCache {
public:
    explicit LRUCache(int capacity) {
        _size = capacity;
    }

    int get(int key) {
        auto entry = _vals.find(key);
        if (entry == _vals.end()) {
            return -1;
        }
        _uses.detach(entry->second.second);
        _uses.add_tail(entry->second.second);
        return entry->second.first;
    }

    void put(int key, int value) {
        auto entry = _vals.find(key);
        if (entry != _vals.end()) {
            entry->second.first = value;
            _uses.detach(entry->second.second);
            _uses.add_tail(entry->second.second);
            return;
        }
        if (_vals.size() == _size) {
            FListNode<int>* head = _uses.pop_head();
            _vals.erase(head->data());
            delete head;
        }
        _uses.add_tail(key);
        _vals.emplace(key, std::make_pair(value, _uses.tail()));
    }

    size_t size() const {
        return _vals.size();
    }

    void clear() {
        _vals.clear();
        _uses.clear();
    }

private:
    size_t _size;
    std::map<int, std::pair<int, FListNode<int>*>> _vals;   // <key, <val, node_ref>>
    FList<int> _uses; // <key>
};

FTEST(test_LRUCache) {
    LRUCache cache(2);
    cache.put(1, 1);
    FEXP(cache.size(), 1);
    cache.put(2, 2);
    FEXP(cache.size(), 2);
    FEXP(cache.get(1), 1);       // returns 1
    cache.put(3, 3);               // evicts key 2
    FEXP(cache.size(), 2);
    FEXP(cache.get(2), -1);      // returns -1 (not found)
    cache.put(4, 4);               // evicts key 1
    FEXP(cache.size(), 2);
    FEXP(cache.get(1), -1);      // returns -1 (not found)
    FEXP(cache.get(3), 3);       // returns 3
    FEXP(cache.get(4), 4);       // returns 4

    cache.clear();
    cache.put(2, 1);
    FEXP(cache.size(), 1);
    cache.put(2, 2);
    FEXP(cache.size(), 1);
    FEXP(cache.get(2), 2);
    cache.put(1, 1);
    FEXP(cache.size(), 2);
    cache.put(4, 1);
    FEXP(cache.size(), 2);
    FEXP(cache.get(2), -1);
}

/**
 ///////////// 147. Insertion Sort List
Sort a linked list using insertion sort.
A graphical example of insertion sort. The partial sorted list (black) initially
 contains only the first element in the list.
With each iteration one element (red) is removed from the input data and
 inserted in-place into the sorted list

Algorithm of Insertion Sort:
Insertion sort iterates, consuming one input element each repetition,
 and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data,
 finds the location it belongs within the sorted list, and inserts it there.
It repeats until no input elements remain.

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5
 */
ListNode* insertionSortList(ListNode* head) {
    return nullptr;
}

/**
 ///////////// 148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5
 */
ListNode* sortList(ListNode* head) {
    return nullptr;
}

/**
 ///////////// 149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:
Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o
+------------->
0  1  2  3  4

Example 2:
Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
 */
int maxPoints(std::vector<std::vector<int>>& points) {
    return 0;
}

/**
 ///////////// 150. Evaluate Reverse Polish Notation
Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:
Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a
 result and there won't be any divide by zero operation.

Example 1:
Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:
Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:
Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation:
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 */
int evalRPN(std::vector<std::string>& tokens) {
    return 0;
}

}