#pragma once

#include <stack>
#include <ostream>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

struct TreeNode {
    explicit TreeNode(int value) : val(value) {}

    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int val = 0;

    TreeNode* p = nullptr;
};

struct LCNode {
    explicit LCNode(int value) : val(value) {}

    LCNode* left = nullptr;
    LCNode* right = nullptr;
    LCNode* next = nullptr;
    int val = 0;
};

struct TreeNodeStub {
    TreeNodeStub(int val) : v(val), null(false) {}

    TreeNodeStub(nullptr_t n) {}

    template<typename T=TreeNode>
    T* create_node() {
        return null ? nullptr : new T(v);
    }

    int v = 0;
    bool null = true;

    friend inline LogStream& operator<<(LogStream& ss, const TreeNodeStub& stub) {
        ss << (stub.null ? "nullptr" : std::to_string(stub.v));
        return ss;
    }
};

template<typename T=TreeNode>
T* create_tree(const std::vector<TreeNodeStub>& nums) {
    T* root = nullptr;
    T* p = nullptr;
    bool left_or_right = true;
    std::deque<T*> qq;
    for (auto num : nums) {
        if (root == nullptr) {
            root = num.create_node<T>();
            qq.push_back(root);
            continue;
        }
        while (p == nullptr && !qq.empty()) {
            p = qq.front();
            left_or_right = true;
            qq.pop_front();
        }
        if (p == nullptr) { // FIXME.. root free
            return nullptr;
        }
        if (left_or_right) {
            p->left = num.create_node<T>();
            left_or_right = false;
            qq.push_back(p->left);
        } else {
            p->right = num.create_node<T>();
            qq.push_back(p->right);
            p = nullptr;
        }
    }
    return root;
}

std::vector<TreeNodeStub> output_tree(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    if (root == nullptr) {
        return res;
    }
    std::deque<TreeNode*> q;
    q.emplace_back(root);
    bool go = true;
    while (!q.empty() || go) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = q.front();
            q.pop_front();
            if (p == nullptr) {
                res.emplace_back(nullptr);
            } else {
                res.emplace_back(p->val);
            }

            if (p != nullptr && (p->left || p->right)) {
                q.emplace_back(p->left);
                q.emplace_back(p->right);
            }
        }
        go = !q.empty();
        for (size_t i = q.size(); i > 0; --i) {
            if (q[i] != nullptr) {
                go = true;
                break;
            }
        }
    }
    if (res.back().null) {
        res.pop_back();
    }
    return res;
}

std::vector<TreeNodeStub> inorder_morris_travel(TreeNode* n);

std::vector<TreeNodeStub> output_tree_inorder(TreeNode* root) {
    return inorder_morris_travel(root);
}

template<typename T=TreeNode>
std::string print_tree(T* n, std::function<char(T*)> next_flag, int ws_col = 50) {
    if (n == nullptr) {
        return "";
    }

    std::stringstream ss;
    std::deque<std::pair<T*, int>> q;
    q.emplace_back(n, 0);

    int level = 0;
    while (!q.empty()) {
        int idx = std::pow(2, (level++)) - 1;
        for (size_t i = q.size(); i > 0; --i) {
            if (i == 1 && q.front().first == nullptr) {
                q.pop_front();
                continue;
            }
            T* p = q.front().first;
            int pos = q.front().second;
            q.pop_front();

            while (idx < pos) {
                ss << std::string(ws_col, ' ');
                ++idx;
            }
            ++idx;

            int value_len = p == nullptr ? 1 : std::to_string(p->val).size();
            int remain_len = ws_col - value_len;
            int space_len = remain_len / 2;

            ss << std::string(space_len + (remain_len % 2 != 0 ? 1 : 0), ' ') <<
               (p == nullptr ? "N" : std::to_string(p->val)) <<
               std::string(std::max(space_len - 1, 0), ' ') << next_flag(p);

            if (p != nullptr && (p->left || p->right)) {
                q.emplace_back(p->left, 2 * pos + 1);
                q.emplace_back(p->right, 2 * pos + 2);
            }
        }
        ss << '\n';
        ws_col /= 2;
    }
    return ss.str();
}

std::string print_tree(TreeNode* n, int ws_col = 50) {
    return print_tree<TreeNode>(n, [](TreeNode*) { return ' '; }, ws_col);
}

std::string print_tree(LCNode* n, int ws_col = 50) {
    return print_tree<LCNode>(n, [](LCNode* p) { return p && p->next ? '>' : ' '; }, ws_col);
}

