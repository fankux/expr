#pragma once

#include <stack>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

struct TreeNode {
    explicit TreeNode(int value) : v(value) {}

    TreeNode* p = nullptr;
    TreeNode* l = nullptr;
    TreeNode* r = nullptr;

    int v = 0;
};

/**
 *
 *         0
 *       /  \
 *     /     \
 *    1       2
 *   / \     /
 *  3   4   5
 *
 */
TreeNode* create_tree(std::vector<TreeNode*>* nodes = nullptr) {

    TreeNode* n0 = new TreeNode(0);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);

    if (nodes != nullptr) {
        nodes->emplace_back(n0);
        nodes->emplace_back(n1);
        nodes->emplace_back(n2);
        nodes->emplace_back(n3);
        nodes->emplace_back(n4);
        nodes->emplace_back(n5);
    }

    n0->l = n1;
    n1->p = n0;

    n0->r = n2;
    n2->p = n0;

    n1->l = n3;
    n3->p = n1;

    n1->r = n4;
    n4->p = n1;

    n2->l = n5;
    n5->p = n2;

    return n0;
}

void print_tree(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    int ws_col = 50;

    std::stringstream ss;
    std::deque<TreeNode*> q;
    q.emplace_back(n);

    bool go = true;
    while (!q.empty() || go) {
        for (size_t i = q.size(); i > 0; --i) {
            TreeNode* p = q.front();
            q.pop_front();

            int value_len = p == nullptr ? 4 : std::to_string(p->v).size();
            int remain_len = ws_col - value_len;
            int space_len = remain_len / 2;
            for (int k = 0; k < space_len; ++k) {
                ss << " ";
            }
            if (remain_len % 2 != 0) {
                ss << " ";
            }
            if (p == nullptr) {
                ss << "null";
            } else {
                ss << p->v;
            }
            for (int k = 0; k < space_len; ++k) {
                ss << " ";
            }

            if (p != nullptr && (p->l || p->r)) {
                q.emplace_back(p->l);
                q.emplace_back(p->r);
            }
        }
        ss << '\n';

        go = !q.empty();
        for (size_t i = q.size(); i > 0; --i) {
            if (q[i] != nullptr) {
                go = true;
                break;
            }
        }
        ws_col /= 2;
    }

    LOG(INFO) << "tree:\n" << ss.str();
}

int tree_height(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }

    return std::max(tree_height(n->l), tree_height(n->r)) + 1;
}

FTEST(test_tree_height) {
    TreeNode* root = create_tree();
    LOG(INFO) << "tree height: " << tree_height(root);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void preorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;
    std::stringstream ss;
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            ss << n->v << " ";
            stack.emplace_back(n);
            n = n->l;
        } else {
            n = stack.back();
            stack.pop_back();
            n = n->r;
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
            n = n->l;
        } else {
            n = stack.back();
            stack.pop_back();
            ss << n->v << " ";
            n = n->r;
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
            n = n->l;
        }

        n = stack.back();
        if (n->r == nullptr || n->r == last) {
            ss << n->v << " ";
            stack.back();
            stack.pop_back();
            last = n;
            n = nullptr;
        } else {
            n = n->r;
        }
    }
    LOG(INFO) << ss.str();
}

void preorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    LOG(INFO) << n->v << " ";
    preorder_recursive_travel(n->l);
    preorder_recursive_travel(n->r);
}

void inorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    inorder_recursive_travel(n->l);
    LOG(INFO) << n->v << " ";
    inorder_recursive_travel(n->r);
}

void postorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    postorder_recursive_travel(n->l);
    postorder_recursive_travel(n->r);
    LOG(INFO) << n->v << " ";
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
        if (n->l == nullptr) {
            ss << n->v << " ";
            n = n->r;
            continue;
        }

        pre = n->l;
        while (pre->r && pre->r != n) {
            pre = pre->r;
        }

        if (pre->r == nullptr) {
            ss << n->v << " ";
            pre->r = n;
            n = n->l;
        } else { // if (pre->r == n)
            pre->r = nullptr;
            n = n->r;
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
void inorder_morris_travel(TreeNode* n) {
    TreeNode* pre = nullptr;
    std::stringstream ss;
    while (n != nullptr) {
        if (n->l == nullptr) {
            ss << n->v << " ";
            n = n->r;
            continue;
        }

        pre = n->l;
        while (pre->r && pre->r != n) {
            pre = pre->r;
        }

        if (pre->r == nullptr) {
            pre->r = n;
            n = n->l;
        } else { // if (pre->r == n)
            pre->r = nullptr;
            ss << n->v << " ";
            n = n->r;
        }
    }
    LOG(INFO) << ss.str();
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
        TreeNode* y = from->r;
        TreeNode* z;
        while (true) {
            z = y->r;
            y->r = x;
            x = y;
            y = z;
            if (x == to) {
                break;
            }
        }
    };

    std::stringstream ss;

    TreeNode temp(0);
    temp.l = n;

    TreeNode* pre = nullptr;
    while (n != nullptr) {
        if (n->l == nullptr) {
            n = n->r;
            continue;
        }

        pre = n->l;
        while (n->r != nullptr && pre->r != n) {
            pre = pre->r;
        }

        if (pre->r == nullptr) {
            pre->r = n;
            n = n->l;
        } else { // if (pre->r == n)

            reverse_morris_node(n, pre);
            TreeNode* p = pre;
            while (p) {
                ss << p->v << " ";
                p = p->r;
            }
            reverse_morris_node(pre, n);

            pre->r = nullptr;
            n = n->r;
        }
    }
    LOG(INFO) << ss.str();
}

