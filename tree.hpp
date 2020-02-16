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
        if (p == nullptr) { // FIXME.. root free
            if (!num.null) {
                return nullptr;
            }
            left_or_right = !left_or_right;
            continue;
        }
        if (left_or_right) {
            if (!num.null) {
                p->left = num.create_node<T>();
                qq.push_back(p->left);
            }
        } else {
            if (!num.null) {
                p->right = num.create_node<T>();
                qq.push_back(p->right);
            }
            p = nullptr;
        }
        left_or_right = !left_or_right;
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
    return print_tree<LCTreeNode>(n, [](LCTreeNode* p) {
        return p && p->next ? '>' : ' ';
    }, ws_col);
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
 *      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
 *         输出当前节点。当前节点更新为当前节点的右孩子。
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
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。
 *         当前节点更新为当前节点的右孩子。
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
 *      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。
 *         倒序输出从当前节点的左孩子到该前驱节点这条路径上的所有节点。当前节点更新为当前节点的右孩子。
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
    explicit SegmentTree(const std::vector<int>& nums, bool lazy = true) {
        _size = nums.size();
        int len = _size <= 1 ? _size : (next_power_of_2(_size) << 1) - 1; // find precise size
        _c.resize(len, INT_MAX);
        if ((_lazy_flag = lazy)) {
            _lazy.resize(len);
        }

        std::function<int(const std::vector<int>&, size_t, size_t, size_t)> build;
        build = [&](const std::vector<int>& nums, size_t l, size_t r, size_t idx) {
            if (l + 1 >= r) {
                _c[idx] = nums[l];
            } else {
                size_t mid = l + (r - l) / 2;
                _c[idx] = std::min(build(nums, l, mid, (idx << 1) + 1),
                        build(nums, mid, r, (idx << 1) + 2));
            }
            return _c[idx];
        };
        build(nums, 0, nums.size(), 0);
    }

    inline void clear() {
        _c.clear();
    }

    inline bool empty() const {
        return _c.empty();
    }

    inline size_t size() const {
        return _size;
    }

    inline int min(size_t start, size_t end) {
        std::function<int(size_t, size_t, size_t, size_t, size_t)> rfunc;
        rfunc = [&](size_t l, size_t r, size_t sl, size_t sr, size_t idx) {
            if (sr <= l || r <= sl) { // no overlap
                return INT_MAX;
            }

            if (_lazy_flag && _lazy[idx] != 0) {
                _c[idx] += _lazy[idx];
                if (l + 1 < r) { // not leaf
                    _lazy[(idx << 1) + 1] += _lazy[idx];
                    _lazy[(idx << 1) + 2] += _lazy[idx];
                }
                _lazy[idx] = 0;
            }

            if (sl <= l && r <= sr) { // total overlap
                return _c[idx];
            }
            // l < sl || sr < r, partial overlap
            size_t mid = l + (r - l) / 2;
            return std::min(rfunc(l, mid, sl, sr, (idx << 1) + 1),
                    rfunc(mid, r, sl, sr, (idx << 1) + 2));
        };
        return rfunc(0, _size, start, end, 0);
    }

    void update(size_t pos, int val) {
        std::function<void(size_t, size_t, size_t)> rfunc;
        rfunc = [&](size_t l, size_t r, size_t idx) {
            if (pos < l || r <= pos) { // out of range
                return;
            }

            /**
              Actually we don't need to do lazy propagation here,
              because updating value by a explicit index must
              traverse to a exactly leaf node.

               - we do lazy propagation here good for other methods

             */
            if (_lazy_flag && _lazy[idx] != 0) {
                _c[idx] += _lazy[idx];
                if (l + 1 < r) { // not leaf
                    _lazy[(idx << 1) + 1] += _lazy[idx];
                    _lazy[(idx << 1) + 2] += _lazy[idx];
                }
                _lazy[idx] = 0;
            }

            if (l + 1 == r) { // got index
                assert(l == pos);
                _c[idx] = val;
                return;
            }
            // l < sl || sr < r, partial overlap
            size_t mid = l + (r - l) / 2;
            rfunc(l, mid, (idx << 1) + 1);
            rfunc(mid, r, (idx << 1) + 2);
            _c[idx] = std::min(_c[(idx << 1) + 1], _c[(idx << 1) + 2]);
        };
        rfunc(0, _size, 0);
    }

    void update(size_t start, size_t end, int delta) {
        std::function<void(size_t, size_t, size_t)> rfunc;
        rfunc = [&](size_t l, size_t r, size_t idx) {
            if (l >= r) {
                return;
            }

            if (_lazy_flag && _lazy[idx] != 0) {
                _c[idx] += _lazy[idx];
                if (l + 1 < r) { // not leave
                    _lazy[(idx << 1) + 1] += _lazy[idx];
                    _lazy[(idx << 1) + 2] += _lazy[idx];
                }
                _lazy[idx] = 0;
            }

            if (r <= start || end <= l) { // no overlap
                return;
            }

            if (_lazy_flag && start <= l && r <= end) { // total overlap
                _c[idx] += delta;
                if (l + 1 < r) { // not leave
                    _lazy[(idx << 1) + 1] += delta;
                    _lazy[(idx << 1) + 2] += delta;
                }
                return;
            }

            if (!_lazy_flag && l + 1 == r) { // got a leave node
                _c[idx] += delta;
                return;
            }

            // l < sl || sr < r, partial overlap
            size_t mid = l + (r - l) / 2;
            rfunc(l, mid, (idx << 1) + 1);
            rfunc(mid, r, (idx << 1) + 2);
            _c[idx] = std::min(_c[(idx << 1) + 1], _c[(idx << 1) + 2]);
        };
        rfunc(0, _size, 0);
    }

    std::string print_tree(int ws_col = 70) {
        // TODO... support lazy propagation.
        std::vector<std::string> node_levels;
        std::function<void(size_t, size_t, size_t, int, int)> rfunc;
        rfunc = [&](size_t l, size_t r, size_t idx, int level, int ws) {
            if (idx >= _c.size()) {
                return;
            }

            if (level >= node_levels.size()) {
                node_levels.resize(level + 1);
            }

            if (_c[idx] == INT_MAX) {
                node_levels[level] += std::string(ws <= 0 ? 1 : ws, ' ');
            } else {
                std::string label = std::to_string(_c[idx]) +
                        '[' + std::to_string(idx) + ':' + std::to_string(l) + ',' +
                        std::to_string(r - 1) + ']';
                int space_size = ws - label.size();
                space_size = space_size <= 0 ? 1 : space_size / 2;
                node_levels[level] +=
                        std::string(space_size, ' ') + label + std::string(space_size, ' ');
            }
            size_t mid = l + (r - l) / 2;
            ws >>= 1;
            rfunc(l, mid, (idx << 1) + 1, level + 1, ws);
            rfunc(mid, r, (idx << 1) + 2, level + 1, ws);
        };
        rfunc(0, _size, 0, 0, ws_col);

        std::stringstream ss;
        for (auto& node_level: node_levels) {
            for (auto& node : node_level) {
                ss << node;
            }
            ss << '\n';
        }
        return ss.str();
    }

