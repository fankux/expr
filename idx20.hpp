#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex20 {

typedef LCListNode ListNode;

/**
 ///////////// 201. Bitwise AND of Numbers Range
Given a range [m, n] where 0 <= m <= n <= 2147483647,
 return the bitwise AND of all numbers in this range, inclusive.

Example 1:
Input: [5,7]
Output: 4

Example 2:
Input: [0,1]
Output: 0

 THOUGHTS:
    find common binary prefix from left.

 */
int rangeBitwiseAnd(int m, int n) {
    auto find_zero_func = [&] {
        if (m == n) {
            return m;
        }

        uint32_t res = 0;
        while (m < n) {
            uint32_t level_lower = m == 0 ? 0 : 1u << (sizeof(m) * 8u - __builtin_clz(m) - 1u);
            uint32_t level_upper = n == 0 ? 0 : 1u << (sizeof(n) * 8u - __builtin_clz(n) - 1u);
            if (level_lower != level_upper) {
                break;
            }
            res = res | level_upper;
            m = (level_upper - 1u) & m;
            n = (level_upper - 1u) & n;
        }
        return (int) res;
    };
    auto find_left_common = [&] {
        uint32_t d = UINT_MAX;
        while (((uint32_t) m & d) != ((uint32_t) n & d)) {
            d <<= 1u;
        }
        return (uint32_t) m & d;
    };
    return (int) find_left_common();
}

FTEST(test_rangeBitwiseAnd) {
    auto t = [](int m, int n) {
        auto re = rangeBitwiseAnd(m, n);
        LOG(INFO) << m << " to " << n << " bitwise AND: " << re;
        return re;
    };

    FEXP(t(0, 0), 0);
    FEXP(t(1, 1), 1);
    FEXP(t(2, 2), 2);
    FEXP(t(3, 3), 3);
    FEXP(t(4, 4), 4);
    FEXP(t(0, 1), 0);
    FEXP(t(1, 2), 0);
    FEXP(t(1, 3), 0);
    FEXP(t(2, 3), 2);
    FEXP(t(5, 7), 4);
    FEXP(t(6, 7), 6);
}

/**
 ///////////// 202. Happy Number
Write an algorithm to determine if a number is "happy".
A happy number is a number defined by the following process:
 Starting with any positive integer, replace the number by the sum of the squares of its digits,
 and repeat the process until the number equals 1 (where it will stay),
 or it loops endlessly in a cycle which does not include 1.
 Those numbers for which this process ends in 1 are happy numbers.

Example:
Input: 19
Output: true
Explanation:
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

 THOUGHTS:
    Not happy number MUST exist 4. and square action would be recurring.

 */
bool isHappyNumber(int n) {
    while (n != 1 && n != 4) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        n = sum;
    }
    return n == 1;
}

FTEST(test_isHappyNumber) {
    auto t = [](int n) {
        auto re = isHappyNumber(n);
        LOG(INFO) << n << " is happy number: " << re;
        return re;
    };

    FEXP(t(1), true);
    FEXP(t(2), false);
    FEXP(t(11), false);
    FEXP(t(19), true);
}

/**
 ///////////// 203. Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example:
Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
 */
ListNode* removeElements(ListNode* head, int val) {
    ListNode* pre = nullptr;
    ListNode* p = head;
    while (p) {
        ListNode* n = p->next;
        if (val == p->val) {
            (pre ? pre->next : head) = n;
        } else {
            pre = p;
        }
        p = n;
    }
    return head;
}

FTEST(test_removeElements) {
    auto t = [](const std::vector<int>& nums, int v) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        auto re = removeElements(list, v);
        LOG(INFO) << nums << " remove " << v << " : " << print_list(re);
        return re;
    };

    t({}, 0);
    t({1}, 0);
    t({1}, 1);
    t({1, 1}, 1);
    t({1, 2}, 1);
    t({1, 2}, 2);
    t({1, 2, 1}, 1);
    t({1, 1, 2}, 1);
    t({2, 1, 1}, 1);
    t({1, 2, 3}, 1);
    t({1, 2, 3}, 2);
    t({1, 2, 3}, 3);
    t({1, 2, 6, 3, 4, 5, 6}, 6);
}

