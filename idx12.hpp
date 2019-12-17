#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

typedef LCListNode ListNode;
typedef LCNode Node;

/**
 ///////////// 121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction
 (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
Note that you cannot sell a stock before you buy one.

Example 1:
Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/
int maxProfit(std::vector<int>& prices) {
    int buy = INT_MAX;
    int res = 0;
    for (auto price : prices) {
        buy = std::min(buy, price);
        res = std::max(res, price - buy);
    }
    return res;
}

FTEST(test_maxProfit) {
    auto t = [](const std::vector<int>& prices) {
        std::vector<int> nns = prices;
        auto re = maxProfit(nns);
        LOG(INFO) << prices << " max profit: \n" << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 0);
    FEXP(t({1, 1}), 0);
    FEXP(t({1, 2}), 1);
    FEXP(t({2, 1}), 0);
    FEXP(t({0, 1, 2}), 2);
    FEXP(t({1, 0, 2}), 2);
    FEXP(t({7, 6, 4, 3, 1}), 0);
    FEXP(t({7, 1, 5, 3, 6, 4}), 5);
    FEXP(t({3, 2, 6, 5, 0, 3}), 4);
}

/**
 ///////////// 122. Best Time to Buy and Sell Stock II
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit.
 You may complete as many transactions as you like
 (i.e., buy one and sell one share of the stock multiple times).
Note: You may not engage in multiple transactions at the same time
 (i.e., you must sell the stock before you buy again).

Example 1:
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

Example 2:
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/
int maxProfitII(std::vector<int>& prices) {
    int res = 0;
    int len = prices.size() - 1;
    for (int i = 0; i < len; ++i) {
        if (prices[i] < prices[i + 1]) {
            res += prices[i + 1] - prices[i];
        }
    }
    return res;
}

FTEST(test_maxProfitII) {
    auto t = [](const std::vector<int>& prices) {
        std::vector<int> nns = prices;
        auto re = maxProfitII(nns);
        LOG(INFO) << prices << " max profit: \n" << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 0);
    FEXP(t({1, 1}), 0);
    FEXP(t({1, 2}), 1);
    FEXP(t({2, 1}), 0);
    FEXP(t({0, 1, 2}), 2);
    FEXP(t({1, 0, 2}), 2);
    FEXP(t({7, 6, 4, 3, 1}), 0);
    FEXP(t({7, 1, 5, 3, 6, 4}), 7);
    FEXP(t({1, 2, 3, 4, 5}), 4);
}

/**
 ///////////// 123. Best Time to Buy and Sell Stock III
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note: You may not engage in multiple transactions at the same time
 (i.e., you must sell the stock before you buy again).

Example 1:
Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/
int maxProfitIII(std::vector<int>& prices) {
    return 0;
}

/**
 ///////////// 124. Binary Tree Maximum Path Sum
Given a non-empty binary tree, find the maximum path sum.
For this problem, a path is defined as any sequence of nodes from some starting
 node to any node in the tree along the parent-child connections.
 The path must contain at least one node and does not need to go through the root.

Example 1:
Input: [1,2,3]
       1
      / \
     2   3

Output: 6

Example 2:
Input: [-10,9,20,null,null,15,7]
   -10
   / \
  9  20
    /  \
   15   7

Output: 42
*/
int maxPathSum(TreeNode* root) {
    std::function<int(TreeNode*, int& res)> r_func;
    r_func = [&](TreeNode* p, int& res) {
        if (p == nullptr) {
            return 0;
        }
        int left = std::max(r_func(p->left, res), 0);
        int right = std::max(r_func(p->right, res), 0);
        res = std::max(res, left + right + p->val);
        return std::max(left, right) + p->val;
    };
    int res = INT_MIN;
    r_func(root, res);
    return res;
    // TODO... output path
}

FTEST(test_maxPathSum) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = maxPathSum(tree);
        LOG(INFO) << nodes << " max node path: \n" << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 1);
    FEXP(t({1, 1}), 2);
    FEXP(t({1, 2}), 3);
    FEXP(t({2, 1}), 3);
    FEXP(t({-10, 1}), 1);
    FEXP(t({0, 1, 2}), 3);
    FEXP(t({1, 0, 2}), 3);
    FEXP(t({1, 2, 3}), 6);
    FEXP(t({-10, 9, 20, nullptr, nullptr, 15, 7}), 42);
}