void levelorder_recursive_travel_handle(TreeNode* n, int level, std::stringstream& ss) {
    if (n == nullptr || level < 1) {
        return;
    }

    if (level == 1) {
        ss << n->v << " ";
        return;
    }
    levelorder_recursive_travel_handle(n->l, level - 1, ss);
    levelorder_recursive_travel_handle(n->r, level - 1, ss);
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

            ss << p->v << " ";

            if (p->l) {
                q.emplace_back(p->l);
            }
            if (p->r) {
                q.emplace_back(p->r);
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
            ss << p->v << " ";

            if (direction) {
                if (p->l) {
                    q.emplace_back(p->l);
                }
                if (p->r) {
                    q.emplace_back(p->r);
                }
            } else {
                if (p->r) {
                    q.emplace_front(p->r);
                }
                if (p->l) {
                    q.emplace_front(p->l);
                }
            }
        }
        direction = !direction;
    }

    LOG(INFO) << ss.str();
}

FTEST(test_binary_tree_travel) {
    TreeNode* root = create_tree();
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
    if (n->r == nullptr) {
        while (n->p) {
            if (n->p->l == n) {
                return n->p->v;
            } else {
                n = n->p;
            }
        }

    } else {
        n = n->r;
        while (n->l) {
            n = n->l;
        }
        return n->v;
    }

    return -1;
}

FTEST(test_next_node_of_inorder_travel) {
    std::vector<TreeNode*> nodes;
    TreeNode* root = create_tree(&nodes);

    LOG(INFO) << "\nnext node of:";
    int ret = next_node_of_inorder_travel(nodes[0]);
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[1]);
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[2]);
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[3]);
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[4]);
    if (ret != -1) {
        LOG(INFO) << ret;
    } else {
        LOG(INFO) << "no next";
    }
    ret = next_node_of_inorder_travel(nodes[5]);
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
    int left = std::max(max_sum_path(p->l, sum, path), 0);
    int right = std::max(max_sum_path(p->r, sum, path), 0);

    int sum_in = left + right + p->v;
    if (sum_in >= sum) {
        path.emplace_back(std::vector<TreeNode*>{p});
        sum = sum_in;
    } else {

    }

    return std::max(left, right) + p->v;
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

// TODO... All possible sentances
std::string word_break(const std::string& sentence, const std::vector<std::string>& dict) {
    if (sentence.empty()) {
        return "";
    }

    TrieNode* trie = create_trie(dict);
    TrieNode* p = trie;

    size_t i = 0;
    size_t o = 0;
    std::string res;
    std::stack<std::tuple<size_t, size_t>> s;

    while (i < sentence.size()) {
        char c = sentence[i];

        if (p->nexts[c]) {
            res += c;
            ++i;
            ++o;
            if (p->nexts[c]->end) {
                s.emplace(std::make_tuple(i, o));
            }

            p = p->nexts[c];

        } else {

            p = trie;
            if (p->nexts[c] == nullptr) {
                if (s.empty()) {
                    return "";
                }

                auto& tuple = s.top();
                i = std::get<0>(tuple);
                o = std::get<1>(tuple);
                s.pop();

                res.erase(o, res.size() - o);
            }

            res += ' ';
            o = res.size();
        }
    }

    return res;
}

FTEST(test_trie) {
    LOG(INFO) << word_break("abcdef", {"ab", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abc", "ab", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abc", "ab", "cde", "cd", "ef"});
    LOG(INFO) << word_break("abcdef", {"abcde", "ab", "ef"});
    LOG(INFO) << word_break("abcdef", {"abcde", "ab", "cd", "ef"});
}

///////////////////////////////////////////////////////////////////////////////////////////////////