/**
 ///////////// 204. Count Primes
Count the number of prime numbers less than a non-negative number, n.

Example:
Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

 THOUGHTS:
    Sieve of Eratosthenes
 */
int countPrimes(int n) {
    int res = 0;
    std::vector<bool> primes(n, true);
    for (int i = 2; i < n; ++i) {
        if (!primes[i]) {
            continue;
        }
        ++res;
        for (int j = 2; i * j < n; ++j) {
            primes[i * j] = false;
        }
    }
    return res;
}

FTEST(test_countPrimes) {
    auto t = [](int n) {
        auto re = countPrimes(n);
        LOG(INFO) << "prime count less than " << n << ": " << re;
        return re;
    };

    FEXP(t(1), 0);
    FEXP(t(2), 0);
    FEXP(t(10), 4);
    FEXP(t(11), 4);
    FEXP(t(12), 5);
    FEXP(t(19), 7);
    FEXP(t(20), 8);
}

/**
 ///////////// 205. Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.
Two strings are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character
 while preserving the order of characters.
No two characters may map to the same character but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true
Note:
You may assume both s and t have the same length.
 */
bool isIsomorphic(std::string s, std::string t) {
    int len = s.size();
    if (t.size() != len) {
        return false;
    }
    int mm[128] = {0};
    int rmm[128] = {0};
    for (int i = 0; i < len; ++i) {
        int from = s[i] + 1;
        int to = t[i] + 1;
        if (mm[from] == 0 && rmm[to] == 0) {
            mm[from] = to;
            rmm[to] = from;
        } else if (mm[from] != to || rmm[to] != from) {
            return false;
        }
    }
    return true;
}

FTEST(test_isIsomorphic) {
    auto t = [](const std::string& s, const std::string& t) {
        auto re = isIsomorphic(s, t);
        LOG(INFO) << "is isomorphic " << s << " and " << t << ": " << re;
        return re;
    };

    FEXP(t("", ""), true);
    FEXP(t("", "a"), false);
    FEXP(t("a", ""), false);
    FEXP(t("a", "a"), true);
    FEXP(t("a", "b"), true);
    FEXP(t("aa", "ba"), false);
    FEXP(t("ac", "bb"), false);
    FEXP(t("ac", "bd"), true);
    FEXP(t("egg", "add"), true);
    FEXP(t("foo", "bar"), false);
    FEXP(t("paper", "title"), true);
    FEXP(t("13", "42"), true);
}

/**
 ///////////// 206. Reverse Linked List
Reverse a singly linked list.

Example:
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

Follow up:
A linked list can be reversed either iteratively or recursively. Could you implement both?
 */
ListNode* reverseList(ListNode* head) {
    auto head_func = [&] {
        ListNode* p = head;
        while (p && p->next) {
            ListNode* oh = head;
            head = p->next;
            p->next = head->next;
            head->next = oh;
        }
        return head;
    };
    auto tail_func = [&] {
        ListNode* pre = nullptr;
        while (head) {
            ListNode* n = head->next;
            head->next = pre;
            pre = head;
            head = n;
        }
        return pre;
    };
    return head_func();
}

FTEST(test_reverseList) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* l1 = list_convert_leetcode(create_list(nums));
        LOG(INFO) << nums << "reverse: " << print_list(reverseList(l1));
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({1, 2, 3, 4, 5});
}

/**
 ///////////// 207. Course Schedule
There are a total of n courses you have to take, labeled from 0 to n-1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1,
 which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs,
 is it possible for you to finish all courses?

Example 1:
Input: 2, [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices.
 Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

 THOUGHTS:
    detect graph circle

 */
