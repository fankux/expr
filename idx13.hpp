#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex13 {

/**
 ///////////// 131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

Example:
Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]
 THOUGHTS:
    See question 5, we caculate palindromic dp infos first, then we extract them.
*/
std::vector<std::vector<std::string>> palindromePartition(std::string s) {
    size_t len = s.size();
    std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, false));
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j || (i == j + 1 && s[i] == s[j]) ||
                    (i > j + 1 && s[i] == s[j] && dp[j + 1][i - 1])) {
                dp[j][i] = true;
            }
        }
    }
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> re;
    std::function<void(int)> r_func;
    r_func = [&](int start) {
        if (start >= len) {
            res.emplace_back(re);
            return;
        }
        for (int i = start; i < len; ++i) {
            if (dp[start][i]) {
                re.emplace_back(s.substr(start, i - start + 1));
                r_func(i + 1);
                re.pop_back();
            }
        }
    };
    r_func(0);
    return res;
}

FTEST(test_palindromePartition) {
    auto t = [](const std::string& s) {
        auto re = palindromePartition(s);
        LOG(INFO) << s << " palindrome substrs: " << re;
        return re;
    };

    t("");
    t("a");
    t("ab");
    t("aba");
    t("aab");
}

/**
 ///////////// 132. Palindrome Partitioning II
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example:
Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/
int palindromePartitionMinCut(std::string s) {
    size_t len = s.size();
    std::vector<int> min_state(len);
    std::vector<std::vector<bool>> state(len, std::vector<bool>(len, false));
    for (int i = 0; i < len; ++i) {
        min_state[i] = i;
        for (int j = 0; j <= i; ++j) {
            if (i == j) {
                state[j][i] = true;
            } else if (i == j + 1) {
                state[j][i] = s[i] == s[j];
            } else { // j > i + 1
                state[j][i] = state[j + 1][i - 1] && s[i] == s[j];
            }
            if (state[j][i]) {
                min_state[i] = j == 0 ? 0 : std::min(min_state[i], min_state[j - 1] + 1);
            }
        }
    }
    return len == 0 ? 0 : min_state[len - 1];
}

FTEST(test_palindromePartitionMinCut) {
    auto t = [](const std::string& s) {
        auto re = palindromePartitionMinCut(s);
        LOG(INFO) << s << " palindrome substrs: " << re;
        return re;
    };

    FEXP(t(""), 0);
    FEXP(t("a"), 0);
    FEXP(t("ab"), 1);
    FEXP(t("aba"), 0);
    FEXP(t("aab"), 1);
    FEXP(t("ababababababababababababcbabababababababababababa"), 0);
}

/**
 ///////////// 133. Clone Graph
Given a reference of a node in a connected undirected graph.
Return a deep copy (clone) of the graph.
Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.
```
class Node {
    public int val;
    public List<Node> neighbors;
}
```
Test case format:
For simplicity sake, each node's value is the same as the node's index (1-indexed).
 For example, the first node with val = 1, the second node with val = 2, and so on.
 The graph is represented in the test case using an adjacency list.
Adjacency list is a collection of unordered lists used to represent a finite graph.
 Each list describes the set of neighbors of a node in the graph.
The given node will always be the first node with val = 1.
 You must return the copy of the given node as a reference to the cloned graph.

Example 1:

                                    (1)────────────────────────(2)
                                     │                          │
                                 ↗   │  you can't return the    │
                               /     │     same graph           │
                             X       │                          │
                           /        (3)────────────────────────(4)

  (1)────────────────────────(2)    [1]────────────────────────[2]
   │                          │      │  This looks like a       │
   │      Original Graph      │ ==>  │  clone.The nodes are     │
   │                          │      │  NEW. Graph looks the    │
   │                          │      │  same.                   │
  (3)────────────────────────(4)    [3]────────────────────────[4]
                           \
                            X       [1]────────────────────────[3]
                             \       │                          │
                              ↘      │  The nodes are cloned.   │
                                     │  But graph is messed up. │
                                     │                          │
                                    [4]────────────────────────[2]

Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:

     (1)

Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list.
 The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:

Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.

Example 4:

     (1) -----> (2)

Input: adjList = [[2],[1]]
Output: [[2],[1]]

Constraints:
 - 1 <= Node.val <= 100
 - Node.val is unique for each node.
 - Number of Nodes will not exceed 100.
 - There is no repeated edges and no self-loops in the graph.
 - The Graph is connected and all nodes can be visited starting from the given node.
*/
class Node {
public:
    int val;
    std::vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }

    explicit Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }

    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node) {
    std::unordered_map<Node*, Node*> mm;
    std::set<Node*> visited{node};
    std::deque<Node*> qq{node};
    Node* res = nullptr;

    while (!qq.empty()) {
        Node* n = qq.front();
        qq.pop_front();
        if (n == nullptr) {
            continue;
        }

        auto entry = mm.find(n);
        if (entry == mm.end()) {
            mm[n] = new Node(n->val);
            entry = mm.find(n);
        }

        for (Node* neighbor : n->neighbors) {
            if (visited.count(neighbor) == 0) {
                qq.emplace_back(neighbor);
                visited.insert(neighbor);
            }
            if (mm.count(neighbor) == 0) {
                mm[neighbor] = new Node(neighbor->val);
            }
            entry->second->neighbors.emplace_back(mm[neighbor]);
        }

        if (n == node) {
            res = entry->second;
        }
    }
    return res;
}

