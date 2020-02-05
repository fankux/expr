#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

namespace LCIndex7 {

/**
 ///////////// 71. Simplify Path
Given an absolute path for a file (Unix-style), simplify it. Or in other words,
 convert it to the canonical path.
In a UNIX-style file system, a period . refers to the current directory. Furthermore,
 a double period .. moves the directory up a level. For more information,
 see: Absolute path vs relative path in Linux/Unix
Note that the returned canonical path must always begin with a slash /,
 and there must be only a single slash / between two directory names.
 The last directory name (if it exists) must not end with a trailing /.
 Also, the canonical path must be the shortest string representing the absolute path.

Example 1:
Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:
Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:
Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:
Input: "/a/./b/../../c/"
Output: "/c"

Example 5:
Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:
Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
*/
std::string simplifyPath(std::string path) {
    std::stack<std::string> ss;
    enum STAT {
        BEGIN = 0,
        SLASH,
        DIR,
        DOT,
        DOUBLE_DOT
    };
    size_t l = 0;
    size_t r = 0;
    int state = BEGIN;
    for (int i = 0; i < path.size(); ++i) {
        char c = path[i];
        switch (state) {
            case BEGIN: {
                if (c == '/') {
                    state = SLASH;
                    break;
                }
                return "";
            }
            case SLASH: {
                if (c == '/') {
                    break;
                }
                if (c == '.') {
                    state = DOT;
                } else {
                    l = i;
                    r = i;
                    state = DIR;
                }
                break;
            }
            case DOT: {
                if (c == '/') {         // /./
                    state = SLASH;
                } else if (c == '.') {
                    state = DOUBLE_DOT;
                } else {
                    state = DIR;
                    l = i - 1;
                    r = i;
                }
                break;
            }
            case DOUBLE_DOT: {
                if (c == '/') {         // /../
                    if (!ss.empty()) {
                        ss.pop();
                    }
                    state = SLASH;
                } else {
                    state = DIR;
                    l = i - 2;
                    r = i;
                }
                break;
            }
            case DIR: {
                if (c == '/') {
                    ss.push(path.substr(l, r - l + 1));
                    state = SLASH;
                    break;
                }
                r = i;
                break;
            }
            default:
                return "";
        }
    }
    if (state == DIR) {
        ss.push(path.substr(l, r - l + 1));
    } else if (state == DOUBLE_DOT && !ss.empty()) {
        ss.pop();
    }
    std::string res;
    while (!ss.empty()) {
        res = "/" + ss.top() + res;
        ss.pop();
    }
    return res.empty() ? "/" : res;
}

FTEST(test_simplifyPath) {
    auto t = [](const std::string& path) {
        auto re = simplifyPath(path);
        LOG(INFO) << path << " simplify: " << re;
        return re;
    };

    FEXP(t("/"), "/");
    FEXP(t("//"), "/");
    FEXP(t("/.."), "/");
    FEXP(t("/../"), "/");
    FEXP(t("/.a"), "/.a");
    FEXP(t("/.a/"), "/.a");
    FEXP(t("/..."), "/...");
    FEXP(t("/.../"), "/...");
    FEXP(t("/...."), "/....");
    FEXP(t("/..../"), "/....");
    FEXP(t("/...a"), "/...a");
    FEXP(t("/...a/"), "/...a");
    FEXP(t("/a"), "/a");
    FEXP(t("/abc"), "/abc");
    FEXP(t("/abc/.."), "/");
    FEXP(t("/abc/../"), "/");
    FEXP(t("/abc/../.."), "/");
    FEXP(t("/abc/../../"), "/");
    FEXP(t("/abc/../../.."), "/");
    FEXP(t("/abc/../../../"), "/");
    FEXP(t("/a/"), "/a");
    FEXP(t("/abc/"), "/abc");
    FEXP(t("//abc"), "/abc");
    FEXP(t("//abc//"), "/abc");
    FEXP(t("/./abc"), "/abc");
    FEXP(t("//./abc"), "/abc");
    FEXP(t("//./abc"), "/abc");
    FEXP(t("/.//abc"), "/abc");
    FEXP(t("/.//abc"), "/abc");
    FEXP(t("//.//abc"), "/abc");
    FEXP(t("//.//abc"), "/abc");
    FEXP(t("/./abc/"), "/abc");
    FEXP(t("/./abc//"), "/abc");
    FEXP(t("/./abc/./"), "/abc");
    FEXP(t("/./abc//./"), "/abc");
    FEXP(t("/./abc/.//"), "/abc");
    FEXP(t("/./abc//.//"), "/abc");
    FEXP(t("/./abc//.//"), "/abc");
    FEXP(t("/home//foo/"), "/home/foo");
    FEXP(t("/a/./b/../../c/"), "/c");
    FEXP(t("/a/../../b/../c//.//"), "/c");
    FEXP(t("/a//b////c/d//././/.."), "/a/b/c");
}

/**
 ///////////// 72. Edit Distance
Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
You have the following 3 operations permitted on a word:
Insert a character
Delete a character
Replace a character

Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

THOUGHTS:
 see VERBOSE dp state transfer
*/
int minDistance(std::string word1, std::string word2) {
    size_t len1 = word1.size();
    size_t len2 = word2.size();
    if (len1 == 0 || len2 == 0) {
        return len1 == 0 ? len2 : len1;
    }
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
    for (size_t i = 0; i <= len1; ++i) {
        dp[i][0] = i;
    }
    for (size_t i = 0; i <= len2; ++i) {
        dp[0][i] = i;
    }
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            dp[i][j] = word1[i - 1] == word2[j - 1] ? dp[i - 1][j - 1] :
                    (std::min(dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1])) + 1);
        }
    }

