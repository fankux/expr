#pragma once

#include <math.h>
#include <assert.h>
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

struct LCTreeNode {
    explicit LCTreeNode(int value) : val(value) {}

    LCTreeNode* left = nullptr;
    LCTreeNode* right = nullptr;
    LCTreeNode* next = nullptr;
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
        if (left_or_right && p == nullptr && !qq.empty()) {
            p = qq.front();
            qq.pop_front();
        }
        if (p == nullptr && !num.null) { // FIXME.. root free
            return nullptr;
        }
        if (left_or_right) {
            if (p != nullptr) {
                p->left = num.create_node<T>();
                qq.push_back(p->left);
            } else {
                qq.push_back(nullptr);
            }
            left_or_right = false;
        } else {
            if (p != nullptr) {
                p->right = num.create_node<T>();
                qq.push_back(p->right);
            } else {
                qq.push_back(nullptr);
            }
            left_or_right = true;
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

std::vector<TreeNodeStub> inorder_morris_travel(TreeNode* root);

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

std::string print_tree(LCTreeNode* n, int ws_col = 50) {
    return print_tree<LCTreeNode>(n, [](LCTreeNode* p) { return p && p->next ? '>' : ' '; },
            ws_col);
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

std::vector<TreeNodeStub> preorder_recursive_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::function<void(TreeNode*)> r_func;
    r_func = [&](TreeNode* n) {
        if (n == nullptr) {
            return;
        }
        res.emplace_back(n->val);
        r_func(n->left);
        r_func(n->right);
    };
    r_func(root);
    return res;
}

std::vector<TreeNodeStub> inorder_recursive_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::function<void(TreeNode*)> r_func;
    r_func = [&](TreeNode* n) {
        if (n == nullptr) {
            return;
        }
        r_func(n->left);
        res.emplace_back(n->val);
        r_func(n->right);
    };
    r_func(root);
    return res;
}

std::vector<TreeNodeStub> postorder_recursive_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::function<void(TreeNode*)> r_func;
    r_func = [&](TreeNode* n) {
        if (n == nullptr) {
            return;
        }
        r_func(n->left);
        r_func(n->right);
        res.emplace_back(n->val);
    };
    r_func(root);
    return res;
}

std::vector<TreeNodeStub> preorder_stack_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::stack<TreeNode*> ss;
    while (root != nullptr || !ss.empty()) {
        if (root != nullptr) {
            res.emplace_back(root->val);
            ss.emplace(root);
            root = root->left;
        } else {
            root = ss.top();
            ss.pop();
            root = root->right;
        }
    }
    return res;
}

std::vector<TreeNodeStub> inorder_stack_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::stack<TreeNode*> ss;
    while (root != nullptr || !ss.empty()) {
        if (root != nullptr) {
            ss.emplace(root);
            root = root->left;
        } else {
            root = ss.top();
            ss.pop();
            res.emplace_back(root->val);
            root = root->right;
        }
    }
    return res;
}

std::vector<TreeNodeStub> postorder_stack_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::stack<TreeNode*> ss;
    TreeNode* last = nullptr;
    while (root != nullptr || !ss.empty()) {
        while (root) {
            ss.emplace(root);
            root = root->left;
        }
        root = ss.top();
        // we not pop here, because right child(if exist and not visited yet) must be visit first
        if (root->right == nullptr || root->right == last) {
            res.emplace_back(root->val);
            last = root;
            ss.pop();
            // make stack do pop
            root = nullptr;
        } else { // right child not exist or not visit first
            root = root->right;
        }
    }
    return res;
}

/**
 * 1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
 * 2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。输出当前节点。当前节点更新为当前节点的右孩子。
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。
 * 3. 重复以上1、2直到当前节点为空。
 */
std::vector<TreeNodeStub> preorder_morris_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    while (root != nullptr) {
        if (root->left == nullptr) {
            res.emplace_back(root->val);
            root = root->right;
            continue;
        }

        TreeNode* pre = root->left;
        while (pre->right && pre->right != root) {
            pre = pre->right;
        }

        if (pre->right == nullptr) {
            res.emplace_back(root->val);
            pre->right = root;
            root = root->left;
        } else { // if (pre->r == n)
            pre->right = nullptr;
            root = root->right;
        }
    }
    return res;
}

/**
 * 1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
 * 2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。当前节点更新为当前节点的右孩子。
 * 3. 重复以上1、2直到当前节点为空。
 */
