#pragma once

#include <assert.h>
#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"

/**
 ///////////// 91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:
Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
int numDecodings(std::string s) {
    if (s.empty() || s[0] == '0') {
        return 0;
    }
    std::function<int(size_t)> recursive_func;
    recursive_func = [&](size_t start) {
        if (start >= s.size()) {
            return 1;
        }
        if (s[start] == '0') {
            return 0;
        }
        int res = 0;
        if (start + 1 < s.size()) {
            int code = std::strtoul(s.substr(start, 2).c_str(), nullptr, 10);
            if (code > 0 && code <= 26) {
                res += recursive_func(start + 2);
            }
        }
        return res + recursive_func(start + 1);
    };
    auto dp_func = [&] {
        size_t len = s.size();
        std::vector<int> dp(len + 1, 0); // len+1 for end state handle
        dp[0] = 1;
        for (size_t i = 1; i < len + 1; ++i) {
            dp[i] = s[i - 1] == '0' ? 0 : dp[i - 1];
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] += dp[i - 2];
            }
        }
        return dp.back();
    };
    return dp_func();
}

FTEST(test_numDecodings) {
    auto t = [](const std::string& s) {
        auto re = numDecodings(s);
        LOG(INFO) << s << " decode ways: " << re;
        return re;
    };
    FEXP(t(""), 0);
    FEXP(t("01"), 0);
    FEXP(t("1"), 1);
    FEXP(t("10"), 1);
    FEXP(t("11"), 2);
    FEXP(t("20"), 1);
    FEXP(t("25"), 2);
    FEXP(t("26"), 2);
    FEXP(t("27"), 1);
    FEXP(t("225"), 3);
    FEXP(t("226"), 3);
    FEXP(t("227"), 2);
    FEXP(t("026"), 0);
    FEXP(t("206"), 1);
    FEXP(t("1226"), 5);
    FEXP(t("1227"), 3);
    FEXP(t("1787897759966261825913315262377298132516969578441236833255596967132573482281598412163216914566534565"),
            3);
}

/**
 ///////////// 92. Reverse Linked List II
Reverse a linked list from position m to n. Do it in one-pass.
Note: 1 ≤ m ≤ n ≤ length of list.

Example:
Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

THOUGHTS:
    1  → [2  →  3  →  4] →  5  →  NULL, m=2, n=4
    f     p                             i=1
       1 ↘   pre↘
 null  ← [2  ←  3  →  4] →  5  →  NULL
  pre     p   next
        pre ↘-→ p                       i=2
       1 ↘
 null  ← [2  ←  3  ←  4] →  5  →  NULL
         pre    p   next
              pre ↘-→ p                 i=3
 null  ← [2  ←  3  ←  4] →  5  →  NULL
               pre    p   next
                    pre ↘-→ p           i=4
    1  → [4  →  3  →  2] →  5  →  NULL
    f     pre               p

 reverse from head:
   [4  →  3  →  2  →  1] →  5  →  NULL
 f  pre             head    p

 reverse all:
   [1  ←  2  ←  3  ←  4  →  5] →  NULL
                     pre    p   next
                          pre ↘-→ p     i=5
   [5  →  4  →  3  →  2  →  1] →  NULL
 f  p               pre   head    next

*/
ListNode* reverseBetween(ListNode* head, int m, int n) {
    int i = 1;
    ListNode* p = head;
    ListNode* pre = nullptr;
    while (p && i < m) {
        pre = p;
        p = p->next;
        ++i;
    }
    while (p && p->next && i < n) {
        ListNode* next = p->next;
        p->next = next->next;
        next->next = (pre ? pre->next : head);
        (pre ? pre->next : head) = next;
        ++i;
    }
    return head;
}