bool courseSchedule(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> graph(numCourses);
    auto BFS_func = [&] {
        std::vector<int> ins(numCourses, 0);
        for (auto& prerequisite : prerequisites) {
            ++ins[prerequisite[0]];
            graph[prerequisite[1]].emplace_back(prerequisite[0]);
        }
        std::deque<int> qq;
        for (size_t i = 0; i < ins.size(); ++i) {
            if (ins[i] == 0) {
                qq.emplace_back(i);
            }
        }
        while (!qq.empty()) {
            int c = qq.front();
            qq.pop_front();
            for (int n : graph[c]) {
                if (--ins[n] == 0) {
                    qq.emplace_back(n);
                }
            }
        }
        for (int in : ins) {
            if (in != 0) {
                return false;
            }
        }
        return true;
    };
    auto DFS_func = [&] {
        std::vector<int> visited(numCourses, 0); // 0:invisited, 1:good, -1:failed
        for (auto& prerequisite : prerequisites) {
            graph[prerequisite[0]].emplace_back(prerequisite[1]);
        }
        std::function<bool(int)> DFS_rfunc;
        DFS_rfunc = [&](int start) {
            if (visited[start] != 0) {
                return visited[start] == 1;
            }
            visited[start] = -1;
            for (int n : graph[start]) {
                if (!DFS_rfunc(n)) {
                    return false;
                }
            }
            visited[start] = 1;
            return true;
        };
        for (int i = 0; i < numCourses; ++i) {
            if (!DFS_rfunc(i)) {
                return false;
            }
        }
        return true;
    };
    return DFS_func();
}

FTEST(test_courseSchedule) {
    auto t = [](int n, const std::vector<std::vector<int>>& nums) {
        std::vector<std::vector<int>> nns = nums;
        auto re = courseSchedule(n, nns);
        LOG(INFO) << n << ", " << nums << " can finish: " << re;
        return re;
    };

    FEXP(t(0, {}), true);
    FEXP(t(1, {}), true);
    FEXP(t(1, {{0, 0}}), false);
    FEXP(t(2, {{0, 1}}), true);
    FEXP(t(2, {{1, 0}}), true);
    FEXP(t(2, {{1, 0}, {0, 1}}), false);
    FEXP(t(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}), true);
}

/**
 ///////////// 208. Implement Trie (Prefix Tree)
Implement a trie with insert, search, and startsWith methods.

Example:
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");
trie.search("app");     // returns true

Note:
You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.

 **
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() = default;

    /** Inserts a word into the trie. */
    void insert(std::string word) {
        TrieNode* p = &root;
        for (char c : word) {
            c -= 'a';
            if (p->nexts[c] == nullptr) {
                p->nexts[c] = new TrieNode(c);
            }
            p = p->nexts[c];
        }
        p->end = !word.empty();
    }

    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        TrieNode* p = &root;
        for (char c : word) {
            c -= 'a';
            if (p->nexts[c] == nullptr) {
                return false;
            }
            p = p->nexts[c];
        }
        return p != nullptr && p->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        TrieNode* p = &root;
        for (char c : prefix) {
            c -= 'a';
            if (p->nexts[c] == nullptr) {
                return false;
            }
            p = p->nexts[c];
        }
        return p != nullptr;
    }

private:
    struct TrieNode {
        explicit TrieNode(char value) : v(value) {
            for (auto& next : nexts) {
                next = nullptr;
            }
        }

        TrieNode* nexts[26]{nullptr};
        char v = 0;
        bool end = false;
    };

    TrieNode root{'\0'};
};

FTEST(test_leetcodeTrie) {
    Trie trie;
    trie.insert("Trie");
    FEXP(trie.search("a"), false);
}


/**
 ///////////// 209. Minimum Size Subarray Sum
Given an array of n positive integers and a positive integer s,
 find the minimal length of a contiguous subarray of which the sum ≥ s.
 If there isn't one, return 0 instead.

Example:
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
Follow up:
If you have figured out the O(n) solution,
 try coding another solution of which the time complexity is O(n log n).

THOUGHTS(map):
    accmulate memeber and put pair<sum, index> to a map.
    Once sum>=s, check if there exists sum-in-map<=sum-s, and we compare the minmium length.

    0   1   2   3   4   5
    2   3   1   2   4   3       map             res
    2                        2                  0
        5                    2,5                0
            6                2,5,6              0
                8            2,5,6,8            4, (8-7=1 not exist)
                    12       2,5,6,8,12         3, (12-7=5, idx=1, res=4-1=3)
                        15   2,5,6,8,12,15      2, (15-7=8, idx=3, res=5-3=2)
 */