FTEST(test_print_tree) {
    LOG(INFO) << "\n" << print_tree(create_tree({4, 1, nullptr, nullptr, 2, nullptr, 3}));
    LOG(INFO) << "\n" << print_tree(create_tree({1, nullptr, 2, nullptr, 3, nullptr, 4}));
}

int tree_height(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }

    return std::max(tree_height(n->left), tree_height(n->right)) + 1;
}

FTEST(test_tree_height) {
    TreeNode* root = create_tree({0, 1, 2, 3, 4, 5});
    LOG(INFO) << "tree height: " << tree_height(root);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void preorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;
    std::stringstream ss;
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            ss << n->val << " ";
            stack.emplace_back(n);
            n = n->left;
        } else {
            n = stack.back();
            stack.pop_back();
            n = n->right;
        }
    }
    LOG(INFO) << ss.str();
}

void inorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;
    std::stringstream ss;
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            stack.emplace_back(n);
            n = n->left;
        } else {
            n = stack.back();
            stack.pop_back();
            ss << n->val << " ";
            n = n->right;
        }
    }
    LOG(INFO) << ss.str();
}

void postorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;
    TreeNode* last = n;

    std::stringstream ss;
    while (n != nullptr || !stack.empty()) {
        while (n != nullptr) {
            stack.emplace_back(n);
            n = n->left;
        }

        n = stack.back();
        if (n->right == nullptr || n->right == last) {
            ss << n->val << " ";
            stack.pop_back();
            last = n;
            n = nullptr;
        } else {
            n = n->right;
        }
    }
    LOG(INFO) << ss.str();
}

void preorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    LOG(INFO) << n->val << " ";
    preorder_recursive_travel(n->left);
    preorder_recursive_travel(n->right);
}

void inorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    inorder_recursive_travel(n->left);
    LOG(INFO) << n->val << " ";
    inorder_recursive_travel(n->right);
}

void postorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    postorder_recursive_travel(n->left);
    postorder_recursive_travel(n->right);
    LOG(INFO) << n->val << " ";
}

/**
 * 1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
 * 2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。输出当前节点。当前节点更新为当前节点的右孩子。
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。
 * 3. 重复以上1、2直到当前节点为空。
 */
void preorder_morris_travel(TreeNode* n) {
    TreeNode* pre = nullptr;
    std::stringstream ss;
    while (n != nullptr) {
        if (n->left == nullptr) {
            ss << n->val << " ";
            n = n->right;
            continue;
        }

        pre = n->left;
        while (pre->right && pre->right != n) {
            pre = pre->right;
        }

        if (pre->right == nullptr) {
            ss << n->val << " ";
            pre->right = n;
            n = n->left;
        } else { // if (pre->r == n)
            pre->right = nullptr;
            n = n->right;
        }
    }
    LOG(INFO) << ss.str();
}

/**
 * 1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
 * 2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。当前节点更新为当前节点的右孩子。
 * 3. 重复以上1、2直到当前节点为空。
 */
std::vector<TreeNodeStub> inorder_morris_travel(TreeNode* n) {
    std::vector<TreeNodeStub> res;
    TreeNode* pre = nullptr;
    std::stringstream ss;
    while (n != nullptr) {
        if (n->left == nullptr) {
            res.emplace_back(n->val);
            n = n->right;
            continue;
        }

        pre = n->left;
        while (pre->right && pre->right != n) {
            pre = pre->right;
        }

        if (pre->right == nullptr) {
            pre->right = n;
            n = n->left;
        } else { // if (pre->r == n)
            pre->right = nullptr;
            res.emplace_back(n->val);
            n = n->right;
        }
    }
    return res;
}

/**
 * 当前节点设置为临时节点dump。
 * 1. 如果当前节点的左孩子为空，则将其右孩子作为当前节点。
 * 2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。倒序输出从当前节点的左孩子到该前驱节点这条路径上的所有节点。当前节点更新为当前节点的右孩子。
 * 3. 重复以上1、2直到当前节点为空。
 */
void postorder_morris_travel(TreeNode* n) {
    auto reverse_morris_node = [](TreeNode* from, TreeNode* to) {
        if (from == to) {
            return;
        }
        TreeNode* x = from;
        TreeNode* y = from->right;
        TreeNode* z;
        while (true) {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
            if (x == to) {
                break;
            }
        }
    };

    std::stringstream ss;

    TreeNode temp(0);
    temp.left = n;

    TreeNode* pre = nullptr;
    while (n != nullptr) {
        if (n->left == nullptr) {
            n = n->right;
            continue;
        }

        pre = n->left;
        while (n->right != nullptr && pre->right != n) {
            pre = pre->right;
        }

        if (pre->right == nullptr) {
            pre->right = n;
            n = n->left;
        } else { // if (pre->r == n)

            reverse_morris_node(n, pre);
            TreeNode* p = pre;
            while (p) {
                ss << p->val << " ";
                p = p->right;
            }
            reverse_morris_node(pre, n);

            pre->right = nullptr;
            n = n->right;
        }
    }
    LOG(INFO) << ss.str();
}