/**
 ///////////// 125. Valid Palindrome
Given a string, determine if it is a palindrome,
 considering only alphanumeric characters and ignoring cases.
Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:
Input: "A man, a plan, a canal: Panama"
Output: true

Example 2:
Input: "race a car"
Output: false
*/
bool isPalindrome(std::string s) {
    int i = 0;
    int j = s.size() - 1;
    while (i < j) {
        while (i < j && !isalnum(s[i])) {
            ++i;
        }
        while (i < j && !isalnum(s[j])) {
            --j;
        }
        if (i >= j) {
            break;
        }
        if ((s[i] | (1 << 5)) != (s[j] | (1 << 5))) {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}

FTEST(test_isPalindromeStr) {
    auto t = [](const std::string& s) {
        auto re = isPalindrome(s);
        LOG(INFO) << s << " is palindrome: " << re;
        return re;
    };

    FEXP(t(""), true);
    FEXP(t(","), true);
    FEXP(t(" "), true);
    FEXP(t(" ,"), true);
    FEXP(t(" , "), true);
    FEXP(t("1"), true);
    FEXP(t("121"), true);
    FEXP(t("122"), false);
    FEXP(t("1a1"), true);
    FEXP(t("1aa"), false);
    FEXP(t("a1A"), true);
    FEXP(t("a,1A"), true);
    FEXP(t("a,1 A"), true);
    FEXP(t("a, 1A"), true);
    FEXP(t("a, 1A"), true);
    FEXP(t("A man, a plan, a canal: Panama"), true);
    FEXP(t("race a car"), false);
}

/**
 ///////////// 126. Word Ladder II
Given two words (beginWord and endWord), and a dictionary's word list,
 find all shortest transformation sequence(s) from beginWord to endWord, such that:
Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Note:
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Example 2:
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []
Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/
std::vector<std::vector<std::string>> findLadders(std::string beginWord, std::string endWord,
        std::vector<std::string>& wordList) {
    return {};
}

/**
 ///////////// 127. Word Ladder
Given two words (beginWord and endWord), and a dictionary's word list,
 find the length of shortest transformation sequence from beginWord to endWord, such that:
Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5
Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Example 2:
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0
Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/
int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    size_t len = beginWord.size();
    if (len == 0 && wordList.empty()) {
        return 1;
    }
    std::unordered_set<std::string> words(wordList.begin(), wordList.end());
    std::vector<std::map<char, std::vector<std::string*>>> mm(len);
    for (auto& word : wordList) {
        for (size_t i = 0; i < len; ++i) {
            mm[i][word[i]].emplace_back(&word);
        }
    }
    std::deque<std::string> qq;
    qq.push_back(beginWord);
    int step = 1;
    while (!qq.empty()) {
        for (size_t qi = qq.size(); qi > 0; --qi) {
            std::string word = qq.front();
            qq.pop_front();
            for (size_t i = 0; i < len; ++i) {
                for (auto& entry : mm[i]) {
                    char c = word[i];
                    word[i] = entry.first;
                    if (word == endWord) {
                        return step + 1;
                    }
                    if (words.count(word) == 1) {
                        qq.push_back(word);
                        words.erase(word);
                    }
                    word[i] = c;
                }
            }
        }
        ++step;
    }
    return 0;
}

FTEST(test_ladderLength) {
    auto t = [](const std::string beginWord, const std::string& endWord,
            const std::vector<std::string>& wordList) {
        std::vector<std::string> nns = wordList;
        auto re = ladderLength(beginWord, endWord, nns);
        LOG(INFO) << beginWord << " to " << endWord << " ladder length: " << re;
        return re;
    };

    FEXP(t("", "", {}), 1);
    FEXP(t("a", "c", {"d"}), 0);
    FEXP(t("a", "c", {"c"}), 2);
    FEXP(t("a", "c", {"a", "b", "c"}), 2);
    FEXP(t("ad", "bc", {"ac", "bc"}), 3);
    FEXP(t("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}), 5);
}

/**
 ///////////// 128. Longest Consecutive Sequence
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.

Example:
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
*/
int longestConsecutive(std::vector<int>& nums) {
    return 0;
}

/**
 ///////////// 129. Sum Root to Leaf Numbers
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.
Note: A leaf is a node with no children.

Example:
Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:
Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
*/
int sumNumbers(TreeNode* root) {
    return 0;
}

/**
 ///////////// 130. Surrounded Regions
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

Explanation:
Surrounded regions shouldn’t be on the border,
 which means that any 'O' on the border of the board are not flipped to 'X'.
 Any 'O' that is not on the border and it is not connected to an 'O' on the
 border will be flipped to 'X'. Two cells are connected if
 they are adjacent cells connected horizontally or vertically.
*/
void solve(std::vector<std::vector<char>>& board) {
}