int minSubArrayLen(int s, std::vector<int>& nums) {
    auto map_method = [&] {
        std::map<int, int> mm;
        int res = INT_MAX;
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            mm[sum] = i;

            if (sum >= s) {
                res = std::min(res, i + 1);
                auto iter = mm.upper_bound(sum - s);
                if (!mm.empty() && iter != mm.begin()) {
                    --iter;
                    res = std::min(res, i - iter->second);
                }
            }
        }
        return nums.empty() || sum < s ? 0 : res;
    };
    auto two_index_method = [&] {
        int res = 0;
        int sum = 0;
        nums.emplace_back(0);
        for (int i = 0, j = 0; i < nums.size();) {
            if (sum < s) {
                sum += nums[i++];
                continue;
            }
            res = res == 0 ? i - j : std::min(res, i - j);
            sum -= nums[j++];
        }
        return res;
    };
    return two_index_method();
}

FTEST(test_minSubArrayLen) {
    auto t = [](int n, const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = minSubArrayLen(n, nns);
        LOG(INFO) << n << ", " << nums << " min len: " << re;
        return re;
    };

    FEXP(t(100, {}), 0);
    FEXP(t(3, {1, 1}), 0);
    FEXP(t(7, {2, 3, 1, 2, 4, 3}), 2);
    FEXP(t(7, {2, 3, 1, 2, 4, 3, 7}), 1);
    FEXP(t(7, {2, 3, 1, 2, 7, 4, 3}), 1);
    FEXP(t(4, {1, 4, 4}), 1);
    FEXP(t(11, {1, 2, 3, 4, 5}), 3);
}

/**
 ///////////// 210. Course Schedule II
There are a total of n courses you have to take, labeled from 0 to n-1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1,
 which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs,
 return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them.
 If it is impossible to finish all courses, return an empty array.

Example 1:
Input: 2, [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
             course 0. So the correct course order is [0,1] .

Example 2:
Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices.
 Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
 */
std::vector<int> courseScheduleII(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<int> res;
    std::vector<std::vector<int>> graph(numCourses);
    auto BFS_func = [&]() -> decltype(res) {
        std::vector<int> ins(numCourses, 0);
        for (auto& prerequisite : prerequisites) {
            ++ins[prerequisite[0]];
            graph[prerequisite[1]].emplace_back(prerequisite[0]);
        }
        std::deque<int> qq;
        for (size_t i = 0; i < ins.size(); ++i) {
            if (ins[i] == 0) {
                qq.emplace_back(i);
            }
        }
        while (!qq.empty()) {
            int c = qq.front();
            qq.pop_front();
            res.emplace_back(c);
            for (int n : graph[c]) {
                if (--ins[n] == 0) {
                    qq.emplace_back(n);
                }
            }
        }
        return res.size() != numCourses ? res.clear(), res : res;
    };
    auto DFS_func = [&]() -> decltype(res) {
        std::vector<int> visited(numCourses, 0); // 0:invisited, 1:good, -1:failed
        for (auto& prerequisite : prerequisites) {
            graph[prerequisite[0]].emplace_back(prerequisite[1]);
        }
        std::function<bool(int)> DFS_rfunc;
        DFS_rfunc = [&](int start) {
            if (visited[start] != 0) {
                return visited[start] == 1;
            }
            visited[start] = -1;
            for (int n : graph[start]) {
                if (!DFS_rfunc(n)) {
                    return false;
                }
            }
            if (res.size() < numCourses) {
                res.emplace_back(start);
            }
            visited[start] = 1;
            return true;
        };
        for (int i = 0; i < numCourses; ++i) {
            if (!DFS_rfunc(i)) {
                return {};
            }
        }
        return res;
    };
    return BFS_func();
}

FTEST(test_courseScheduleII) {
    auto t = [](int n, const std::vector<std::vector<int>>& nums) {
        std::vector<std::vector<int>> nns = nums;
        auto re = courseScheduleII(n, nns);
        LOG(INFO) << n << ", " << nums << " can finish: " << re;
        return re;
    };

    t(0, {});
    t(1, {});
    t(1, {{0, 0}});
    t(2, {{0, 1}});
    t(2, {{1, 0}});
    t(2, {{1, 0}, {0, 1}});
    t(2, {{1, 0}, {0, 1}});
    t(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}});
}

}