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
    auto insert_func = [&] {
        ListNode* pre = nullptr;
        ListNode* p = head;
        while (p) {
            ListNode* n = p->next;
            ListNode* qpre = nullptr;
            ListNode* q = head;
            while (q && q != p && p->val > q->val) {    // find q postion before p
                qpre = q;
                q = q->next;
            }
            assert(q != nullptr);
            if (p != q) {
                (pre ? pre->next : head) = p->next;     // detach p
                p->next = q;                            // link p->q
                (qpre ? qpre->next : head) = p;         // make p before q
            }
            pre = q->next == n ? q : pre;               // update pre
            p = n;
        }
        return head;
    };

    std::function<ListNode*(ListNode*&, ListNode*)> quick_sort_func;
    quick_sort_func = [&](ListNode*& start, ListNode* end) { // end is right border unclosed
        if (start == nullptr || start == end || start->next == end) {
            return (start == nullptr || start == end) ? nullptr : start;
        }
        ListNode* pivot = start;
        ListNode* pre = start;
        ListNode* p = start->next;
        while (p && p != end) {
            ListNode* n = p->next;
            if (p->val < pivot->val) {
                pre->next = p->next;    // detach p
                p->next = start;        // make p as head
                start = p;
            } else {
                pre = p;
            }
            p = n;
        }
        pre = quick_sort_func(start, pivot);
        if (pre) {
            pre->next = pivot;
        }
        p = pivot->next;
        pre = quick_sort_func(p, end);
        pivot->next = p;
        return pre;
    };
    quick_sort_func(head, nullptr);
    return head;
}

FTEST(test_sortList) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        auto re = sortList(list);
        LOG(INFO) << nums << " sorted: " << print_list(re);
        return re;
    };

    t({});
    t({1});
    t({1, 1});
    t({1, 2});
    t({2, 1});
    t({1, 1, 1});
    t({1, 1, 2});
    t({1, 2, 2});
    t({2, 2, 1});
    t({1, 2, 3});
    t({1, 3, 2});
    t({2, 1, 3});
    t({2, 3, 1});
    t({3, 1, 2});
    t({3, 2, 1});
    t({4, 2, 1, 3});
    t({4, 2, 1, 5, 3});
    t({-1, 5, 3, 4, 0});
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

 THOUGHTS:
    notice that greatest common divisor (GCD) must concern signature.
    gradient of two points also need,
    as follow, if we ignore signature of GCD:
        delta of [3,2] to [2,3] is (-1,1),
        delta of [3,2] to [4,1] is (1,-1)
        these are different respect to std::pair causing error.
    only we concern signature of GCD which we got -1 that points delta would be fixed.
 */
int maxPointsSameLine(std::vector<std::vector<int>>& points) {
    auto gcd = [](int a, int b) {
        while (b != 0) {
            int r = b;
            b = a % b;
            a = r;
        }
        return a;
    };
    size_t len = points.size();
    int res = 0;
    for (size_t i = 0; i < len; ++i) {
        std::map<std::pair<int, int>, int> vv;
        int dup = 1;
        for (size_t j = i + 1; j < len; ++j) {
            if (points[j][0] == points[i][0] && points[j][1] == points[i][1]) {
                ++dup;              // avoid gradient be 0 causing divded by 0 error
                continue;
            }
            int x_delta = points[j][0] - points[i][0];
            int y_delta = points[j][1] - points[i][1];
            int xygcd = gcd(x_delta, y_delta);
            ++vv[{x_delta / xygcd, y_delta / xygcd}];
        }
        res = std::max(res, dup);
        for (auto& entry : vv) {
            res = std::max(res, entry.second + dup);
        }
    }
    return res;
}

FTEST(test_maxPointsSameLine) {
    auto t = [](const std::vector<std::vector<int>>& points) {
        std::vector<std::vector<int>> nns = points;
        auto re = maxPointsSameLine(nns);
        LOG(INFO) << points << " max points in samve line: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({{1, 1}}), 1);
    FEXP(t({{1, 1}, {2, 2}, {3, 3}}), 3);
    FEXP(t({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}), 4);
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
    std::map<std::string, std::function<int(int, int)>> signs{
            {"+", [](int a, int b) {
                return a + b;
            }},
            {"-", [](int a, int b) {
                return a - b;
            }},
            {"*", [](int a, int b) {
                return a * b;
            }},
            {"/", [](int a, int b) {
                return a / b;
            }}};
    std::stack<int> ss;
    for (auto& token : tokens) {
        auto entry = signs.find(token);
        if (entry != signs.end()) {
            int val = ss.top();
            ss.pop();
            ss.top() = entry->second(ss.top(), val);
        } else {
            ss.push(strtol(token.c_str(), nullptr, 10));
        }
    }
    return ss.top();
}

FTEST(test_evalRPN) {
    auto t = [](const std::vector<std::string>& tokens) {
        std::vector<std::string> nns = tokens;
        auto re = evalRPN(nns);
        LOG(INFO) << tokens << " valus: " << re;
        return re;
    };

    FEXP(t({"2", "1", "+", "3", "*"}), 9);
    FEXP(t({"4", "13", "5", "/", "+"}), 6);
    FEXP(t({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}), 22);
}

}