private:

    // num > 1
    static inline uint64_t next_power_of_2(uint64_t num) {
#if defined(__GNUC__)
        return 1 << (sizeof(int) * 8 - __builtin_clz(num - 1));
#else
        --num;
        num |= num >> 1;
        num |= num >> 2;
        num |= num >> 4;
        num |= num >> 8;
        num |= num >> 16;
        num |= num >> 32;
        return ++num;
#endif
    }

private:
    size_t _size = 0;
    std::vector<int> _c;
    bool _lazy_flag = true;
    std::vector<int> _lazy;
};

FTEST(test_SegmentTree) {
    auto t = [](const std::vector<int>& nums) {
        SegmentTree st(nums);
        LOG(INFO) << nums << " segment tree(" << st.size() << "):\n" << st.print_tree();
        for (int i = 1; i <= st.size(); ++i) {
            for (int j = 0; j < st.size(); j += i) {
                LOG(INFO) << "min of [" << j << "," << (i + j) << "):"
                          << st.min(j, i + j);
            }
        }
        return st;
    };
    t({1});
    t({1, 2});
    t({3, 1, 2});
    t({4, 3, 1, 2});
    t({4, 3, 1, 5, 2});
    t({4, 6, 3, 1, 5, 2});
    t({4, 6, 3, 1, 5, 2, 7});
    t({4, 6, 3, 1, 5, 2, 8, 7});

    auto t_update = [](const std::vector<int>& nums) {
        SegmentTree st(nums);
        st.update(nums.size() - 1, 99);
        st.update(0, nums.size(), 1);
        LOG(INFO) << nums << " segment tree(" << st.size() << "):\n" << st.print_tree();
        for (int i = 1; i <= st.size(); ++i) {
            for (int j = 0; j < st.size(); j += i) {
                LOG(INFO) << "min of [" << j << "," << (i + j) << "):"
                          << st.min(j, i + j);
            }
        }
        return st;
    };
    t_update({1});
    t_update({1, 2});
    t_update({3, 1, 2});
    t_update({4, 3, 1, 2});
    t_update({4, 3, 1, 5, 2});
    t_update({4, 6, 3, 1, 5, 2});
    t_update({4, 6, 3, 1, 5, 2, 7});
    t_update({4, 6, 3, 1, 5, 2, 8, 7});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

struct PathNode {
    typedef std::function<void(PathNode*)> Callback;

    explicit PathNode(const std::string& k, const std::string& v, PathNode* parent) : key(k),
            val(v), p(parent) {}

    PathNode* p = nullptr;
    std::string key;
    std::string val;
    std::unordered_map<std::string, PathNode*> childs;
    std::vector<Callback> cbs;
};

/**
 /aa/bb/cc
 /aa/ee/ff

        /
        ↓
        aa
       ↙   ↘
      bb   ee
      ↓    ↓
      cc   ff
 */
class PathStore {
public:
    bool create(const std::string& path, const std::string& value) {
        std::deque<std::string> sections;
        PathNode* cur = nullptr;
        PathNode* p = fetch_last_node(path, sections, cur);
        if (root == nullptr && path == "/") {   // handle root
            root = new PathNode("", value, nullptr);
            return true;
        } else if (p && sections.size() == 1) {
            p->childs.emplace(sections.front(), new PathNode(sections.front(), value, p));
            return true;
        } else {
            return false;
        }
    }

    std::string get(const std::string& path) {
        std::deque<std::string> sections;
        PathNode* cur = nullptr;
        fetch_last_node(path, sections, cur);
        return cur == nullptr ? "" : cur->val;
    }

    bool set(const std::string& path, const std::string& value) {
        std::deque<std::string> sections;
        PathNode* cur = nullptr;
        fetch_last_node(path, sections, cur);
        if (cur) {
            cur->val = value;

            while (cur) {
                for (auto& cb : cur->cbs) {
                    cb(cur);
                }
                cur = cur->p;
            }
            return true;
        } else {
            return false;
        }
    }

    bool watch(const std::string& path, PathNode::Callback callback) {
        std::deque<std::string> sections;
        PathNode* cur = nullptr;
        fetch_last_node(path, sections, cur);
        if (cur) {
            cur->cbs.emplace_back(callback);
            return true;
        } else {
            return false;
        }
    }

    static std::deque<std::string> explode_path(const std::string& path) {
        std::deque<std::string> res;
        std::size_t pos = 0;
        std::size_t left = pos;
        while (pos != std::string::npos) {
            if (left < pos) {
                res.emplace_back(path.substr(left, pos - left));
            }
            left = pos + 1;
            pos = path.find('/', left);
        }
        if (left < path.size()) {
            res.emplace_back(path.substr(left));
        }
        return res;
    }

private:
    PathNode* fetch_last_node(const std::string& path, std::deque<std::string>& sections,
            PathNode*& cur) {
        sections = explode_path(path);

        PathNode* p = root;
        cur = root;
        while (cur && !sections.empty()) {
            p = cur;

            std::string section = sections.front();
            auto entry = cur->childs.find(section);
            if (entry == cur->childs.end()) {
                cur = nullptr;
                break;
            }
            cur = entry->second;
            sections.pop_front();
        }
        return p;
    }

private:
    PathNode* root = nullptr;
};

FTEST(test_PathStore) {
    auto t_path = [](const std::string& path) {
        auto re = PathStore::explode_path(path);
        LOG(INFO) << path << " explode: (" << re.size() << ")" << re;
    };

    t_path("");
    t_path("/");
    t_path("//");
    t_path("///");
    t_path("/a");
    t_path("//a");
    t_path("///a");
    t_path("/a/");
    t_path("//a/");
    t_path("///a/");
    t_path("/a//");
    t_path("/a///");
    t_path("//a///");
    t_path("///a///");
    t_path("/a/b");
    t_path("/a/b/");
    t_path("/a//b");
    t_path("/a///b");
    t_path("/a/b/c");
    t_path("/a/b/c/");
    t_path("/a/b//c/");
    t_path("/a/b///c/");
    t_path("/aa");
    t_path("//aa");
    t_path("///aa");
    t_path("/aa/");
    t_path("//aa/");
    t_path("///aa/");
    t_path("/aa//");
    t_path("/aa///");
    t_path("//aa///");
    t_path("///aa///");
    t_path("/aa/bb");
    t_path("/aa/bb/");
    t_path("/aa//bb");
    t_path("/aa///bb");
    t_path("/aa/bb/cc");
    t_path("/aa/bb/cc/");
    t_path("/aa/bb//cc/");
    t_path("/aa/bb///cc/");

    PathStore ps;
    FEXP(ps.create("/a", "a"), false);
    FEXP(ps.create("/", "root"), true);
    FEXP(ps.get("/"), "root");
    FEXP(ps.create("/aa", "aa"), true);
    FEXP(ps.get("/aa"), "aa");
    FEXP(ps.create("/bb", "bb"), true);
    FEXP(ps.get("/bb"), "bb");
    FEXP(ps.create("/aa/cc", "cc"), true);
    FEXP(ps.get("/aa/cc"), "cc");
    FEXP(ps.set("/aa/cc1", "cc1"), false);
    FEXP(ps.set("/aa/cc", "cc1"), true);
    FEXP(ps.get("/aa/cc"), "cc1");

    LOG(INFO) << "------";
    FEXP(ps.watch("/ff", [](PathNode* c) { LOG(INFO) << "cb " << c->val; }), false);
    FEXP(ps.watch("/", [](PathNode* c) { LOG(INFO) << "cb1 " << c->val; }), true);
    FEXP(ps.watch("/", [](PathNode* c) { LOG(INFO) << "cb2 " << c->val; }), true);
    FEXP(ps.set("/", "root_set"), true);

    LOG(INFO) << "------";
    FEXP(ps.watch("/aa", [](PathNode* c) { LOG(INFO) << "cb1 " << c->val; }), true);
    FEXP(ps.watch("/aa", [](PathNode* c) { LOG(INFO) << "cb2 " << c->val; }), true);
    FEXP(ps.set("/aa", "aa_set"), true);

    LOG(INFO) << "------";
    FEXP(ps.watch("/bb", [](PathNode* c) { LOG(INFO) << "cb1 " << c->val; }), true);
    FEXP(ps.watch("/bb", [](PathNode* c) { LOG(INFO) << "cb2 " << c->val; }), true);
    FEXP(ps.set("/bb", "bb_set"), true);

    LOG(INFO) << "------";
    FEXP(ps.watch("/aa/cc", [](PathNode* c) { LOG(INFO) << "cb1 " << c->val; }), true);
    FEXP(ps.watch("/aa/cc", [](PathNode* c) { LOG(INFO) << "cb2 " << c->val; }), true);
    FEXP(ps.set("/aa/cc", "cc_set"), true);
}

struct NormalTreeNode {
    NormalTreeNode() = default;

    explicit NormalTreeNode(int i, int value) : id(i), val(value) {}

    int id;
    int val;
    std::vector<NormalTreeNode*> childs;
};

class NormalTree {
public:
    /**
     * @param pairs <node number from, node number to>
     * @param values values of each node
     */
    bool build(const std::vector<std::pair<int, int>>& pairs, const std::vector<int>& values) {
        std::map<int, NormalTreeNode*> nodes;
        // ensure size match, then do right things
        for (auto& pair : pairs) {
            NormalTreeNode* from;
            auto entry = nodes.find(pair.first);
            if (entry == nodes.end()) {
                if (pair.first > values.size()) {
                    goto fail;
                }
                from = new NormalTreeNode(pair.first, values[pair.first - 1]);
                from->val = values[pair.first - 1];
                nodes[pair.first] = from;
            } else {
                from = entry->second;
            }

            NormalTreeNode* to;
            entry = nodes.find(pair.second);
            if (entry == nodes.end()) {
                if (pair.second > values.size()) {
                    goto fail;
                }
                to = new NormalTreeNode(pair.second, values[pair.second - 1]);
                to->val = values[pair.second - 1];
                nodes[pair.second] = to;
            } else {
                to = entry->second;
            }

            from->childs.emplace_back(to);
            if (from->id == 1) {
                _root = from;
            }
        }
        return true;

        fail:
        for (auto& entry : nodes) {
            delete entry.second;
        }
        return false;
    }

    ~NormalTree() {
        clear(_root);
    }

    NormalTreeNode* root() {
        return _root;
    }

private:
    void clear(NormalTreeNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& entry : node->childs) {
            clear(entry);
            delete entry;
        }
        delete node;
    }

private:
    NormalTreeNode* _root = nullptr;
};