void levelorder_recursive_travel_handle(TreeNode* n, int level, std::stringstream& ss) {
    if (n == nullptr || level < 1) {
        return;
    }

    if (level == 1) {
        ss << n->val << " ";
        return;
    }
    levelorder_recursive_travel_handle(n->left, level - 1, ss);
    levelorder_recursive_travel_handle(n->right, level - 1, ss);
}

void levelorder_recursive_travel(TreeNode* n) {
    std::stringstream ss;
    int height = tree_height(n);

    for (int i = 1; i <= height; ++i) {
        levelorder_recursive_travel_handle(n, i, ss);
    }
    LOG(INFO) << ss.str();
}

void levelorder_stack_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    std::stringstream ss;
    std::deque<TreeNode*> q;
    q.emplace_back(n);

    while (!q.empty()) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = q.front();
            q.pop_front();

            ss << p->val << " ";

            if (p->left) {
                q.emplace_back(p->left);
            }
            if (p->right) {
                q.emplace_back(p->right);
            }
        }
    }

    LOG(INFO) << ss.str();
}

void levelorder_zigzag_travel(TreeNode* n) {

    if (n == nullptr) {
        return;
    }

    std::stringstream ss;
    std::deque<TreeNode*> q;
    q.emplace_back(n);

    bool direction = true;

    while (!q.empty()) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = nullptr;
            if (direction) {
                p = q.front();
                q.pop_front();
            } else {
                p = q.back();
                q.pop_back();
            }
            ss << p->val << " ";

            if (direction) {
                if (p->left) {
                    q.emplace_back(p->left);
                }
                if (p->right) {
                    q.emplace_back(p->right);
                }
            } else {
                if (p->right) {
                    q.emplace_front(p->right);
                }
                if (p->left) {
                    q.emplace_front(p->left);
                }
            }
        }
        direction = !direction;
    }

    LOG(INFO) << ss.str();
}

FTEST(test_binary_tree_travel) {
    TreeNode* root = create_tree({0, 1, 2, 3, 4, 5});
    print_tree(root);

    LOG(INFO) << "recursive:";
    preorder_recursive_travel(root);
    LOG(INFO);
    inorder_recursive_travel(root);
    LOG(INFO);
    postorder_recursive_travel(root);
    LOG(INFO);

    LOG(INFO) << "stack:";
    preorder_stack_travel(root);
    inorder_stack_travel(root);
    postorder_stack_travel(root);

    LOG(INFO);
    LOG(INFO) << "morris:";
    preorder_morris_travel(root);
    inorder_morris_travel(root);
    postorder_stack_travel(root);

    LOG(INFO);
    LOG(INFO) << "level:";
    levelorder_stack_travel(root);
    levelorder_recursive_travel(root);

    LOG(INFO);
    LOG(INFO) << "level zigzag:";
    levelorder_zigzag_travel(root);
}

int next_node_of_inorder_travel(TreeNode* n) {
    if (n->right == nullptr) {
        while (n->p) {
            if (n->p->left == n) {
                return n->p->val;
            } else {
                n = n->p;
            }
        }

    } else {
        n = n->right;
        while (n->left) {
            n = n->left;
        }
        return n->val;
    }

    return -1;
}