FTEST(test_cloneGraph) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    n1.neighbors = {&n2, &n4};
    n2.neighbors = {&n1, &n3};
    n3.neighbors = {&n2, &n4};
    n4.neighbors = {&n1, &n3};

    Node* nn = cloneGraph(&n1);
}

/**
 ///////////// 134. Gas Station
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel
 from station i to its next station (i+1). You begin the journey with an empty tank
 at one of the gas stations.
Return the starting gas station's index if you can travel around the circuit
 once in the clockwise direction, otherwise return -1.

Note:
If there exists a solution, it is guaranteed to be unique.
Both input arrays are non-empty and have the same length.
Each element in the input arrays is a non-negative integer.

Example 1:
Input:
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.

Example 2:
Input:
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.

THOUGHTS:
  RULE_1: total gas must >= total cost
  RULE_1: SUM is the cost from START to current pos, once SUM less than 0 means no gas station
          from the START could be a valid one.
*/
int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    int total = 0;
    int sum = 0;
    int start = 0;
    for (size_t i = 0; i < gas.size(); ++i) {
        total += gas[i] - cost[i];
        sum += gas[i] - cost[i];
        if (sum < 0) {
            sum = 0;
            start = i + 1;
        }
    }
    return total < 0 ? -1 : start;
}

FTEST(test_canCompleteCircuit) {
    auto t = [](const std::vector<int>& gas, const std::vector<int>& cost) {
        std::vector<int> g = gas;
        std::vector<int> c = cost;
        auto re = canCompleteCircuit(g, c);
        LOG(INFO) << "gas:" << gas << ", cost:" << cost << " can circuit: " << re;
        return re;
    };

    FEXP(t({}, {}), 0);
    FEXP(t({2, 3, 4}, {3, 4, 3}), -1);
    FEXP(t({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}), 3);
}

/**
 ///////////// 135. Candy
There are N children standing in a line. Each child is assigned a rating value.
You are giving candies to these children subjected to the following requirements:
 - Each child must have at least one candy.
 - Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

Example 1:
Input: [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2,1,2 candies respectively.

Example 2:
Input: [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1,2,1 candies respectively.
             The third child gets 1 candy because it satisfies the above two conditions.

THOUGHTS(iter method):
  1  2  5  4  3  2  1
  1  2  3  p              at p, 4 less than previous 5,
       pre                we find how much number forms a decreasing arithmetic sequence

  1  2  5  4  3  2  1     from s to e there are 4 numbers, easy to calculate is 4(4+1)/2=10,
       pre s        e     and we plus count to pos pre, which is 4-3+1=2

  if there exist duplicate number, just set the latter one to 1

  finally, we acculate all count.
*/
int candy(std::vector<int>& ratings) {
    size_t len = ratings.size();
    auto two_iter_method = [&] {
        std::vector<int> nums(len, 1); // at least 1
        for (size_t i = 0; i < len; ++i) {
            if (i > 0 && ratings[i] > ratings[i - 1] && nums[i] <= nums[i - 1]) {
                nums[i] = nums[i - 1] + 1;
            }
        }
        for (int i = len - 1; i >= 0; --i) {
            if (i < len - 1 && ratings[i] > ratings[i + 1] && nums[i] <= nums[i + 1]) {
                nums[i] = nums[i + 1] + 1;
            }
        }
        int res = 0;
        for (int num : nums) {
            res += num;
        }
        return res;
    };
    auto one_iter_method = [&] {
        if (ratings.empty()) {
            return 0;
        }
        int res = 1;
        int pre = 1;
        int count = 0;
        for (size_t i = 1; i < len; ++i) {
            if (ratings[i] >= ratings[i - 1]) {
                if (count > 0) {
                    res += count * (count + 1) / 2;
                    if (pre <= count) {
                        res += count - pre + 1;
                    }
                    count = 0;
                    pre = 1;
                }
                pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1;
                res += pre;
            } else {
                ++count;
            }
        }
        if (count > 0) {
            res += count * (count + 1) / 2;
            if (pre <= count) {
                res += count - pre + 1;
            }
        }
        return res;
    };
    return one_iter_method();
}