FTEST(test_reverseBetween) {
    auto t = [](const std::vector<int>& nums, int m, int n) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        ListNode* re = reverseBetween(list, m, n);
        LOG(INFO) << nums << " reverse between " << m << ", " << n << ": ";
        print_list(re);
    };

    t({}, 0, 0);
    t({1}, 0, 1);
    t({1}, 1, 1);
    t({1, 2}, 1, 1);
    t({1, 2}, 2, 2);
    t({1, 2}, 1, 2);
    t({1, 2, 3}, 1, 1);
    t({1, 2, 3}, 2, 2);
    t({1, 2, 3}, 3, 3);
    t({1, 2, 3}, 1, 2);
    t({1, 2, 3}, 2, 3);
    t({1, 2, 3}, 1, 3);
    t({1, 2, 3, 4}, 1, 2);
    t({1, 2, 3, 4}, 2, 3);
    t({1, 2, 3, 4}, 1, 3);
    t({1, 2, 3, 4, 5}, 1, 2);
    t({1, 2, 3, 4, 5}, 2, 3);
    t({1, 2, 3, 4, 5}, 1, 3);
}

/**
 ///////////// 93. Restore IP Addresses
Given a string containing only digits,
 restore it by returning all possible valid IP address combinations.

Example:
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
*/
std::vector<std::string> restoreIpAddresses(std::string s) {
    int len = s.size();
    std::vector<std::string> res;
    std::vector<int> re;
    std::function<void(int, int)> r_func;
    r_func = [&](int idx, int section) {
        if (idx >= len || section >= 4) {
            if (idx >= len && section >= 4) {
                res.emplace_back();
                for (int i = 0; i < re.size(); ++i) {
                    res.back() += std::to_string(re[i]);
                    if (i != 3) {
                        res.back() += '.';
                    }
                }
            }
            return;
        }
        for (int i = 0; i < 3; ++i) {
            if (idx + i >= len) {
                break;
            }
            uint32_t code_n = strtoul(s.substr(idx, i + 1).c_str(), nullptr, 10);
            if ((code_n <= 255 && code_n > 0 && s[idx] != '0') || (code_n == 0 && i == 0)) {
                re.emplace_back(code_n);
                r_func(idx + i + 1, section + 1);
                re.pop_back();
            }
        }
    };
    r_func(0, 0);
    return res;
}

FTEST(test_restoreIpAddresses) {
    auto t = [](const std::string& s) {
        auto re = restoreIpAddresses(s);
        LOG(INFO) << s << " restore ip: " << re;
    };

    t("");
    t("0");
    t("1");
    t("11");
    t("101");
    t("111");
    t("255");
    t("256");
    t("2550");
    t("2551");
    t("2555");
    t("2556");
    t("25525511135");
    t("010010");
}

/**
 ///////////// 94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

Example:
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
Follow up: Recursive solution is trivial, could you do it iteratively?
*/
std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> res;
    auto iter_func = [&] {
        std::stack<TreeNode*> ss;
        while (!ss.empty() || root) {
            while (root) {
                ss.push(root);
                root = root->left;
            }
            root = ss.top();
            res.emplace_back(root->val);
            ss.pop();
            root = root->right;
        }
    };
    auto morris_func = [&] {
        while (root) {
            if (root->left == nullptr) {
                res.emplace_back(root->val);
                root = root->right;
                continue;
            }
            TreeNode* pre = root->left;
            while (pre->right && pre->right != root) {
                pre = pre->right;
            }
            if (pre->right == root) {
                res.emplace_back(root->val);
                pre->right = nullptr;
                root = root->right;
            } else {
                assert(pre->right == nullptr);
                pre->right = root;
                root = root->left;
            }
        }
    };
    morris_func();
    return res;
}

FTEST(test_inorderTraversal) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* tree = create_tree(nodes);
        auto re = inorderTraversal(tree);
        LOG(INFO) << nodes << " in order traversal: " << re;
    };

    t({1, nullptr, 2, 3});
    t({5, 1, 4, nullptr, nullptr, 3, 6});
}

