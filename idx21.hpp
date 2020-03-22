#pragma once

#include <queue>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex21 {

/**
 ///////////// 211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:
 - void addWord(word)
 - bool search(word)
search(word) can search a literal word or a regular expression string containing
 only letters a-z or .. A . means it can represent any one letter.

Example:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
 **
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);

 OPTIMISE:
    BFS
 */
class WordDictionary {
private:
    struct TrieNode {
        explicit TrieNode(char value) : v(value) {
            for (auto& next : nexts) {
                next = nullptr;
            }
        }

        std::set<int> any_idxs;
        TrieNode* nexts[26]{nullptr};
        char v = 0;
        bool end = false;
    };

public:
    /** Initialize your data structure here. */
    WordDictionary() = default;

    /** Adds a word into the data structure. */
    void addWord(std::string word) {
        TrieNode* p = &root;
        for (char c : word) {
            c -= 'a';
            if (p->nexts[c] == nullptr) {
                p->nexts[c] = new TrieNode(c);
            }
            p->any_idxs.emplace(c);
            p = p->nexts[c];
        }
        p->end = !word.empty();
    }

    bool search(std::string word, int start, TrieNode* p) {
        for (size_t i = start; i < word.size(); ++i) {
            char c = word[i];
            if (c == '.') {
                for (auto& next : p->nexts) {
                    if (next == nullptr) {
                        continue;
                    }
                    if (search(word, i + 1, next)) {
                        return true;
                    }
                }
                return false;
            }

            c -= 'a';
            if (p->nexts[c] == nullptr) {
                return false;
            }
            p = p->nexts[c];
        }
        return p != nullptr && p->end;
    }

    /** Returns if the word is in the data structure.
     * A word could contain the dot character '.' to represent any one letter. */
    bool search(std::string word) {
        return search(word, 0, &root);
    }

private:
    TrieNode root{'\0'};
};

FTEST(test_WordDictionary) {
    WordDictionary dict;
    dict.addWord("trie");
    FEXP(dict.search("trie"), true);
    FEXP(dict.search("trid"), false);
    FEXP(dict.search(".rie"), true);
    FEXP(dict.search("t.ie"), true);
    FEXP(dict.search("tr.e"), true);
    FEXP(dict.search("...."), true);
    FEXP(dict.search("tri."), true);

    dict.addWord("ran");
    dict.addWord("rune");
    dict.addWord("runner");
    dict.addWord("runs");
    FEXP(dict.search("r.n"), true);
}

/**
 ///////////// 212. Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell,
 where "adjacent" cells are those horizontally or vertically neighboring.
 The same letter cell may not be used more than once in a word.

Example:
Input:
board = [
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Note:
All inputs are consist of lowercase letters a-z.
The values of words are distinct.
 */
std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
        std::vector<std::string>& words) {
    if (board.empty() || board.front().empty()) {
        return {};
    }
    size_t row = board.size();
    size_t col = board.front().size();

    TrieNode root('\0');
    auto add_func = [&](const std::string& word) {
        TrieNode* p = &root;
        for (char c : word) {
            c -= 'a';
            if (p->nexts[c] == nullptr) {
                p->nexts[c] = new TrieNode(c);
            }
            p = p->nexts[c];
        }
        p->end = true;
    };

    std::string re;
    std::vector<std::string> res;
    std::function<void(int, int, TrieNode*)> r_func;
    r_func = [&](int x, int y, TrieNode* p) {
        if (x < 0 || x >= row || y < 0 || y >= col || p == nullptr || board[x][y] == '#') {
            return;
        }
        int c = board[x][y] - 'a';
        if (p->nexts[c] == nullptr) {
            return;
        }

        re += board[x][y];
        board[x][y] = '#';
        if (p->nexts[c]->end) {
            p->nexts[c]->end = false; // deduplicate
            res.emplace_back(re);
        }

        p = p->nexts[c];
        r_func(x, y + 1, p);
        r_func(x, y - 1, p);
        r_func(x + 1, y, p);
        r_func(x - 1, y, p);

        re.pop_back();
        board[x][y] = c + 'a';
    };
    for (auto& word : words) {
        add_func(word);
    }
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            r_func(i, j, &root);
        }
    }
    return res;
}