#ifdef VERBOSE
    printf("\t");
    for (size_t j = 1; j < len2; ++j) {
        printf("%2c\t", word2[j]);
    }
    printf("\n");
    for (size_t i = 1; i < len1; ++i) {
        printf("%2c\t", word1[i]);
        for (size_t j = 1; j < len2; ++j) {
            printf("%2d\t", dp[i][j]);
        }
        printf("\n");
    }
#endif
    return dp[len1][len2];
}

FTEST(test_minDistance) {
    auto t = [](const std::string& word1, const std::string word2) {
        auto re = minDistance(word1, word2);
        LOG(INFO) << word1 << " min distance " << word2 << ": " << re;
        return re;
    };

    FEXP(t("", ""), 0);
    FEXP(t("", "a"), 1);
    FEXP(t("", "ab"), 2);
    FEXP(t("", "abc"), 3);
    FEXP(t("a", ""), 1);
    FEXP(t("ab", ""), 2);
    FEXP(t("abc", ""), 3);
    FEXP(t("abc", "abc"), 0);
    FEXP(t("horse", "ros"), 3);
    FEXP(t("intention", "execution"), 5);
    FEXP(t("sea", "eat"), 2);
    FEXP(t("pneumonoultramicroscopicsilicovolcanoconiosis", "ultramicroscopically"), 27);
}

