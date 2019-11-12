#pragma once

#include "util.hpp"
#include "tree.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *
 *         3
 *       /  \
 *     /     \
 *    1       5
 *   / \     /
 *  0   2   4
 *
 */

TreeNode a0(0);
TreeNode a1(1);
TreeNode a2(2);
TreeNode a3(3);
TreeNode a4(4);
TreeNode a5(5);

void bst_add(TreeNode*& root, int value) {
    TreeNode* n = root;
    TreeNode* p = n;
    while (n) {
        p = n;
        if (value < n->v) {
            n = n->l;
        } else if (value > n->v) {
            n = n->r;
        } else {
            return;
        }
    }

    n = new TreeNode(value);
    if (p == nullptr) {
        root = n;
    } else if (value < p->v) {
        p->l = n;
    } else if (value > p->v) {
        p->r = n;
    }
}

void bst_del(TreeNode*& root, int value) {
    TreeNode* n = root;
    TreeNode* p = nullptr;
    while (n) {
        if (value == n->v) {
            break;
        }

        p = n;
        if (value < n->v) {
            n = n->l;
        } else { // if (value > n->v)
            n = n->r;
        }
    }

    if (n == nullptr) {
        return; // not exist
    }

    if (n->l == nullptr && n->r == nullptr) {
        if (p == nullptr) {
            delete root;
            root = nullptr;
            return;
        }
        if (value < p->v) {
            p->l = nullptr;
        } else { // if (value > p->v)
            p->r = nullptr;
        }
        delete n;

    } else if (n->l != nullptr) {
        TreeNode* next = n->l;
        TreeNode* pre_next = nullptr;
        while (next->r) {
            pre_next = next;
            next = next->r;
        }
        n->v = next->v;
        if (pre_next != nullptr) {
            pre_next->r = nullptr;
        } else {
            n->l = nullptr;
        }
        delete next;

    } else if (n->l == nullptr && n->r != nullptr) {
        TreeNode* next = n->r;
        TreeNode* pre_next = nullptr;
        while (next->l) {
            pre_next = next;
            next = next->l;
        }
        n->v = next->v;
        if (pre_next != nullptr) {
            pre_next->r = nullptr;
        } else {
            n->r = nullptr;
        }
        delete next;
    }
}

TreeNode* create_balance_tree() {
//    a3.l = &a1;
//    a3.r = &a5;
//
//    a1.l = &a0;
//    a1.r = &a2;
//
//    a5.l = &a4;

    TreeNode* root = nullptr;
    bst_add(root, 3);
    bst_add(root, 1);
    bst_add(root, 0);
    bst_add(root, 2);
    bst_add(root, 5);
    bst_add(root, 4);

    return root;
}

void bst_left_rotate(TreeNode*& p) {
    TreeNode* right = p->r;
    if (right == nullptr) {
        return;
    }
    p->r = right->l;
    right->l = p;
    p = right;
}

void bst_right_rotate(TreeNode*& p) {
    TreeNode* left = p->l;
    if (left == nullptr) {
        return;
    }
    p->l = left->r;
    left->r = p;
    p = left;
}

void test_bst_add_del() {
    TreeNode* root = create_balance_tree();
    preorder_stack_travel(root);
    std::cout << std::endl;
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_left_rotate(root);
    preorder_stack_travel(root);
    std::cout << std::endl;
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_right_rotate(root);
    preorder_stack_travel(root);
    std::cout << std::endl;
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_right_rotate(root);
    preorder_stack_travel(root);
    std::cout << std::endl;
    inorder_stack_travel(root);
    std::cout << std::endl;


    bst_del(root, 0);
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_del(root, 3);
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_del(root, 4);
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_del(root, 1);
    bst_del(root, 2);
    inorder_stack_travel(root);
    std::cout << std::endl;

    bst_del(root, 5);
    inorder_stack_travel(root);
    std::cout << std::endl;
}

void convert_tree_to_linkedlist(TreeNode* n, TreeNode** last) {
    if (n == nullptr) {
        return;
    }

    if (n->l != nullptr) {
        convert_tree_to_linkedlist(n->l, last);
    }

    n->l = *last;

    if (*last != nullptr) {
        (*last)->r = n;
    }

    *last = n;

    if (n->r != nullptr) {
        convert_tree_to_linkedlist(n->r, last);
    }
}

void test_convert_tree_to_linkedlist() {
    TreeNode* root = create_balance_tree();
    inorder_recursive_travel(root);
    std::cout << std::endl;

    TreeNode* head = root;
    while (head->l != nullptr) {
        head = head->l;
    }

    TreeNode* last = nullptr;
    convert_tree_to_linkedlist(root, &last);
    std::cout << "convert_tree_to_linkedlist: ";
    while (head != nullptr) {
        std::cout << head->v << " ";
        head = head->r;
    }
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