FTEST(test_findWords) {
    std::vector<std::vector<char>> board = {
            {'o', 'a', 'a', 'n'},
            {'e', 't', 'a', 'e'},
            {'i', 'h', 'k', 'r'},
            {'i', 'f', 'l', 'v'}
    };
    auto t = [&](const std::vector<std::string>& words) {
        std::vector<std::string> nns = words;
        auto re = findWords(board, nns);
        LOG(INFO) << words << " find: " << re;
        return re;
    };

    t({"oath", "pea", "eat", "rain"});
    t({"oath", "oat", "pea", "eat", "rain"});

    board = {{'a', 'a'}};
    t({"a"});

    board = {{'a', 'a', 'a'}};
    t({"a"});
}

/**
 ///////////// 213. House Robber II
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed. All houses at this place are arranged in a circle.
That means the first house is the neighbor of the last one.
 Meanwhile, adjacent houses have security system connected and it will automatically
 contact the police if two adjacent houses were broken into on the same night.
Given a list of non-negative integers representing the amount of money of each house,
 determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.

Example 2:
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
 */
int robII(std::vector<int>& nums) {
    size_t len = nums.size();
    if (len <= 2) {
        return len == 0 ? 0 : (len == 1 ? nums[0] : std::max(nums[0], nums[1]));
    }
    auto robI = [&](int start, int end) {
        int dp1 = nums[start];
        int dp2 = std::max(nums[start], nums[start + 1]);
        for (int i = start + 2; i < end; ++i) {
            int n = std::max(dp1 + nums[i], dp2);
            dp1 = dp2;
            dp2 = n;
        }
        return std::max(dp1, dp2);
    };
    return std::max(robI(0, len - 1), robI(1, len));
}

FTEST(test_robII) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = robII(nns);
        LOG(INFO) << nums << " robII max " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 1);
    FEXP(t({1, 2}), 2);
    FEXP(t({2, 1}), 2);
    FEXP(t({1, 2, 3}), 3);
    FEXP(t({1, 3, 2}), 3);
    FEXP(t({2, 1, 3}), 3);
    FEXP(t({2, 3, 1}), 3);
    FEXP(t({3, 1, 2}), 3);
    FEXP(t({3, 2, 1}), 3);
    FEXP(t({2, 3, 2}), 3);
    FEXP(t({1, 2, 3, 1}), 4);
    FEXP(t({2, 7, 9, 3, 1}), 11);
}

/**
 ///////////// 214. Shortest Palindrome
Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it.
 Find and return the shortest palindrome you can find by performing this transformation.

Example 1:
Input: "aacecaaa"
Output: "aaacecaaa"

Example 2:
Input: "abcd"
Output: "dcbabcd"
 */
std::string shortestPalindrome(std::string s) {
    size_t len = s.size();
    int i = 0;
    for (int j = len - 1; j >= 0; --j) {
        if (s[i] == s[j]) {
            ++i;
        }
    }
    if (i == len) {
        return s;
    }
    std::string prefix = s.substr(i);
    std::reverse(prefix.begin(), prefix.end());
    return prefix + shortestPalindrome(s.substr(0, i)) + s.substr(i);
}

FTEST(test_shortestPalindrome) {
    auto t = [](const std::string& str) {
        auto re = shortestPalindrome(str);
        LOG(INFO) << str << " to palindrom: " << re;
        return re;
    };

    t("");
    FEXP(t("a"), "a");
    FEXP(t("aa"), "aa");
    FEXP(t("aba"), "aba");
    FEXP(t("ab"), "bab");
    FEXP(t("aacecaaa"), "aaacecaaa");
    FEXP(t("abcd"), "dcbabcd");
}

/**
 ///////////// 215. Kth Largest Element in an Array
Find the kth largest element in an unsorted array.
 Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:
Input: [3,2,1,5,6,4] and k = 2
Output: 5

Example 2:
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.
 */