/**
 ///////////// 73. Set Matrix Zeroes
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:
Input:
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output:
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]

Example 2:
Input:
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output:
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]

Follow up:
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/
void setZeroes(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        return;
    }
    int m = matrix.front().size();
    int n = matrix.size();
    int col_zero = false;
    int row_zero = false;
    for (size_t j = 0; j < m; ++j) {
        if (matrix[0][j] == 0) {
            row_zero = true;
            break;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        if (matrix[i][0] == 0) {
            col_zero = true;
            break;
        }
    }
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < m; ++j) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    for (size_t j = 1; j < m; ++j) {
        if (matrix[0][j] == 0) {
            for (size_t i = 1; i < n; ++i) {
                matrix[i][j] = 0;
            }
        }
    }
    for (size_t i = 1; i < n; ++i) {
        if (matrix[i][0] == 0) {
            for (size_t j = 1; j < m; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    if (row_zero) {
        for (size_t j = 0; j < m; ++j) {
            matrix[0][j] = 0;
        }
    }
    if (col_zero) {
        for (size_t i = 0; i < n; ++i) {
            matrix[i][0] = 0;
        }
    }
}

FTEST(test_setZeroes) {
    auto t = [](const std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> mm = matrix;
        setZeroes(mm);
        LOG(INFO) << matrix << " set zeros: " << mm;
    };
    t({});
    t({{}});
    t({{0}});
    t({{1}});
    t({{0, 0}});
    t({{0, 1}});
    t({{1, 0}});
    t({{1, 1}});
    t({{1, 1, 1}});
    t({{1, 0, 1}});
    t({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});
    t({{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}});
}

/**
 ///////////// 74. Search a 2D Matrix
Write an efficient algorithm that searches for a value in an m x n matrix.
 This matrix has the following properties:
 Integers in each row are sorted from left to right.
 The first integer of each row is greater than the last integer of the previous row.

Example 1:
Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true

Example 2:
Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
Output: false

THOUGHTS:
    binary search with coordinate conversion.
*/
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix.front().empty()) {
        return false;
    }
    size_t m = matrix.front().size();
    size_t n = matrix.size();
    size_t l = 0;
    size_t r = m * n;
    while (l < r) {
        size_t mid = l + (r - l) / 2;
        if (matrix[mid / m][mid % m] < target) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    assert(l == r);
    return l < m * n && matrix[l / m][l % m] == target;
}

FTEST(test_searchMatrix) {
    auto t = [](const std::vector<std::vector<int>>& matrix, int target) {
        std::vector<std::vector<int>> mm = matrix;
        auto re = searchMatrix(mm, target);
        LOG(INFO) << matrix << " search " << target << ": " << re;
        return re;
    };
    FEXP(t({}, 0), false);
    FEXP(t({{}}, 0), false);
    FEXP(t({{1}}, 1), true);
    FEXP(t({{1, 2}}, -1), false);
    FEXP(t({{1, 2}}, 3), false);
    FEXP(t({{1, 2}}, 1), true);
    FEXP(t({{1, 2}}, 2), true);
    FEXP(t({{1}, {3}}, 3), true);
    FEXP(t({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}, 3), true);
    FEXP(t({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}, 13), false);
}

/**
 ///////////// 75. Sort Colors
Given an array with n objects colored red, white or blue, sort them in-place so that objects
 of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
Note: You are not suppose to use the library's sort function for this problem.

Example:
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's,
 then overwrite array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?
*/
void sortColors(std::vector<int>& nums) {
    int l = 0;
    int r = nums.size() - 1;
    for (int i = 0; i <= r; ++i) {
        if (nums[i] == 0) {
            std::swap(nums[l++], nums[i]);
        } else if (nums[i] == 2) {
            std::swap(nums[r--], nums[i--]);
        }
    }
}

FTEST(test_sortColors) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        sortColors(nns);
        LOG(INFO) << nums << " color sorted " << nns;
    };

    t({2, 0, 2, 1, 1, 0});
    t({2, 0, 1});
}

/**
 ///////////// 76. Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain
 all the characters in T in complexity O(n).

Example:
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

Note:
If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.

 THOUGHTS:
  A   D   O   B   E   C   O   D   E   B   A   N   C                              ABC
  1           1       1                                  cnt=0                   111
  0           0       0(r)                               SCN,cnt=3               000
  0(l)        0       0(r)                               CHK,res=ADOBEC,cnt=2    100
(0→1)→l       0       0(r)                               MOV,cnt=2               100
      l       0(-1)   0              -1   0(r)           SCN,cnt=3               0-10
              ------→ 0(l)            0   0(r)           CHK,res=CODEBA,cnt=3    000
                    (0→1)→l                              MOV,cnt=2               001
                          l           0   0       0      SCN,cnt=3               000
                          ----------→ 0(l)0       0      CHK,res=BANC,cnt=3      000

*/
std::string minWindow(std::string s, std::string t) {
    int mm[128] = {0};
    for (char c : t) {
        ++(mm[c]);
    }
    int min_left = -1;
    int min_len = INT_MAX;
    int count = 0;
    size_t l = 0;
    for (size_t r = 0; r < s.size(); ++r) {
        if (--mm[s[r]] >= 0) {       // if c not concern, always negative
            ++count;
        }
        while (count == t.size()) { // all words collected
            if (mm[s[l]] == 0 && r - l + 1 < min_len) {
                min_len = r - l + 1;
                min_left = l;
            }
            if (++mm[s[l]] > 0) {// only when vaild char occured, count modified breaking while loop
                --count;
            }
            ++l;
        }
    }
    return min_left == -1 ? "" : s.substr(min_left, min_len);
}