FTEST(test_next_node_of_inorder_travel) {
    TreeNode* tree = create_tree({0, 1, 2, 3, 4, 5});
    std::vector<TreeNodeStub> nodes = output_tree(tree);

    LOG(INFO) << "\nnext node of:";
    int ret = next_node_of_inorder_travel(nodes[0].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[1].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[2].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[3].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[4].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[5].create_node());
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int max_sum_path(TreeNode* p, int& sum, std::vector<std::vector<TreeNode*>>& path) {
    // TODO...
    if (p == nullptr) {
        return 0;
    }
    int left = std::max(max_sum_path(p->left, sum, path), 0);
    int right = std::max(max_sum_path(p->right, sum, path), 0);

    int sum_in = left + right + p->val;
    if (sum_in >= sum) {
        path.emplace_back(std::vector<TreeNode*>{p});
        sum = sum_in;
    } else {

    }

    return std::max(left, right) + p->val;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

struct TrieNode {
    explicit TrieNode(char value) : v(value) {
        for (auto& next : nexts) {
            next = nullptr;
        }
    }

    TrieNode* nexts[128]{nullptr};
    char v = 0;
    bool end = false;
};

TrieNode* create_trie(const std::vector<std::string>& dict) {
    TrieNode* root = new TrieNode('\0');

    for (auto& word : dict) {
        TrieNode* p = root;
        for (char c : word) {
            if (p->nexts[c] == nullptr) {
                p->nexts[c] = new TrieNode(c);
            }
            p = p->nexts[c];
        }
        p->end = true;
    }

    return root;
}

void trie_level_travel(TrieNode* trie) {
    std::stringstream ss;

    std::deque<TrieNode*> q;
    q.emplace_back(trie);

    while (!q.empty()) {
        for (size_t i = q.size(); i > 0; --i) {
            trie = q.front();
            q.pop_front();

            if (trie->end) {
                ss << "*";
            }
            if (trie->v != '\0') {
                ss << trie->v << " ";
            }

            for (auto& next : trie->nexts) {
                if (next != nullptr) {
                    q.emplace_back(next);
                }
            }
        }
        LOG(INFO) << ss.str();
        ss.str("");
    }
}

std::vector<std::string>
word_break_trie(const std::string& s, const std::vector<std::string>& wordDict) {
    std::vector<std::string> ress;
    if (s.empty()) {
        return ress;
    }
    size_t len = s.size();
    std::vector<std::vector<size_t>> st(len);

    std::function<void(size_t, std::vector<size_t>&)> bt;
    bt = [&s, &ress, &st, &bt](size_t start, std::vector<size_t>& starts) {
        if (start == s.size()) {
            std::string entry;
            for (int i = 1, n = starts.size(); i < n; ++i) {
                if (i > 1) {
                    entry += ' ';
                }
                entry += s.substr(starts[i - 1], starts[i] - starts[i - 1]);
            }
            ress.push_back(entry);
            return;
        }

        for (auto& next : st[start]) {
            starts.push_back(next);
            bt(next, starts);
            starts.pop_back();
        }
    };

    TrieNode* trie = create_trie(wordDict);
    TrieNode* p;

    for (int i = len - 1; i >= 0; --i) {
        p = trie;
        size_t pos = i;
        while (pos < len && p) {
            TrieNode* n = p->nexts[s[pos]];
            ++pos;
            if (n && n->end &&
                    (pos == len || !st[pos].empty())) { // pos here connect to next word or end
                st[i].emplace_back(pos);
            }
            p = n;
        }
    }

    std::vector<size_t> starts{0};
    bt(0, starts);
    return ress;
}

std::vector<std::string>
word_break_hashmap(const std::string& s, const std::vector<std::string>& wordDict) {
    std::vector<std::string> ans;

    std::function<void(const std::string&, std::vector<std::vector<int>>&, int, std::string)> bt;
    bt = [&ans, &bt](const std::string& s, std::vector<std::vector<int>>& res, int k,
            std::string cur) {
        if (k == 0) {
            ans.push_back(cur);
            ans.back().pop_back();
            return;
        }
        for (int id: res[k]) {
            bt(s, res, id, s.substr(id, k - id) + " " + cur);
        }
    };

    std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    std::vector<bool> dp(n + 1, false);
    std::vector<std::vector<int>> res(n + 1);
    dp[0] = true;
    for (int i = 1; i < n + 1; i++) {
        bool ok = false;
        for (int j = 1; j <= i; j++) {
            if (dp[j - 1] && dict.count(s.substr(j - 1, i - j + 1))) {
                ok = true;
                res[i].push_back(j - 1);
            }
        }
        dp[i] = ok;
    }
    bt(s, res, n, "");
    return ans;
}

std::vector<std::string>
word_break(const std::string& s, const std::vector<std::string>& wordDict) {
//    return word_break_hashmap(s, wordDict);
    return word_break_trie(s, wordDict);
}

FTEST(test_trie) {

    LOG(INFO) << word_break("abcdef", {"abcde", "ab", "ef"});
    LOG(INFO) << word_break("abcdef", {"abcde", "fg"});
    LOG(INFO) << word_break("abcdef", {"ab", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abc", "ab", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abc", "ab", "cde", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abcde", "ab", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abcde", "ab", "abc", "cd", "ef", "d", "def"});

    LOG(INFO) << word_break("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"});

    Timer timer;
    auto res = word_break("aaaaaaaaaaaaaaaaaaaaaaaa",
            {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa"});
    LOG(INFO) << res.size() << ", cost: " << timer.elapsed();

    timer.reset();
    res = word_break("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                     "aaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                     "aaaaaaaaaaaaaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa",
            "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
    LOG(INFO) << res.size() << ", cost: " << timer.elapsed();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