/**
 ///////////// 95. Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees) that
 store values 1 ... n.

Example:
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
std::vector<TreeNode*> generateBSTrees(int n) {
    if (n <= 0) {
        return {};
    }
    std::map<int64_t, std::vector<TreeNode*>> mm;
    std::function<std::vector<TreeNode*>(int, int)> r_func;
    r_func = [&](int start, int end) {
        if (start > end) {
            return std::vector<TreeNode*>{nullptr};
        }
        int64_t k = ((int64_t) start << 32) | end;
        auto entry = mm.find(k);
        if (entry != mm.end()) {
            return entry->second;
        }
        std::vector<TreeNode*> re;
        for (int i = start; i <= end; ++i) {
            auto left = r_func(start, i - 1);
            auto right = r_func(i + 1, end);
            for (auto& l : left) {
                for (auto& r : right) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    re.emplace_back(root);
                }
            }
        }
        return mm[k] = re;
    };
    return r_func(1, n);
}

FTEST(test_generateBSTrees) {
    auto t = [](int n) {
        auto re = generateBSTrees(n);
        LOG(INFO) << n << " BSTrees: ";
        for (auto t : re) {
            LOG(INFO) << "tree:" << output_tree(t) << ": \n" << print_tree(t);
        }
    };

    t(0);
    t(1);
    t(2);
    t(3);
    t(4);
}

/**
 ///////////// 96. Unique Binary Search Trees
Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:
Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
int numBSTrees(int n) {
    if (n <= 0) {
        return 1;
    }
    std::vector<int> dp(n, 0);
    dp[0] = 1;
    for (size_t i = 1; i < n; ++i) {
        dp[i] = 0;
        for (size_t j = 1; j < (i + 1) / 2; ++j) {
            dp[i] += dp[j - 1] * dp[i - j - 1];
        }
        dp[i] = dp[i] * 2 + dp[i - 1] * 2;
        dp[i] += (i % 2 == 0) ? dp[i / 2 - 1] * dp[i / 2 - 1] : 0;
    }
    return dp.back();
}

FTEST(test_numBSTrees) {
    auto t = [](int n) {
        auto re = numBSTrees(n);
        LOG(INFO) << n << " numbers of BST: " << re;
        return re;
    };

    FEXP(t(0), 1);
    FEXP(t(1), 1);
    FEXP(t(2), 2);
    FEXP(t(3), 5);
    FEXP(t(4), 14);
    FEXP(t(5), 42);
    FEXP(t(6), 132);
    FEXP(t(7), 429);
}

/**
 ///////////// 97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
*/
bool isInterleave(std::string s1, std::string s2, std::string s3) {
    size_t len1 = s1.size();
    size_t len2 = s2.size();
    if (len1 + len2 != s3.size()) {
        return false;
    }
    std::vector<std::vector<bool>> dp(len1 + 1, std::vector<bool>(len2 + 1, false));
    dp[0][0] = true;
    for (size_t i = 1; i <= len1; ++i) {
        dp[i][0] = s1[i - 1] == s3[i - 1] && dp[i - 1][0];
    }
    for (size_t j = 1; j <= len2; ++j) {
        dp[0][j] = s2[j - 1] == s3[j - 1] && dp[0][j - 1];
    }
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            dp[i][j] = (s3[i + j - 1] == s1[i - 1] && dp[i - 1][j]) ||
                    (s3[i + j - 1] == s2[j - 1] && dp[i][j - 1]);
        }
    }
    return dp.back().back();
}

FTEST(test_isInterleave) {
    auto t = [](const std::string& s1, const std::string& s2, const std::string& s3) {
        auto re = isInterleave(s1, s2, s3);
        LOG(INFO) << s1 << ", " << s2 << " is interleaving of " << s3 << ": " << re;
        return re;
    };

//    FEXP(t("", "", ""), true);
//    FEXP(t("1", "", ""), false);
//    FEXP(t("", "1", ""), false);
//    FEXP(t("", "", "1"), false);
//    FEXP(t("1", "", "1"), true);
//    FEXP(t("", "1", "1"), true);
//    FEXP(t("aabcc", "dbbca", "aadbbcbcac"), true);
//    FEXP(t("aabcc", "dbbca", "aadbbbaccc"), false);
    FEXP(t("aabc", "abad", "aabadabc"), true);
}