FTEST(test_minWindow) {
    auto t = [](const std::string& s, const std::string& t) {
        auto re = minWindow(s, t);
        LOG(INFO) << s << " min window of " << t << ": " << re;
        return re;
    };
    FEXP(t("", ""), "");
    FEXP(t("", "A"), "");
    FEXP(t("A", ""), "");
    FEXP(t("A", "A"), "A");
    FEXP(t("A", "AA"), "");
    FEXP(t("A", "AB"), "");
    FEXP(t("AB", "AB"), "AB");
    FEXP(t("AB", "ABC"), "");
    FEXP(t("ABC", "ABC"), "ABC");
    FEXP(t("ADBDCEEABFC", "ABC"), "ABFC");
    FEXP(t("ADOBECODEBANC", "ABC"), "BANC");
    FEXP(t("ABC", "AABBCC"), "");
    FEXP(t("ABAABBBCC", "AABBCC"), "AABBBCC");
    FEXP(t("ADBDCEEABF", "AABBCC"), "");
    FEXP(t("ADBDCEEAAFBBCFCC", "AABBCC"), "AAFBBCFC");
    FEXP(t("ADOBECODEBAN", "AABBCC"), "");
    FEXP(t("ADOBECODEAABANCCCBB", "AABBCC"), "ABANCCCB");
}

/**
 ///////////// 77. Combinations
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
std::vector<std::vector<int>> combine(int n, int k) {
    if (k <= 0) {
        return {};
    }
    std::vector<std::vector<int>> res;
    std::vector<int> re;
    std::function<void(int)> r_func;
    r_func = [&](int start) {
        if (re.size() >= k) {
            res.emplace_back(re);
            return;
        }

        for (size_t i = start; i <= n; ++i) {
            re.emplace_back(i);
            r_func(i + 1);
            re.pop_back();
        }
    };

    auto iter_func = [&] {
        re.resize(k, 0);
        int i = 0;
        while (i >= 0) {
            ++re[i];
            if (re[i] > n) {
                --i;
            } else if (i == k - 1) {
                res.emplace_back(re);
            } else {
                ++i;
                re[i] = re[i - 1];
            }
        }
    };

    iter_func();
    return res;
}

FTEST(test_combine) {
    auto t = [](int n, int k) {
        auto re = combine(n, k);
        LOG(INFO) << n << ", " << k << " combine: " << re;
        return re;
    };
    t(0, 0);
    t(0, 1);
    t(1, 0);
    t(1, 1);
    t(2, 1);
    t(1, 2);
    t(2, 2);
    t(1, 3);
    t(3, 1);
    t(3, 2);
    t(2, 3);
    t(3, 3);
    t(4, 2);
}

/**
 ///////////// 78. Subsets
Given a set of distinct integers, nums, return all possible subsets (the power set).
Note: The solution set must not contain duplicate subsets.

Example:
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

THOUGTHS:
    for each member in result collection, put current index to it and add it to collection.
    example: 1 2 3
    init:   []
    add 1:  [], [1]
    add 2:  [], [1], [2], [1,2]
    add 3:  [], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]

*/
std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    auto recursive_method = [&] {
        std::vector<int> re;
        std::function<void(int, int)> rfunc;
        rfunc = [&](int start, int level) {
            if (re.size() >= level) {
                res.emplace_back(re);
                return;
            }
            for (size_t i = start; i < nums.size(); ++i) {
                re.emplace_back(nums[i]);
                rfunc(i + 1, level);
                re.pop_back();
            }
        };
        for (size_t i = 0; i <= nums.size(); ++i) {
            rfunc(0, i);
        }
        return res;
    };
    auto iter_method = [&] {
        res.emplace_back();
        for (int& num : nums) {
            int len = res.size();
            for (size_t j = 0; j < len; ++j) {
                res.emplace_back(res[j]);
                res.back().emplace_back(num);
            }
        }
        return res;
    };
    return iter_method();
}