int findKthLargest(std::vector<int>& nums, int k) {
    auto quick_sort_func = [&] {
        auto partition = [&nums](int left, int r) {
            if (left >= r) {
                return r;
            }
            int pivot = nums[left];
            int l = left + 1;
            while (l <= r) {
                if (nums[l] < pivot && pivot < nums[r]) {
                    // there must be three(l, pivot, r) number exist
                    // that ensure would out of range after l++, r--.
                    std::swap(nums[l++], nums[r--]);
                }
                if (pivot >= nums[r]) {
                    --r;
                }
                if (nums[l] >= pivot) {
                    ++l;
                }
            }
            std::swap(nums[left], nums[r]);
            return r;
        };

        size_t len = nums.size();
        int l = 0;
        int r = len - 1;
        while (l <= r) {
            int pos = partition(l, r);
            if (pos == k - 1) {
                return nums[pos];
            } else if (pos < k - 1) {
                l = pos + 1;
            } else { // pos > k - 1
                r = pos - 1;
            }
        }
        return (len == 0 || l >= len) ? -1 : nums[l];
    };
    auto heap_func = [&] {
        if (k == 0 || k > nums.size()) {
            return -1;
        }
        std::priority_queue<int> qq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; ++i) {
            qq.pop();
        }
        return qq.top();
    };
    return heap_func();
}

FTEST(test_findKthLargest) {
    auto t = [&](const std::vector<int>& nums, int k) {
        std::vector<int> nns = nums;
        auto re = findKthLargest(nns, k);
        LOG(INFO) << nums << " find " << k << "th: " << re;
        return re;
    };

    FEXP(t({}, 0), -1);
    FEXP(t({}, 1), -1);
    FEXP(t({1}, 1), 1);
    FEXP(t({1}, 2), -1);
    FEXP(t({1, 2}, 1), 2);
    FEXP(t({1, 2}, 2), 1);
    FEXP(t({2, 1}, 1), 2);
    FEXP(t({2, 1}, 2), 1);
    FEXP(t({1, 2, 3}, 1), 3);
    FEXP(t({1, 2, 3}, 2), 2);
    FEXP(t({1, 2, 3}, 3), 1);
    FEXP(t({3, 2, 1}, 1), 3);
    FEXP(t({3, 2, 1}, 2), 2);
    FEXP(t({3, 2, 1}, 3), 1);
    FEXP(t({3, 1, 2}, 1), 3);
    FEXP(t({3, 1, 2}, 2), 2);
    FEXP(t({3, 1, 2}, 3), 1);
    FEXP(t({3, 2, 1, 5, 6, 4}, 2), 5);
    FEXP(t({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4), 4);
}

/**
 ///////////// 216. Combination Sum III
Find all possible combinations of k numbers that add up to a number n,
 given that only numbers from 1 to 9 can be used and each combination should
 be a unique set of numbers.

Note:
All numbers will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
 */
std::vector<std::vector<int>> combinationSum3(int k, int n) {
    return {};
}

/**
 ///////////// 217. Contains Duplicate
Given an array of integers, find if the array contains any duplicates.
Your function should return true if any value appears at least twice in the array,
 and it should return false if every element is distinct.

Example 1:
Input: [1,2,3,1]
Output: true

Example 2:
Input: [1,2,3,4]
Output: false

Example 3:
Input: [1,1,1,3,3,4,3,2,4,2]
Output: true

 TODO...
 bit trie

 */
bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> mm;
    for (int num : nums) {
        if (mm.count(num) == 1) {
            return true;
        }
        mm.emplace(num);
    }
    return false;
}