FTEST(test_candy) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = candy(nns);
        LOG(INFO) << nums << " candy cost: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({0}), 1);
    FEXP(t({1}), 1);
    FEXP(t({0, 0}), 2);
    FEXP(t({1, 0}), 3);
    FEXP(t({0, 1}), 3);
    FEXP(t({1, 1}), 2);
    FEXP(t({0, 0, 0}), 3);
    FEXP(t({0, 1, 1}), 4);
    FEXP(t({1, 0, 0}), 4);
    FEXP(t({0, 1, 0}), 4);
    FEXP(t({0, 0, 1}), 4);
    FEXP(t({0, 1, 1}), 4);
    FEXP(t({1, 2, 2}), 4);
    FEXP(t({1, 0, 1}), 5);
    FEXP(t({1, 0, 2}), 5);
    FEXP(t({1, 1, 0}), 4);
    FEXP(t({1, 1, 1}), 3);
    FEXP(t({1, 2, 3}), 6);
    FEXP(t({1, 3, 2}), 4);
    FEXP(t({2, 1, 3}), 5);
    FEXP(t({2, 3, 1}), 4);
    FEXP(t({3, 1, 2}), 5);
    FEXP(t({3, 2, 1}), 6);
}

/**
 ///////////// 136. Single Number
Given a non-empty array of integers, every element appears twice except for one.
 Find that single one.

Note:
Your algorithm should have a linear runtime complexity.
 Could you implement it without using extra memory?

Example 1:
Input: [2,2,1]
Output: 1

Example 2:
Input: [4,1,2,1,2]
Output: 4
*/
int singleNumber(std::vector<int>& nums) {
    for (int i = 1; i < nums.size(); ++i) {
        nums[0] ^= nums[i];
    }
    return nums[0];
}

FTEST(test_singleNumber) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = singleNumber(nns);
        LOG(INFO) << nums << " single number: " << re;
        return re;
    };

    FEXP(t({1}), 1);
    FEXP(t({1, 2, 2}), 1);
    FEXP(t({2, 2, 1}), 1);
    FEXP(t({4, 1, 2, 1, 2}), 4);
}

/**
 ///////////// 137. Single Number II
Given a non-empty array of integers, every element appears three times except for one,
 which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity.
 Could you implement it without using extra memory?

Example 1:
Input: [2,2,3,2]
Output: 3

Example 2:
Input: [0,1,0,1,0,1,99]
Output: 99
*/
int singleNumberII(std::vector<int>& nums) {
    int res = 0;
    int count_1 = 0;
    uint32_t mask = 1;
    for (int i = 0; i < 32; ++i) {
        count_1 = 0;
        for (int num : nums) {
            count_1 += (num & mask) != 0 ? 1 : 0;
        }
        res |= (count_1 % 3 != 0) ? mask : 0;
        mask <<= 1;
    }
    return res;
}

FTEST(test_singleNumberII) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = singleNumberII(nns);
        LOG(INFO) << nums << " single number: " << re;
        return re;
    };

    FEXP(t({0, 0, 0, 1}), 1);
    FEXP(t({1, 0, 1, 1}), 0);
    FEXP(t({2, 2, 3, 2}), 3);
    FEXP(t({0, 1, 0, 1, 0, 1, 99}), 99);
}

/**
 ///////////// 138. Copy List with Random Pointer
A linked list is given such that each node contains an additional random pointer
 which could point to any node in the list or null.
Return a deep copy of the list.
The Linked List is represented in the input/output as a list of n nodes.
 Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) where random pointer points to,
 or null if it does not point to any node.

Example 1:
 _____________    ______________    ______________    ______________    _____________
 | 7 | next -|--->| 13 | next -|--->| 11 | next -|--->| 10 | next -|--->| 1 | next -|--->NULL
 |___|_rand__|    |____|_rand__|    |____|_rand__|    |____|_rand__|    |___|_rand__|     ↑
   ↑____|_________________|           ↑_____|_________________|          ↑     |          |
   |____|___________________________________|____________________________|_____|          |
        |                                   |____________________________|                |
        |_________________________________________________________________________________|

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:
 _____________    _____________
 | 1 | next -|--->| 2 | next -|--->NULL
 |___|_rand__|    |___|_rand__|
                    ↑_____|

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:
 _____________    _____________    _____________
 | 3 | next -|--->| 3 | next -|--->| 3 | next -|--->NULL
 |___|_rand__|    |___|_rand__|    |___|_rand__|     ↑
    ↑___|________________|                |__________|
        |____________________________________________|

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Example 4:
Input: head = []
Output: []
Explanation: Given linked list is empty (null pointer), so return null.

Constraints:
-10000 <= Node.val <= 10000
Node.random is null or pointing to a node in the linked list.
Number of Nodes will not exceed 1000.
*/
namespace Q138 {
class Node {
public:
    int val;
    Node* next;
    Node* random;

