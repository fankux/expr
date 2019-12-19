#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex13 {

typedef LCListNode ListNode;
typedef GraphNode Node;

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
    return 0;
}

/**
 ///////////// 133. Clone Graph
Given a reference of a node in a connected undirected graph,
 return a deep copy (clone) of the graph. Each node in the graph
 contains a val (int) and a list (List[Node]) of its neighbors.

Example:
TODO.. graph

Input:
{"$id":"1","neighbors":[{"$id":"2","neighbors":[{"$ref":"1"},{"$id":"3","neighbors":[{"$ref":"2"},{"$id":"4","neighbors":[{"$ref":"3"},{"$ref":"1"}],"val":4}],"val":3}],"val":2},{"$ref":"4"}],"val":1}

Explanation:
Node 1's value is 1, and it has two neighbors: Node 2 and 4.
Node 2's value is 2, and it has two neighbors: Node 1 and 3.
Node 3's value is 3, and it has two neighbors: Node 2 and 4.
Node 4's value is 4, and it has two neighbors: Node 1 and 3.

Note:
The number of nodes will be between 1 and 100.
The undirected graph is a simple graph, which means no repeated edges and no self-loops in the graph.
Since the graph is undirected, if node p has node q as neighbor, then node q must have node p as neighbor too.
You must return the copy of the given node as a reference to the cloned graph.
*/
Node* cloneGraph(Node* node) {
    return nullptr;
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
*/
int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    return 0;
}

/**
 ///////////// 135. Candy
There are N children standing in a line. Each child is assigned a rating value.
You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

Example 1:
Input: [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
             The third child gets 1 candy because it satisfies the above two conditions.
*/
int candy(std::vector<int>& ratings) {
    return 0;
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
    return 0;
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
    return 0;
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
TODO.. graph

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:
TODO.. graph

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:
TODO.. graph

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
    return nullptr;
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
    return false;
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
    return {};
}

}