std::vector<TreeNodeStub> inorder_morris_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    while (root != nullptr) {
        if (root->left == nullptr) {
            res.emplace_back(root->val);
            root = root->right;
            continue;
        }

        TreeNode* pre = root->left;
        while (pre->right && pre->right != root) {
            pre = pre->right;
        }

        if (pre->right == nullptr) {
            pre->right = root;
            root = root->left;
        } else { // if (pre->r == n)
            pre->right = nullptr;
            res.emplace_back(root->val);
            root = root->right;
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
std::vector<TreeNodeStub> postorder_morris_travel(TreeNode* root) {
    auto reverse_nodes = [](TreeNode* p) {
        TreeNode* pre = nullptr;
        while (p != nullptr) {
            TreeNode* n = p->right;
            p->right = pre;
            pre = p;
            p = n;
        }
        return pre;
    };

    std::vector<TreeNodeStub> res;
    TreeNode dummy(0);
    dummy.left = root;
    root = &dummy;
    while (root != nullptr) {
        if (root->left == nullptr) {
            root = root->right;     // left null, go to right through 'pre->right->root'
            continue;
        }

        TreeNode* pre = root->left;
        while (pre->right && pre->right != root) {
            pre = pre->right;
        }

        if (pre->right == nullptr) { // left invisited
            pre->right = root;
            root = root->left;
        } else { // pre->right == root, left visited
            pre->right = nullptr;
            // reverse pre~root nodes to ouput
            TreeNode* p = reverse_nodes(root->left);
            assert(p == pre);
            while (p) {
                res.emplace_back(p->val);
                p = p->right;
            }
            reverse_nodes(pre);

            root = root->right;
        }
    }
    return res;
}

std::vector<TreeNodeStub> levelorder_recursive_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::function<void(TreeNode*, int)> r_func;
    r_func = [&](TreeNode* n, int level) {
        if (n == nullptr || level < 1) {
            return;
        }
        if (level == 1) {
            res.emplace_back(n->val);
            return;
        }
        r_func(n->left, level - 1);
        r_func(n->right, level - 1);
    };

    int height = tree_height(root);
    for (int i = 1; i <= height; ++i) {
        r_func(root, i);
    }
    return res;
}

std::vector<TreeNodeStub> levelorder_travel_queue(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::deque<TreeNode*> q{root};
    while (!q.empty()) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = q.front();
            q.pop_front();
            if (p == nullptr) {
                continue;
            }

            res.emplace_back(p->val);
            q.emplace_back(p->left);
            q.emplace_back(p->right);
        }
    }
    return res;
}

std::vector<TreeNodeStub> levelorder_zigzag_travel(TreeNode* root) {
    std::vector<TreeNodeStub> res;
    std::deque<TreeNode*> q{root};
    bool direction = true;
    while (!q.empty()) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = direction ? q.front() : q.back();
            direction ? q.pop_front() : q.pop_back();
            if (p == nullptr) {
                continue;
            }
            res.emplace_back(p->val);
            if (direction) {
                q.emplace_back(p->left);
                q.emplace_back(p->right);
            } else {
                q.emplace_front(p->right);
                q.emplace_front(p->left);
            }
        }
        direction = !direction;
    }
    return res;
}

FTEST(test_binary_tree_travel) {
    TreeNode* root = create_tree({0, 1, 2, 3, 4, 5});
    LOG(INFO) << "tree: \n" << print_tree(root);

    LOG(INFO);
    LOG(INFO) << "level:";
    LOG(INFO) << "queue:" << levelorder_travel_queue(root);
    LOG(INFO) << "recursive:" << levelorder_recursive_travel(root);

    LOG(INFO);
    LOG(INFO) << "recursive:";
    LOG(INFO) << "pre:" << preorder_recursive_travel(root);
    LOG(INFO) << "in:" << inorder_recursive_travel(root);
    LOG(INFO) << "post:" << postorder_recursive_travel(root);

    LOG(INFO);
    LOG(INFO) << "stack:";
    LOG(INFO) << "pre:" << preorder_stack_travel(root);
    LOG(INFO) << "in:" << inorder_stack_travel(root);
    LOG(INFO) << "post:" << postorder_stack_travel(root);

    LOG(INFO);
    LOG(INFO) << "morris:";
    LOG(INFO) << "pre:" << preorder_morris_travel(root);
    LOG(INFO) << "in:" << inorder_morris_travel(root);
    LOG(INFO) << "post:" << postorder_morris_travel(root);

    LOG(INFO);
    LOG(INFO) << "level:";
    LOG(INFO) << "queue:" << levelorder_travel_queue(root);
    LOG(INFO) << "recursive:" << levelorder_recursive_travel(root);
    LOG(INFO) << "zigzag:" << levelorder_zigzag_travel(root);
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

///////////////////////////////////////////////////////////////////////////////////////////////////

class SegmentTree {
public:
    void clear() {
        _c.clear();
    }

    bool empty() const {
        return _c.empty();
    }

    size_t size() const {
        return _c.size();
    }


private:
    std::deque<int> _c;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void rb_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////
void b_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

void avl_tree() {}