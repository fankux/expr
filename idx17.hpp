#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex17 {

/**
 ///////////// 171. Excel Sheet Column Number
Given a column title as appear in an Excel sheet, return its corresponding column number.
For example:
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
    ...

Example 1:
Input: "A"
Output: 1

Example 2:
Input: "AB"
Output: 28

Example 3:
Input: "ZY"
Output: 701
 */
int titleToNumber(std::string s) {
    int res = 0;
    int len = s.size();
    int level = 1;
    for (int i = len - 1; i >= 0; --i) {
        if (i < len - 1) {
            level *= 26;
        }
        res += level * (s[i] - 'A' + 1);
    }
    return res;
}

FTEST(test_titleToNumber) {
    auto t = [](const std::string& s) {
        auto re = titleToNumber(s);
        LOG(INFO) << s << " number: " << re;
        return re;
    };

    FEXP(t(""), 0);
    FEXP(t("A"), 1);
    FEXP(t("B"), 2);
    FEXP(t("Y"), 25);
    FEXP(t("Z"), 26);
    FEXP(t("AA"), 27);
    FEXP(t("AB"), 28);
    FEXP(t("ZY"), 701);
    FEXP(t("ZZ"), 702);
    FEXP(t("AAA"), 703);
}

/**
 ///////////// 172. Factorial Trailing Zeroes
Given an integer n, return the number of trailing zeroes in n!.

Example 1:
Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.

Example 2:
Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.


 THOUGHTS:
 find the count of number 5 when factoring, like:
 10! = 1*2*3*4*5*6*7*8*9*10 = 1*3*4*6*7*8*9* (2*5) * (2*5)
 each 2*5 generate a zero. once 5 exist, there must be 2 exist, so just find 5.
 */
int trailingZeroes(int n) {
    int res = 0;
    while (n != 0) {
        res += n / 5;
        n /= 5;
    }
    return res;
}

/**
 ///////////// 173. Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST).
 Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.

Example:
        7
       / \
      3  15
         / \
        9  20

BSTIterator iterator = new BSTIterator(root);
iterator.next();    // return 3
iterator.next();    // return 7
iterator.hasNext(); // return true
iterator.next();    // return 9
iterator.hasNext(); // return true
iterator.next();    // return 15
iterator.hasNext(); // return true
iterator.next();    // return 20
iterator.hasNext(); // return false

Note:
next() and hasNext() should run in average O(1) time and uses O(h) memory,
 where h is the height of the tree.
You may assume that next() call will always be valid, that is,
 there will be at least a next smallest number in the BST when next() is called.

 **
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 *
 */
class BSTIterator {
public:
    explicit BSTIterator(TreeNode* root) {
        _p = root;
    }

    /** @return the next smallest number */
    int next() {
        while (_p) {
            _qq.push(_p);
            _p = _p->left;
        }
        _p = _qq.top()->right;
        int v = _qq.top()->val;
        _qq.pop();
        return v;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return _p || !_qq.empty();
    }

private:
    TreeNode* _p = nullptr;
    std::stack<TreeNode*> _qq;
};

FTEST(test_BSTIterator) {
    TreeNode* tree = create_tree({7, 3, 15, nullptr, nullptr, 9, 20});
    BSTIterator iterator(tree);
    FEXP(iterator.hasNext(), true); // return true
    FEXP(iterator.next(), 3);    // return 3
    FEXP(iterator.hasNext(), true); // return true
    FEXP(iterator.next(), 7);    // return 7
    FEXP(iterator.hasNext(), true); // return true
    FEXP(iterator.next(), 9);    // return 9
    FEXP(iterator.hasNext(), true); // return true
    FEXP(iterator.next(), 15);    // return 15
    FEXP(iterator.hasNext(), true); // return true
    FEXP(iterator.next(), 20);    // return 20
    FEXP(iterator.hasNext(), false); // return false
}

/**
 ///////////// 174. Dungeon Game
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon.
 The dungeon consists of M x N rooms laid out in a 2D grid.
 Our valiant knight (K) was initially positioned in the top-left room
 and must fight his way through the dungeon to rescue the princess.
The knight has an initial health point represented by a positive integer.
 If at any point his health point drops to 0 or below, he dies immediately.
Some of the rooms are guarded by demons, so the knight loses health (negative integers)
 upon entering these rooms; other rooms are either empty (0's) or contain magic orbs
 that increase the knight's health (positive integers).
In order to reach the princess as quickly as possible,
 the knight decides to move only rightward or downward in each step.
Write a function to determine the knight's minimum initial health so that he is able to
 rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7
 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

| -2(K) | -3  |   3   |
|   -5  | -10 |   1   |
|   10  | 30  | -5(P) |

Note:
The knight's health has no upper bound.
Any room can contain threats or power-ups,
 even the first room the knight enters and the bottom-right room where the princess is imprisoned.

THOUGHTS:
    p       | right |
    bottom  |       |

    if (right or bottom) - p <=0, means next step is positive or health enough
    if (right or bottom) - p >0, means minium health of p = min(right, bottom) - p

 */
int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
    if (dungeon.empty() || dungeon.front().empty()) {
        return 0;
    }
    int n = dungeon.size();
    int m = dungeon.front().size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, INT_MAX));
    dp[n][m - 1] = 1;
    dp[n - 1][m] = 1;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            dp[i][j] = std::max(1, std::min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
        }
    }
    return dp.front().front();
}

FTEST(test_calculateMinimumHP) {
    auto t = [](const std::vector<std::vector<int>>& dungeon) {
        std::vector<std::vector<int>> nns = dungeon;
        auto re = calculateMinimumHP(nns);
        LOG(INFO) << dungeon << " min health: " << re;
        return re;
    };

    FEXP(t({{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}}), 7);
    FEXP(t({{3, -20, 30}, {-3, 4, 0}}), 1);
    FEXP(t({{1, -3, 3}, {0, -2, 0}, {-3, -3, -3}}), 3);
}

/**
 ///////////// 175. IGNORE SQL
 ///////////// 176. IGNORE SQL
 ///////////// 177. IGNORE SQL
 ///////////// 178. IGNORE SQL
 */

/**
 ///////////// 179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:
Input: [10,2]
Output: "210"

Example 2:
Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.
 */
std::string largestNumber(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), [](int a, int b) {
        std::string as = std::to_string(a);
        std::string bs = std::to_string(b);
        return (bs + as) < (as + bs);
    });
    std::string res;
    for (auto& num : nums) {
        res += std::to_string(num);
    }
    return !res.empty() && res.front() == '0' ? "0" : res;
}

FTEST(test_largestNumber) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = largestNumber(nns);
        LOG(INFO) << nums << " max number: " << re;
        return re;
    };
    FEXP(t({1}), "1");
    FEXP(t({1, 2}), "21");
    FEXP(t({2, 1}), "21");
    FEXP(t({10, 2}), "210");
    FEXP(t({3, 30, 34, 5, 9}), "9534330");
    FEXP(t({0}), "0");
    FEXP(t({0, 0}), "0");
    FEXP(t({0, 0, 0}), "0");
}

/**
 ///////////// 180. IGNORE SQL
 */
}