std::vector<int> interlaced_transfer_to(NormalTree& from, NormalTree& to) {
    std::vector<int> res;
    std::function<void(NormalTreeNode*, NormalTreeNode*, int, int)> rfunc;
    rfunc = [&](NormalTreeNode* f, NormalTreeNode* t, int ccnt, int gcnt) {
        int value = f->val;
        if (gcnt % 2 == 1) {
            value = !value;
        }
        if (value != t->val) {
            ++gcnt;
            res.emplace_back(f->id);
        }
        for (size_t i = 0; i < f->childs.size(); ++i) {
            rfunc(f->childs[i], t->childs[i], gcnt, ccnt);
        }
    };
    rfunc(from.root(), to.root(), 0, 0);
    return res;
}

FTEST(test_interlaced_transfer_to) {
    /**
                1(0)                        1(0)
             /   |   \                   /   |   \
          2(1)  3(1)  4(0)   ==>      2(0)  3(1)  4(0)   ==> [2, 6, 9, 8]
         /  |    |      \            /  |    |      \
      5(1) 6(0) 7(1)   8(0)       5(1) 6(1) 7(1)   8(1)
            |                           |
           9(1)                        9(1)
    */
    std::vector<std::pair<int, int>> nodes = {
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 5},
            {2, 6},
            {3, 7},
            {4, 8},
            {6, 9},
    };
    NormalTree from;
    FEXP(from.build(nodes, {1}), false);
    FEXP(from.build(nodes, {0, 1, 1, 0, 1, 0, 1, 0, 1}), true);
    NormalTree to;
    FEXP(to.build(nodes, {0, 0, 1, 0, 1, 1, 1, 1, 1}), true);

    LOG(INFO) << "interlaced_transfer_to: " << interlaced_transfer_to(from, to);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void rb_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////
void b_tree() {}
