#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex43 {

/**
 ///////////// 431.

 */

/**
 ///////////// 432.

 */

/**
 ///////////// 433.

 */


/**
 ///////////// 434.

 */


/**
 ///////////// 435.

 */


/**
 ///////////// 436.

 */


/**
 ///////////// 437. Path Sum III
You are given a binary tree in which each node contains an integer value.
Find the number of paths that sum to a given value.
The path does not need to start or end at the root or a leaf,
 but it must go downwards (traveling only from parent nodes to child nodes).
The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
 */
int pathSumIII(TreeNode* root, int sum) {
    std::map<int, int> nums;
    nums[0] = 1;
    std::function<int(TreeNode*, int)> r_func;
    r_func = [&](TreeNode* p, int cur_sum) {
        if (p == nullptr) {
            return 0;
        }
        cur_sum += p->val;
        int r = nums[cur_sum - sum];
        ++nums[cur_sum];
        r += r_func(p->left, cur_sum) + r_func(p->right, cur_sum);
        --nums[cur_sum];
        return r;
    };
    return r_func(root, 0);
}

FTEST(test_pathSumIII) {
    auto t = [&](const std::vector<TreeNodeStub>& nodes, int sum) {
        TreeNode* tree = create_tree(nodes);
        auto re = pathSumIII(tree, sum);
        LOG(INFO) << "sum " << sum << " count " << re << " of tree\n" << print_tree(tree);
        return re;
    };

    FEXP(t({0, 1, 1}, 1), 4);
    FEXP(t({1, 2, 1}, 2), 2);
    FEXP(t({-2, nullptr, -5}, -5), 1);
    FEXP(t({10, 5, -3, 3, 2, nullptr, 11, 3, -2, nullptr, 1}, 8), 3);
}

/**
 ///////////// 438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.
Strings consists of lowercase English letters only and the length of both strings s
 and p will not be larger than 20,100.
The order of output does not matter.

Example 1:
Input:
s: "cbaebabacd" p: "abc"
Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input:
s: "abab" p: "ab"
Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

THOUGHTS:
    sliding window
    right border move, if(mm[c]-- >= 1) --cnt:
        If chars' count in window larger than input or char not concern,
        cnt dosen't change, and mm[c] will be negative after this line.

    left border move, if(mm[c]++ >= 0) ++cnt:
        Contrary as follow.

   c   b   a   e   b   a   b   a   c   d  | a b c[cnt]
  s,i                                       1 1 1[3] → 1 1 0[2]
   s   i                                    1 0 0[1]
   s → s   i                                0 0 0[0] → 0 0 1[1], add subs(i-start+1) to result
                                                                 move left boder from now.
       s → s   i                            0 0 1[1] → 0 1 1[2], e not concern
           s → s   i                        0 0 1[1] → 1 0 1[2]
               s → s   i                    0 0 1[1] → 0 0 1[1]
                   s → s   i                0 -1 1[1] → 0 0 1[1]
                       s → s   i            -1 0 1[1] → 0 0 1[1]
                           s → s   i        0 0 0[0] → 0 1 0[1], add subs(i-start+1) to result
                               s → s   i    0 1 0[0] → 1 1 0[2]
 */
std::vector<int> findAnagrams(std::string s, std::string p) {
    int mm[26] = {0};
    for (auto& c : p) {
        ++mm[c - 'a'];
    }
    std::vector<int> res;
    size_t count = p.size();
    size_t start = 0;
    size_t i = 0;
    while (i < s.size()) {
        if (mm[s[i++] - 'a']-- >= 1) {
            --count;
        }
        if (count == 0) {
            res.emplace_back(start);
        }
        if (i - start == p.size() && mm[s[start++] - 'a']++ >= 0) {
            ++count;
        }
    }
    return res;
}

FTEST(test_findAnagrams) {
    auto t = [&](const std::string s, const std::string p) {
        auto re = findAnagrams(s, p);
        LOG(INFO) << s << " anagram: " << p << " count: " << re;
        return re;
    };

    t("", "");
    t("", "a");
    t("a", "");
    t("a", "a");
    t("aa", "a");
    t("aa", "aa");
    t("aa", "ab");
    t("aba", "ab");
    t("aab", "ab");
    t("baa", "aa");
    t("abab", "ab");
    t("cbaebabacd", "abc");
    t("cbaebaabcd", "abc");
}

/**
 ///////////// 439.

 */


/**
 ///////////// 440.

 */



}