FTEST(test_subsets) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = subsets(nns);
        LOG(INFO) << nums << " subsets: " << re;
        return re;
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 1});
    t({1, 1, 2});
    t({1, 1, 2, 2});
}

/**
 ///////////// 79. Word Search
Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell,
 where "adjacent" cells are those horizontally or vertically neighboring.
 The same letter cell may not be used more than once.

Example:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
*/
bool wordExistInMatrix(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board.front().empty() || word.empty()) {
        return false;
    }
    size_t m = board.front().size();
    size_t n = board.size();
    std::function<bool(int, int, size_t)> r_func;
    r_func = [&](int x, int y, size_t idx) {
        if (idx >= word.size()) {
            return true;
        }
        if (x < 0 || x >= n || y < 0 || y >= m) {
            return false;
        }
        char c = board[x][y];
        if (c != word[idx]) {
            return false;
        }

        board[x][y] = '#';
        bool re = r_func(x + 1, y, idx + 1) || r_func(x, y + 1, idx + 1) ||
                r_func(x - 1, y, idx + 1) || r_func(x, y - 1, idx + 1);
        board[x][y] = c;
        return re;
    };
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (board[i][j] == word.front()) {
                if (r_func(i, j, 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}

FTEST(test_wordExistInMatrix) {
    auto t = [](const std::vector<std::vector<char>>& board, const std::string& word) {
        std::vector<std::vector<char>> nns = board;
        auto re = wordExistInMatrix(nns, word);
        LOG(INFO) << board << " exist " << word << ": " << re;
        return re;
    };

    FEXP(t({}, ""), false);
    FEXP(t({{}}, ""), true);
    FEXP(t({{}}, "A"), false);
    FEXP(t({{'A'}}, ""), true);
    FEXP(t({{'A'}}, "A"), true);
    FEXP(t({{'A'}}, "B"), false);
    FEXP(t({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED"), true);
    FEXP(t({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "SEE"), true);
    FEXP(t({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCB"), false);
}

/**
 ///////////// 80. Remove Duplicates from Sorted Array II
Given a sorted array nums, remove the duplicates in-place such that duplicates
 appeared at most twice and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input
 array in-place with O(1) extra memory.

Example 1:
Given nums = [1,1,1,2,2,3],
Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,0,1,1,1,1,2,3,3],
Your function should return length = 7, with the first seven elements of nums being
 modified to 0, 0, 1, 1, 2, 3 and 3 respectively.
It doesn't matter what values are set beyond the returned length.

Clarification:
Confused why the returned value is an integer but your answer is an array?
Note that the input array is passed in by reference, which means modification to
 the input array will be known to the caller as well.

Internally you can think of this:
```
// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```
*/
int removeDuplicatesII(std::vector<int>& nums) {
    size_t i = 0;
    for (int num: nums) {
        if (i < 2 || num > nums[i - 2]) {
            nums[i++] = num;
        }
    }
    return i;
}

FTEST(test_removeDuplicatesII) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = removeDuplicatesII(nns);
        LOG(INFO) << nums << " remove dups size: " << re << ", " << nns;
        return re;
    };

    t({-2147483648, -2147483648, -2147483648, 1, 1, 1, 2});
    t({1, 1, 1, 2, 2, 3});
    t({1, 1, 1, 1, 2, 2, 2, 3});
    t({0, 0, 1, 1, 1, 1, 2, 3, 3});
}

}