    explicit Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copyRandomList(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* p = head;
    while (p) {
        Node* next = p->next;
        p->next = new Node(p->val);
        p->next->next = next;
        p = next;
    }
    p = head;
    while (p) {
        p->next->random = p->random ? p->random->next : nullptr;
        p = p->next->next;
    }
    p = head;
    head = p->next;
    while (p) {
        Node* next = p->next;
        p->next = next->next;
        p = next->next;
        next->next = p ? p->next : nullptr;
    }
    return head;
}
}

/**
 ///////////// 139. Word Break
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
 determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
*/
bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    TrieNode* dict = create_trie(wordDict);
    size_t len = s.size();
    std::vector<std::vector<size_t>> dp(len);
    for (int i = len - 1; i >= 0; --i) {
        int pos = i;
        TrieNode* n = dict;
        while (pos < len && n) {
            n = n->nexts[s[pos++]];
            // pos is word right border that is unclosed or the s.end().
            // pos == len must be preorder than dp[pos] avoiding memory over range.
            if (n && n->end && (pos == len || !dp[pos].empty())) {
                dp[i].emplace_back(pos);
            }
        }
    }
    return !dp[0].empty();
}

FTEST(test_wordBreak) {
    auto t = [](const std::string& s, const std::vector<std::string>& wordDict) {
        std::vector<std::string> nns = wordDict;
        auto re = wordBreak(s, nns);
        LOG(INFO) << s << ", " << wordDict << " break: " << re;
        return re;
    };

    t("abcdef", {"abcde", "ab", "ef"});
    t("abcdef", {"abcde", "fg"});
    t("abcdef", {"ab", "cd", "ef"});
    t("abcdef", {"abc", "ab", "cd", "ef"});
    t("abcdef", {"abc", "ab", "cde", "cd", "ef"});
    t("abcdef", {"abcde", "ab", "cd", "ef"});
    t("abcdef", {"abcde", "ab", "abc", "cd", "ef", "d", "def"});
    t("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"});
    t("aaaaaaaaaaaaaaaaaaaaaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa"});
    t("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa",
            "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
}

/**
 ///////////// 140. Word Break II
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
 add spaces in s to construct a sentence where each word is a valid dictionary word.
 Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

Example 2:
Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
*/
std::vector<std::string> wordBreakII(std::string s, std::vector<std::string>& wordDict) {
    TrieNode* dict = create_trie(wordDict);
    size_t len = s.size();
    std::vector<std::vector<size_t>> dp(len);
    for (int i = len - 1; i >= 0; --i) {
        int pos = i;
        TrieNode* n = dict;
        while (pos < len && n) {
            n = n->nexts[s[pos++]];
            // pos is word right border that is unclosed or the s.end().
            // pos == len must be preorder than dp[pos] avoiding memory over range.
            if (n && n->end && (pos == len || !dp[pos].empty())) {
                dp[i].emplace_back(pos);
            }
        }
    }
    std::vector<size_t> re{0};
    std::vector<std::string> res;
    std::function<void(int)> r_func;
    r_func = [&](int start) {
        if (start >= len) {
            res.emplace_back();
            for (size_t i = 1; i < re.size(); ++i) {
                if (i > 1) {
                    res.back() += ' ';
                }
                res.back() += s.substr(re[i - 1], re[i] - re[i - 1]);
            }
            return;
        }
        for (auto& next : dp[start]) {
            re.emplace_back(next);
            r_func(next);
            re.pop_back();
        }
    };
    r_func(0);
    return res;
}

FTEST(test_wordBreakII) {
    auto t = [](const std::string& s, const std::vector<std::string>& wordDict) {
        std::vector<std::string> nns = wordDict;
        auto re = wordBreakII(s, nns);
        LOG(INFO) << s << ", " << wordDict << " break: " << re;
        return re;
    };

    t("abcdef", {"abcde", "ab", "ef"});
    t("abcdef", {"abcde", "fg"});
    t("abcdef", {"ab", "cd", "ef"});
    t("abcdef", {"abc", "ab", "cd", "ef"});
    t("abcdef", {"abc", "ab", "cde", "cd", "ef"});
    t("abcdef", {"abcde", "ab", "cd", "ef"});
    t("abcdef", {"abcde", "ab", "abc", "cd", "ef", "d", "def"});
    t("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"});
    t("catsanddog", {"cat", "cats", "and", "sand", "dog"});
//    t("aaaaaaaaaaaaaaaaaaaaaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa"});
//    t("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//      "aaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//      "aaaaaaaaaaaaaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa",
//            "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
}

}