/**
 ///////////// 98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
    2
   / \
  1   3
Input: [2,1,3]
Output: true

Example 2:
    5
   / \
  1   4
     / \
    3   6
Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/
bool isValidBST(TreeNode* root) {
    auto morris_func = [&] {
        TreeNode* p = nullptr;
        bool res = true;
        while (root) {
            if (root->left == nullptr) {
                if (p && p->val >= root->val) {
                    res = false;
                }
                p = root;
                root = root->right;
                continue;
            }
            TreeNode* pre = root->left;
            while (pre->right && pre->right != root) {
                pre = pre->right;
            }
            if (pre->right == root) {
                if (p && p->val >= root->val) {
                    res = false;
                }
                p = root;
                pre->right = nullptr;
                root = root->right;
            } else {
                assert(pre->right == nullptr);
                pre->right = root;
                root = root->left;
            }
        }
        return res;
    };

    std::function<bool(TreeNode*, int64_t, int64_t)> r_func;
    r_func = [&](TreeNode* root, int64_t mn, int64_t mx) {
        if (!root) {
            return true;
        }
        if (root->val <= mn || root->val >= mx) {
            return false;
        }
        return r_func(root->left, mn, root->val) && r_func(root->right, root->val, mx);
    };
    return r_func(root, INT64_MIN, INT64_MAX);
}

FTEST(test_isValidBST) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* root = create_tree(nodes);
        auto re = isValidBST(root);
        LOG(INFO) << nodes << " is BST: " << re;
        return re;
    };
    FEXP(t({5, 1, 4, nullptr, nullptr, 3, 6}), false);
    FEXP(t({10, 5, 15, nullptr, nullptr, 6, 20}), false);
    FEXP(t({2147483647}), true);
}

/**
 ///////////// 99. Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

Example 1:
Input: [1,3,null,null,2]
   1
  /
 3
  \
   2
Output: [3,1,null,null,2]
   3
  /
 1
  \
   2

Example 2:
Input: [3,1,4,null,null,2]
  3
 / \
1   4
   /
  2
Output: [2,1,4,null,null,3]
  2
 / \
1   4
   /
  3

Follow up:
A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
*/
void recoverTree(TreeNode* root) {
    TreeNode* p = nullptr;
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    while (root) {
        if (root->left == nullptr) {
            if (p && p->val >= root->val) {
                if (first == nullptr) {
                    first = p;
                }
                second = root;
            }
            p = root;
            root = root->right;
            continue;
        }
        TreeNode* pre = root->left;
        while (pre->right && pre->right != root) {
            pre = pre->right;
        }
        if (pre->right == root) {
            if (p && p->val >= root->val) {
                if (first == nullptr) {
                    first = p;
                }
                second = root;
            }
            p = root;
            pre->right = nullptr;
            root = root->right;
        } else {
            assert(pre->right == nullptr);
            pre->right = root;
            root = root->left;
        }
    }
    if (first && second) {
        std::swap(first->val, second->val);
    }
}

FTEST(test_recoverTree) {
    auto t = [](const std::vector<TreeNodeStub>& nodes) {
        TreeNode* root = create_tree(nodes);
        recoverTree(root);
        LOG(INFO) << nodes << " recover BST: " << output_tree_inorder(root);
    };

    t({1, 3, nullptr, nullptr, 2});
}

/**
 ///////////// 100. Same Tree
Given two binary trees, write a function to check if they are the same or not.
Two binary trees are considered the same if they are
 structurally identical and the nodes have the same value.

Example 1:
Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]
Output: true

Example 2:
Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]
Output: false

Example 3:
Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]
Output: false
*/
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr) {
        return q == nullptr;
    }
    if (q == nullptr) {
        return p == nullptr;
    }
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

FTEST(test_isSameTree) {
    auto t = [](const std::vector<TreeNodeStub>& a, const std::vector<TreeNodeStub>& b) {
        TreeNode* tree1 = create_tree(a);
        TreeNode* tree2 = create_tree(b);
        auto re = isSameTree(tree1, tree2);
        LOG(INFO) << a << " is same to " << b << ": " << re;
        return re;
    };

    FEXP(t({}, {}), true);
    FEXP(t({nullptr}, {nullptr}), true);
    FEXP(t({}, {nullptr}), true);
    FEXP(t({nullptr}, {}), true);
    FEXP(t({1}, {}), false);
    FEXP(t({}, {1}), false);
    FEXP(t({1, 2}, {1, nullptr, 2}), false);
    FEXP(t({1, 2}, {1, 2}), true);
    FEXP(t({1, 2, 3}, {1, 2, 3}), true);
    FEXP(t({1, 2, 1}, {1, 1, 2}), false);
    FEXP(t({10, 5, 15}, {10, 5, nullptr, nullptr, 15}), false);
    FEXP(isSameTree(create_tree(), create_tree({0, 1, 2, 3, 4, 5})), true);
}
