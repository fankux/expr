#pragma once

#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

class TreeNode {
public:
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
        nodes->emplace_back(n0, n1, n2, n3, n4, n5);
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

void preorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;

    LOG(INFO) << "preorder travel: ";
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            LOG(INFO) << n->v << " ";
            stack.emplace_back(n);
            n = n->l;
        } else {
            n = stack.back();
            stack.pop_back();
            n = n->r;
        }
    }
}

void inorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;

    LOG(INFO) << "inorder travel: ";
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            stack.emplace_back(n);
            n = n->l;
        } else {
            n = stack.back();
            stack.pop_back();
            LOG(INFO) << n->v << " ";
            n = n->r;
        }
    }
}

void postorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;
    TreeNode* last = n;

    while (n != nullptr || !stack.empty()) {
        while (n != nullptr) {
            stack.emplace_back(n);
            n = n->l;
        }

        n = stack.back();
        if (n->r == nullptr || n->r == last) {
            LOG(INFO) << n->v << " ";
            stack.back();
            stack.pop_back();
            last = n;
            n = nullptr;
        } else {
            n = n->r;
        }

    }
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

    while (n != nullptr) {
        if (n->l == nullptr) {
            LOG(INFO) << n->v << " ";
            n = n->r;
            continue;
        }

        pre = n->l;
        while (pre->r && pre->r != n) {
            pre = pre->r;
        }

        if (pre->r == nullptr) {
            LOG(INFO) << n->v << " ";
            pre->r = n;
            n = n->l;
        } else { // if (pre->r == n)
            pre->r = nullptr;
            n = n->r;
        }
    }
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

    while (n != nullptr) {
        if (n->l == nullptr) {
            LOG(INFO) << n->v << " ";
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
            LOG(INFO) << n->v << " ";
            n = n->r;
        }
    }
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
                LOG(INFO) << p->v << " ";
                p = p->r;
            }
            reverse_morris_node(pre, n);

            pre->r = nullptr;
            n = n->r;
        }
    }
}

FTEST(test_binary_tree_travel) {
    TreeNode* root = create_tree();
    LOG(INFO) << "recursive:";
    preorder_recursive_travel(root);
    LOG(INFO);
    inorder_recursive_travel(root);
    LOG(INFO);
    postorder_recursive_travel(root);
    LOG(INFO);

    LOG(INFO) << "\nstack:";
    preorder_stack_travel(root);
    LOG(INFO);
    inorder_stack_travel(root);
    LOG(INFO);
    postorder_stack_travel(root);
    LOG(INFO);

    LOG(INFO) << "\nmorris:";
    preorder_morris_travel(root);
    LOG(INFO);
    inorder_morris_travel(root);
    LOG(INFO);
    postorder_stack_travel(root);
    LOG(INFO);
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

int max_sum_path(TreeNode* p, int& sum, std::vector<std::vector<TreeNode*>>& path) {
    if (p == nullptr) {
        return 0;
    }
    int left = std::max(max_sum_path(p->l, sum, path), 0);
    int right = std::max(max_sum_path(p->r, sum, path), 0);

    int sum_in = left+right+p->v;
    if (sum_in >= sum) {
        path.emplace_back(p);
        sum = sum_in;
    } else {

    }

    return std::max(left, right) + p->v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