FTEST(test_containsDuplicate) {
    auto t = [&](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = containsDuplicate(nns);
        LOG(INFO) << nums << " contains duplicate: " << re;
        return re;
    };

    FEXP(t({}), false);
    FEXP(t({1}), false);
    FEXP(t({1, 2}), false);
    FEXP(t({1, 1}), true);
    FEXP(t({1, 1, 2}), true);
    FEXP(t({1, 2, 1}), true);
    FEXP(t({2, 1, 1}), true);
    FEXP(t({1, 2, 3, 1}), true);
    FEXP(t({1, 2, 3, 4}), false);
    FEXP(t({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}), true);
    FEXP(t({1, 10, 1, 3, 3, 4, 3, 2, 4, 2}), true);
    FEXP(t({1, 5, -2, -4, 0}), false);
    FEXP(t({0, 4, 5, 0, 3, 6}), true);
    FEXP(t({0, 4, 5, 10, 3, 6}), false);
    FEXP(t({10, 4, 5, 10, 3, 6}), true);
}

/**
 ///////////// 218. The Skyline Problem
A city's skyline is the outer contour of the silhouette formed by all the buildings in
 that city when viewed from a distance. Now suppose you are given the locations
 and height of all the buildings as shown on a cityscape photo (Figure A),
 write a program to output the skyline formed by these buildings collectively (Figure B).
TODO.. figure

Buildings Skyline Contour
The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi],
 where Li and Ri are the x coordinates of the left and right edge of the ith building,
 respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX,
 and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded
 on an absolutely flat surface at height 0.
For instance, the dimensions of all buildings in Figure A are recorded as:
 [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .
The output is a list of "key points" (red dots in Figure B) in the format of
 [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline.
 A key point is the left endpoint of a horizontal line segment.
 Note that the last key point, where the rightmost building ends,
 is merely used to mark the termination of the skyline, and always has zero height.
 Also, the ground in between any two adjacent buildings should be considered
 part of the skyline contour.
For instance, the skyline in Figure B should be represented as:
 [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:
The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline.
 For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
 the three lines of height 5 should be merged into one in the final
 output as such: [...[2 3], [4 5], [12 7], ...]

THOUGHTS:
    Sort start edge and end edge as below RULE:
    1. for start edge, when x equal, height at descent order, make value to negative is a easy way.
    2. for end edge, when x equal, height asend order

    There is a multi priority_queue record current max height.
    We put start edge in it, and pop queue when end edge occured.
    Once height changed, record a node with queue top value as height.
    RULE_1 make sure start edge as higher as possible
    RULE_2 make sure end edge as lower as possible
        which avoid duplicated height changing cause duplicated result.
 */
std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
    std::vector<std::pair<int, int>> vv;
    for (auto& building : buildings) {
        vv.emplace_back(building[0], -building[2]); // start when x equal, height descent order
        vv.emplace_back(building[1], building[2]);     // end when x equal, height asend order
    }
    std::sort(vv.begin(), vv.end());
    std::vector<std::vector<int>> res;
    std::multiset<int> qq;
    qq.emplace(0);
    for (auto& v : vv) {
        int pre = *(qq.rbegin());
        if (v.second < 0) {                 // start edge
            qq.emplace(-v.second);
        } else {                            // end edge
            qq.erase(qq.find(v.second));    // delete first one
        }
        int top = *qq.rbegin();
        if (pre != top) {
            res.emplace_back(std::vector<int>{v.first, top});
        }
    }
    return res;
}

FTEST(test_getSkyline) {
    auto t = [&](const std::vector<std::vector<int>>& buildings) {
        std::vector<std::vector<int>> nns = buildings;
        auto re = getSkyline(nns);
        LOG(INFO) << buildings << " get skylines: " << re;
        return re;
    };

    t({{0, 2, 3}, {2, 5, 3}});
    t({{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
}

/**
 ///////////// 219. Contains Duplicate II
Given an array of integers and an integer k,
 find out whether there are two distinct indices i and j in the array such
 that nums[i] = nums[j] and the absolute difference between i and j is at most k.

Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false
 */
bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
    return false;
}

/**
 ///////////// 220. Contains Duplicate III
Given an array of integers, find out whether there are two distinct indices i
 and j in the array such that the absolute difference between nums[i]
 and nums[j] is at most t and the absolute difference between i and j is at most k.

Example 1:
Input: nums = [1,2,3,1], k = 3, t = 0
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1, t = 2
Output: true

Example 3:
Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false
 */
bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int k, int t) {
    return false;
}

}