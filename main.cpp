#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <limits.h>
#include <string.h>
#include <functional>

void print_rhombus(int n) {
    if (n <= 0) {
        return;
    }

    int max_count = 2 * n + 1;

    for (int i = 0 - n; i <= n; ++i) {
        int count = 2 * (n - abs(i)) + 1;
        int delta = (max_count - count) / 2;

        for (int c = 0; c < max_count; ++c) {
            if (c < delta || c >= delta + count) {
                std::cout << " ";
            } else {
                std::cout << "*";
            }
        }
        std::cout << std::endl;
    }
}

void test_print_rhombus() {
//    print_rhombus(0);
    print_rhombus(1);
    print_rhombus(2);
//    print_rhombus(3);
    print_rhombus(8);
//    print_rhombus(16);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

struct LinkNode {
    explicit LinkNode(int value) : v(value) {}

    int v;
    LinkNode* next = nullptr;
};

LinkNode* create_list(const std::vector<int>& nums) {
    LinkNode* root = nullptr;
    LinkNode* cur = nullptr;
    for (int num : nums) {
        LinkNode* n = new LinkNode(num);
        if (cur == nullptr) {
            cur = n;
            root = n;
        } else {
            cur->next = n;
            cur = n;
        }
    }
    return root;
}

void print_list(LinkNode* n) {
    while (n) {
        std::cout << n->v << ", ";
        n = n->next;
    }

    std::cout << std::endl;
}

LinkNode* reverse_list(LinkNode* n) {
    if (n == nullptr) {
        return nullptr;
    }
    if (n->next == nullptr) {
        return n;
    }

    LinkNode* pre = n;
    n = n->next;
    pre->next = nullptr;

    while (n) {
        LinkNode* next = n->next;

        n->next = pre;
        pre = n;
        n = next;
    }
    return pre;
}

void test_reverse_list() {
    LinkNode* root = create_list({});
    print_list(root);
    root = reverse_list(root);
    print_list(root);

    root = create_list({1});
    print_list(root);
    root = reverse_list(root);
    print_list(root);

    root = create_list({1, 2});
    print_list(root);
    root = reverse_list(root);
    print_list(root);

    root = create_list({1, 2, 3});
    print_list(root);
    root = reverse_list(root);
    print_list(root);

    root = create_list({1, 2, 3, 4});
    print_list(root);
    root = reverse_list(root);
    print_list(root);

    root = create_list({1, 2, 3, 4, 5});
    print_list(root);
    root = reverse_list(root);
    print_list(root);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void reverse_stack_put(std::vector<int>& stack, int value) {
    if (stack.empty()) {
        stack.push_back(value);
        return;
    }

    int top = stack.back();
    stack.pop_back();

    reverse_stack_put(stack, value);
    stack.push_back(top);
}

void reverse_stack(std::vector<int>& stack) {
    if (stack.size() <= 1) {
        return;
    }

    int top = stack.back();
    stack.pop_back();

    reverse_stack(stack);
    reverse_stack_put(stack, top);
}

void test_reverse_stack() {
    std::vector<int> s{1, 2, 3, 4, 5};
    for (int i : s) {
        std::cout << i << ",";
    }
    std::cout << std::endl;

    reverse_stack(s);
    for (int i : s) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

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
TreeNode n0(0);
TreeNode n1(1);
TreeNode n2(2);
TreeNode n3(3);
TreeNode n4(4);
TreeNode n5(5);

TreeNode* create_tree() {

    n0.l = &n1;
    n1.p = &n0;

    n0.r = &n2;
    n2.p = &n0;

    n1.l = &n3;
    n3.p = &n1;

    n1.r = &n4;
    n4.p = &n1;

    n2.l = &n5;
    n5.p = &n2;

    return &n0;
}

void preorder_stack_travel(TreeNode* n) {
    std::vector<TreeNode*> stack;

    std::cout << "preorder travel: ";
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            std::cout << n->v << " ";
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

    std::cout << "inorder travel: ";
    while (n != nullptr || !stack.empty()) {
        if (n != nullptr) {
            stack.emplace_back(n);
            n = n->l;
        } else {
            n = stack.back();
            stack.pop_back();
            std::cout << n->v << " ";
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
            std::cout << n->v << " ";
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

    std::cout << n->v << " ";
    preorder_recursive_travel(n->l);
    preorder_recursive_travel(n->r);
}

void inorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    inorder_recursive_travel(n->l);
    std::cout << n->v << " ";
    inorder_recursive_travel(n->r);
}

void postorder_recursive_travel(TreeNode* n) {
    if (n == nullptr) {
        return;
    }

    postorder_recursive_travel(n->l);
    postorder_recursive_travel(n->r);
    std::cout << n->v << " ";
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
            std::cout << n->v << " ";
            n = n->r;
            continue;
        }

        pre = n->l;
        while (pre->r && pre->r != n) {
            pre = pre->r;
        }

        if (pre->r == nullptr) {
            std::cout << n->v << " ";
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
            std::cout << n->v << " ";
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
            std::cout << n->v << " ";
            n = n->r;
        }
    }
}

void reverse_morris_node(TreeNode* from, TreeNode* to) {
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
                std::cout << p->v << " ";
                p = p->r;
            }
            reverse_morris_node(pre, n);

            pre->r = nullptr;
            n = n->r;
        }
    }
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

int tree_height(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }

    return std::max(tree_height(n->l), tree_height(n->r)) + 1;
}

void test_binary_tree_travel() {
    TreeNode* root = create_tree();
    std::cout << "tree height: " << tree_height(root) << std::endl;

    std::cout << "recursive:" << std::endl;
    preorder_recursive_travel(root);
    std::cout << std::endl;
    inorder_recursive_travel(root);
    std::cout << std::endl;
    postorder_recursive_travel(root);
    std::cout << std::endl;

    std::cout << "\nstack:" << std::endl;
    preorder_stack_travel(root);
    std::cout << std::endl;
    inorder_stack_travel(root);
    std::cout << std::endl;
    postorder_stack_travel(root);
    std::cout << std::endl;

    std::cout << "\nmorris:" << std::endl;
    preorder_morris_travel(root);
    std::cout << std::endl;
    inorder_morris_travel(root);
    std::cout << std::endl;
    postorder_stack_travel(root);
    std::cout << std::endl;

    std::cout << "\nnext node of:" << std::endl;
    int ret = next_node_of_inorder_travel(&n0);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
    ret = next_node_of_inorder_travel(&n1);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
    ret = next_node_of_inorder_travel(&n2);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
    ret = next_node_of_inorder_travel(&n3);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
    ret = next_node_of_inorder_travel(&n4);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
    ret = next_node_of_inorder_travel(&n5);
    if (ret != -1) {
        std::cout << ret << std::endl;
    } else {
        std::cout << "no next" << std::endl;
    }
}

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
void sort(std::vector<int>& nums);

void premute(std::vector<int>& nums, int start, std::vector<std::vector<int>>& res) {
    if (start >= nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); ++i) {
        int j = i - 1;
        while (j >= start && nums[j] != nums[i]) {
            --j;
        }
        if (j != start - 1) {
            continue;
        }

        std::swap(nums[start], nums[i]);
        premute(nums, start + 1, res);
        std::swap(nums[start], nums[i]);
    }
}

void premute2(std::vector<int>& nums, size_t level, std::vector<size_t>& visit,
        std::vector<size_t>& out, std::vector<std::vector<size_t>>& res) {
    if (level >= nums.size()) {
        res.push_back(out);
        return;
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        if (visit[i] == 1) {
            continue;
        }
        if (i > 0 && nums[i] == nums[i - 1] && visit[i - 1] == 0) {
            continue;
        }
        visit[i] = 1;
        out.emplace_back(nums[i]);
        premute2(nums, level + 1, visit, out, res);
        out.pop_back();
        visit[i] = 0;
    }
}

void do_premutation(std::vector<int> nums) {
    std::vector<std::vector<int>> res;
    premute(nums, 0, res);

    for (auto& r : res) {
        for (int n : r) {
            std::cout << n << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void do_premutation2(std::vector<int> nums) {
    std::vector<size_t> visit(nums.size(), 0);
    std::vector<std::vector<size_t>> res;
    std::vector<size_t> out;
    sort(nums);
    premute2(nums, 0, visit, out, res);

    for (auto& r : res) {
        for (int n : r) {
            std::cout << n << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_premutation() {
    do_premutation({4, 5, 6});
    do_premutation({7, 7, 8});

    do_premutation2({6, 5, 4});
    do_premutation2({7, 8, 7});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[left];

    while (left < right) {
        while (right > left && nums[right] >= pivot) {
            --right;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] <= pivot) {
            ++left;
        }
        nums[right] = nums[left];
    }
    nums[left] = pivot;

    return left;
}

void qsort(std::vector<int>& nums, int start, int end) {
    if (nums.empty() || start >= end) {
        return;
    }

    int m = partition(nums, start, end);
    qsort(nums, start, m - 1);
    qsort(nums, m + 1, end);
}

void sort(std::vector<int>& nums) {
    qsort(nums, 0, nums.size() - 1);
}

void test_qsort_item(std::vector<int> nums) {
    sort(nums);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

void test_qsort() {
    test_qsort_item({});
    test_qsort_item({1});
    test_qsort_item({1, 2});
    test_qsort_item({1, 2, 3});
    test_qsort_item({1, 2, 3, 4});
    test_qsort_item({1, 1});
    test_qsort_item({1, 1, 2});
    test_qsort_item({1, 2, 2});
    test_qsort_item({2, 1, 2});
    test_qsort_item({2, 1});
    test_qsort_item({2, 2, 1});
    test_qsort_item({2, 1, 1});
    test_qsort_item({1, 2, 1});
    test_qsort_item({3, 2, 1});
    test_qsort_item({4, 2, 1});
    test_qsort_item({-1, -1, 0});
    test_qsort_item({0, -1, -1});
    test_qsort_item({1, 0, -1});
    test_qsort_item({-1, 0, 1});
    test_qsort_item({6, 2, 8, 1, 5, 7});
    test_qsort_item({-6, -2, -8, -1, -5, -7});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void search_palindrome(std::string s, int left, int right, int& start, int& maxLen) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    if (maxLen < right - left - 1) {
        start = left + 1;
        maxLen = right - left - 1;
    }
}

std::string longest_palindrome(std::string s) {
    if (s.size() < 2) return s;
    int n = s.size(), maxLen = 0, start = 0;
    for (int i = 0; i < n - 1; ++i) {
        search_palindrome(s, i, i, start, maxLen);
        search_palindrome(s, i, i + 1, start, maxLen);
    }
    return s.substr(start, maxLen);
}

std::string longest_palindrome2(std::string s) {
    if (s.empty()) {
        return "";
    }

    int n = s.size();
    int len = 1;
    int left = 0;
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
        for (int j = 0; j < i; ++j) {
//            dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
            if (i == j + 1) {
                dp[j][i] = s[i] == s[j];
            } else if (i > j + 1) {
                dp[j][i] = s[i] == s[j] && dp[j + 1][i - 1];
            }

            if (dp[j][i] && len < i - j + 1) {
                len = i - j + 1;
                left = j;
            }
        }
    }

    return s.substr(left, len);
}

void test_longest_palindrome() {
    std::cout << longest_palindrome("") << std::endl;
    std::cout << longest_palindrome("a") << std::endl;
    std::cout << longest_palindrome("aa") << std::endl;
    std::cout << longest_palindrome("baa") << std::endl;
    std::cout << longest_palindrome("aab") << std::endl;
    std::cout << longest_palindrome("ab") << std::endl;
    std::cout << longest_palindrome("abab") << std::endl;
    std::cout << longest_palindrome("aba") << std::endl;
    std::cout << longest_palindrome("ebababb") << std::endl;

    std::cout << longest_palindrome2("") << std::endl;
    std::cout << longest_palindrome2("a") << std::endl;
    std::cout << longest_palindrome2("aa") << std::endl;
    std::cout << longest_palindrome2("baa") << std::endl;
    std::cout << longest_palindrome2("aab") << std::endl;
    std::cout << longest_palindrome2("ab") << std::endl;
    std::cout << longest_palindrome2("abab") << std::endl;
    std::cout << longest_palindrome2("aba") << std::endl;
    std::cout << longest_palindrome2("ebababb") << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int length_of_longest_substring(std::string s) {
    std::vector<int> m(128, -1);
    int res = 0, left = -1;
    for (int i = 0; i < s.size(); ++i) {
        left = std::max(left, m[s[i]]);
        m[s[i]] = i;
        res = std::max(res, i - left);
    }
    return res;
}

int length_of_longest_substring_two_distinct(std::string s) {
    int res = 0, left = 0;
    std::unordered_map<char, int> m;
    for (int i = 0; i < s.size(); ++i) {
        ++m[s[i]];
        while (m.size() > 2) {
            if (--m[s[left]] == 0) {
                m.erase(s[left]);
            }
            ++left;
        }
        res = std::max(res, i - left + 1);
    }
    return res;
}

void test_len_of_longest_substr() {
    length_of_longest_substring_two_distinct("eceba");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void min_heap_fixup(int a[], int i) {
    int j;
    int temp = a[i];
    j = (i - 1) / 2;      //父结点
    while (j >= 0 && i != 0) {
        if (a[j] <= temp) {
            break;
        }

        a[i] = a[j];     //把较大的子结点往下移动,替换它的子结点
        i = j;
        j = (i - 1) / 2;
    }
    a[i] = temp;
}

void min_heap_fixdown(int a[], int i, int n) {
    int j, temp;

    temp = a[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j + 1 < n && a[j + 1] < a[j]) { //在左右孩子中找最小的
            j++;
        }

        if (a[j] >= temp) {
            break;
        }

        a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
        i = j;
        j = 2 * i + 1;
    }
    a[i] = temp;
}

void min_heap_add(int a[], int n, int nNum) {
    a[n] = nNum;
    min_heap_fixup(a, n);
}

void min_heap_delete(int a[], int n) {
    std::swap(a[0], a[n - 1]);
    min_heap_fixdown(a, 0, n - 1);
}

void create_min_heap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heap_fixdown(a, i, n);
    }
}

void min_heap_sort(int a[], int n) {
    for (int i = n - 1; i >= 1; i--) {
        std::swap(a[i], a[0]);
        min_heap_fixdown(a, 0, i);
    }
}

void test_heap() {
    int nums[] = {2, 5, 1, 7, 8, 4, 3, 6};
    int len = sizeof(nums) / sizeof(nums[0]);
    create_min_heap(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_add(nums, len, 9);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_delete(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class SkipList {
private:
    struct Node {
        int k;
        std::string v;
        std::vector<Node*> nexts;
    };

public:
    void add(int k, const std::string& v) {
        size_t level = rand_level();
        if (level >= _head.nexts.size()) {
            _head.nexts.push_back(nullptr);
            level = _head.nexts.size() - 1;
        }

        std::vector<Node*> pres(level + 1, &_head);
        Node* n = nullptr;
        for (int i = level; i >= 0; --i) {
            if (n == nullptr) {
                n = _head.nexts[i];
            }
            Node* pre = pres[i];
            while (n != nullptr) {
                if (k == n->k) {
                    n->v = v;
                    return;
                }
                if (k < n->k) {
                    pres[i] = pre;
                    n = pre;
                    break;
                }

                pre = n;
                pres[i] = pre;
                n = n->nexts[i];
            }
        }

        Node* c = new Node();
        c->k = k;
        c->v = v;
        c->nexts.resize(pres.size(), nullptr);

        for (int i = pres.size() - 1; i >= 0; --i) {
            c->nexts[i] = pres[i]->nexts[i];
            pres[i]->nexts[i] = c;
        }
    }

    std::string get(int k) {
        Node* pre = nullptr;
        Node* n = get_node(k, pre);
        return n == nullptr ? "no key" : n->v;
    }

    void earse(int k) {
        if (_head.nexts.empty()) {
            return;
        }

        size_t level = _head.nexts.size() - 1;
        Node* n = nullptr;
        Node* pre = nullptr;
        for (int i = level; i >= 0; --i) {
            if (n == nullptr) {
                n = _head.nexts[i];
                pre = &_head;
            }
            while (n != nullptr) {
                if (k == n->k) {
                    pre->nexts[i] = n->nexts[i];
                    n = pre;
                    continue;
                }
                if (k < n->k) {
                    n = pre;
                    break;
                }

                pre = n;
                n = n->nexts[i];
            }
        }

        if (!_head.nexts.empty()) {
            if (_head.nexts[_head.nexts.size() - 1] == nullptr) {
                _head.nexts.pop_back();
            }
        }
    }

    void debug_structure() {
        std::cout << "=========" << std::endl;
        if (_head.nexts.empty()) {
            std::cout << "null\n=========" << std::endl;
            return;
        }

        size_t max_len = 0;
        for (int i = 0; i >= 0; --i) {
            size_t len = 0;
            Node* n = _head.nexts[0];
            while (n != nullptr) {
                ++len;
                n = n->nexts[i];
            }

            if (len > max_len) {
                max_len = len;
            }
        }

        std::map<int, size_t> key_pos;
        Node* n = _head.nexts[0];
        size_t idx = 0;
        while (n != nullptr) {
            key_pos.emplace(n->k, idx);
            n = n->nexts[0];
            ++idx;
        }

        for (int i = _head.nexts.size() - 1; i >= 0; --i) {
            n = _head.nexts[i];
            std::cout << "[" << i << "]->";

            idx = 0;
            while (n != nullptr) {
                if (idx != key_pos[n->k]) {
                    std::cout << "->->-->";
                } else {
                    std::cout << "(" << n->k << ":" << n->v << ")->";
                    n = n->nexts[i];
                }
                ++idx;
            }
            while (idx < max_len) {
                std::cout << "->->-->";
                ++idx;
            }
            std::cout << "null" << std::endl;
        }
        std::cout << "=========" << std::endl;
    }

private:
    Node* get_node(int k, Node*& pre) {
        if (_head.nexts.empty()) {
            pre = nullptr;
            return nullptr;
        }

        size_t level = _head.nexts.size() - 1;
        Node* n = _head.nexts[level];
        pre = &_head;
        while (n != nullptr && level >= 0) {
            if (k == n->k) {
                return n;
            }
            if (k < n->k) {
                n = pre->nexts[--level];
                continue;
            }

            pre = n;
            n = n->nexts[level];
        }

        return nullptr;
    }

    size_t rand_level() {
//        srand(time(nullptr));
//        size_t level = 0;
//        while (rand() % 2 == 0) {
//            ++level;
//        }
//        return level;
        return _head.nexts.size();
    }

private:
    Node _head;
};

void test_skiplist() {
    SkipList sl;
    std::cout << sl.get(0) << std::endl;

    sl.add(0, "a");
    sl.debug_structure();
    std::cout << sl.get(0) << std::endl;

    sl.add(1, "b");
    sl.debug_structure();

    sl.add(5, "f");
    sl.debug_structure();

    sl.add(3, "d");
    sl.debug_structure();

    std::cout << sl.get(0) << std::endl;
    std::cout << sl.get(1) << std::endl;
    std::cout << sl.get(3) << std::endl;
    std::cout << sl.get(5) << std::endl;

    sl.add(2, "c");
    sl.debug_structure();

    sl.earse(2);
    sl.debug_structure();

    sl.earse(1);
    sl.debug_structure();

    sl.earse(3);
    sl.debug_structure();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void debug_lcs_seq(const std::string& s1, const std::string& s2,
        const std::vector<std::vector<int>>& seqs) {
    std::cout << "\\| ";
    for (size_t j = 1; j <= s2.size(); ++j) {
        std::cout << s2[j - 1] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 1; i <= s1.size(); ++i) {
        std::cout << s1[i - 1] << "| ";
        for (size_t j = 1; j <= s2.size(); ++j) {
            std::cout << seqs[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @param direction  0, left; 1, up
 */
void lcs_path(const std::string& s1, const std::string& s2, int s1_pos, int s2_pos,
        int direction, const std::vector<std::vector<int>>& seqs, std::string& seq,
        std::vector<std::string>& results) {

    size_t i = s1_pos;
    size_t j = s2_pos;
    while (i > 0 && j > 0) {

        if (s1[i - 1] == s2[j - 1]) {
            seq = s1[i - 1] + seq;
            --i;
            --j;
            continue;
        }

        if (seqs[i - 1][j] > seqs[i][j - 1]) { // move up
            --i;
        } else if (seqs[i - 1][j] < seqs[i][j - 1]) { // move left
            --j;
        } else {
            //chose a direction, recuresive for multiple path
            if (direction == 1 && j != s2_pos) {
                std::string seq_left = seq;
                lcs_path(s1, s2, i, j - 1, 0, seqs, seq_left, results);
            }
            if (direction == 0 && i != s1_pos) {
                std::string seq_right = seq;
                lcs_path(s1, s2, i - 1, j, 1, seqs, seq_right, results);
            }
            if (direction == 0) {
                --j;
            } else {
                --i;
            }
        }
    }
    results.emplace_back(seq);
}

void lcs(const std::string& s1, const std::string& s2, std::vector<std::string>& results) {
    if (s1.empty() || s2.empty()) {
        return;
    }

    std::vector<std::vector<int>> seqs;
    for (size_t i = 0; i <= s1.size(); ++i) {
        seqs.emplace_back(std::vector<int>());
        for (size_t j = 0; j <= s2.size(); ++j) {
            seqs[i].emplace_back(0);
        }
    }

    for (size_t i = 0; i < s1.size(); ++i) {
        for (size_t j = 0; j < s2.size(); ++j) {
            if (s1[i] == s2[j]) {
                seqs[i + 1][j + 1] = seqs[i][j] + 1;
            } else {
                seqs[i + 1][j + 1] = std::max(seqs[i + 1][j], seqs[i][j + 1]);
            }
        }
    }

    debug_lcs_seq(s1, s2, seqs);

    std::string seq;
    lcs_path(s1, s2, s1.size(), s2.size(), 0, seqs, seq, results);
}

void test_lcs() {
    std::string a = "13456778";
    std::string b = "357486782";
    std::vector<std::string> seqs;

    lcs(a, b, seqs);

    for (auto& seq : seqs) {
        std::cout << seq << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

size_t edit_distance_recusive_handle(const std::string& s1, const std::string& s2, size_t i,
        size_t j, std::vector<std::vector<size_t>>& counts) {
    if (i == s1.size()) {
        return s2.size() - j;
    }
    if (j == s2.size()) {
        return s1.size() - i;
    }
    if (counts[i][j] > 0) {
        return counts[i][j];
    }

    if (s1[i] == s2[j]) {
        return edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    }

    size_t insert_count = edit_distance_recusive_handle(s1, s2, i, j + 1, counts);
    size_t delete_count = edit_distance_recusive_handle(s1, s2, i + 1, j, counts);
    size_t update_count = edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    size_t count = std::min(insert_count, std::min(delete_count, update_count)) + 1;
    counts[i][j] = count;
    return count;
}

size_t edit_distance_recusive(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";
    std::vector<std::vector<size_t>> counts(s1.size(), std::vector<size_t>(s2.size()));
    return edit_distance_recusive_handle(s1, s2, 0, 0, counts);
}

size_t edit_distance_dp(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";

    std::vector<std::vector<size_t>> counts(s1.size() + 1, std::vector<size_t>(s2.size() + 1));
    for (size_t i = 0; i <= s1.size(); ++i) {
        counts[i][0] = i;
    }
    for (size_t i = 0; i <= s2.size(); ++i) {
        counts[0][i] = i;
    }

    for (size_t i = 1; i <= s1.size(); ++i) {
        for (size_t j = 1; j <= s2.size(); ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                counts[i][j] = counts[i - 1][j - 1];
            } else {
                counts[i][j] = std::min(counts[i - 1][j - 1],
                        std::min(counts[i - 1][j], counts[i][j - 1])) + 1;
            }
        }
    }
    return counts[s1.size()][s2.size()];
}

void test_edit_distance() {
    std::cout << edit_distance_recusive("", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "") << std::endl;
    std::cout << edit_distance_recusive("", "") << std::endl;
    std::cout << edit_distance_recusive("1", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "2") << std::endl;
    std::cout << edit_distance_recusive("2", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "11") << std::endl;
    std::cout << edit_distance_recusive("1", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "1") << std::endl;
    std::cout << edit_distance_recusive("12", "1") << std::endl;
    std::cout << edit_distance_recusive("11", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "22") << std::endl;

    std::cout << std::endl;

    std::cout << edit_distance_dp("", "1") << std::endl;
    std::cout << edit_distance_dp("1", "") << std::endl;
    std::cout << edit_distance_dp("", "") << std::endl;
    std::cout << edit_distance_dp("1", "1") << std::endl;
    std::cout << edit_distance_dp("1", "2") << std::endl;
    std::cout << edit_distance_dp("2", "1") << std::endl;
    std::cout << edit_distance_dp("1", "11") << std::endl;
    std::cout << edit_distance_dp("1", "12") << std::endl;
    std::cout << edit_distance_dp("11", "1") << std::endl;
    std::cout << edit_distance_dp("12", "1") << std::endl;
    std::cout << edit_distance_dp("11", "12") << std::endl;
    std::cout << edit_distance_dp("11", "22") << std::endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////////

int kth_of_two(const std::vector<int>& nums1, const std::vector<int>& nums2,
        size_t i, size_t j, size_t k) {
    if (i >= nums1.size()) {
        return nums2[j + k - 1];
    }
    if (j >= nums2.size()) {
        return nums1[i + k - 1];
    }
    if (k == 1) {
        return std::min(nums1[i], nums2[j]);
    }

    // if exist the K th number
    int mv1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
    int mv2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
    if (mv1 < mv2) {
        return kth_of_two(nums1, nums2, i + k / 2, j, k - k / 2);
    } else {
        return kth_of_two(nums1, nums2, i, j + k / 2, k - k / 2);
    }
}

double median_of_two(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    size_t i = nums1.size();
    size_t j = nums2.size();
    size_t left = (i + j + 1) / 2;
    size_t right = (i + j + 2) / 2;
    return (kth_of_two(nums1, nums2, 0, 0, left) + kth_of_two(nums1, nums2, 0, 0, right)) / 2.0;
}

double median_of_two_iteration(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int i = nums1.size();
    int j = nums2.size();
    if (i > j) {
        return median_of_two_iteration(nums2, nums1);
    }
    size_t l = 0;
    size_t h = 2 * i;
    size_t c1;
    size_t c2;
    int l1;
    int l2;
    int r1;
    int r2;
    while (l <= h) {
        c1 = (l + h) / 2;
        c2 = i + j - c1;
        l1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
        r1 = (c1 == 2 * i) ? INT_MAX : nums1[c1 / 2];
        l2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
        r2 = (c2 == 2 * j) ? INT_MAX : nums2[c2 / 2];

        if (l1 > r2) {
            h = c1 - 1;
        } else if (l2 > r1) {
            l = c1 + 1;
        } else {
            break;
        }
    }
    return (std::max(l1, l2) + std::min(r1, r2)) / 2.0;
}

void test_median_of_two() {
    std::cout << "recursive: " << std::endl;
    std::cout << median_of_two({0}, {0}) << std::endl;
    std::cout << median_of_two({1}, {1}) << std::endl;
    std::cout << median_of_two({0}, {1}) << std::endl;
    std::cout << median_of_two({1, 3}, {2}) << std::endl;
    std::cout << median_of_two({1, 2}, {3, 4}) << std::endl;
    std::cout << median_of_two({1, 2}, {2, 4}) << std::endl;
    std::cout << median_of_two({4, 4}, {4, 4}) << std::endl;

    std::cout << "\niteration: " << std::endl;
    std::cout << median_of_two_iteration({0}, {0}) << std::endl;
    std::cout << median_of_two_iteration({1}, {1}) << std::endl;
    std::cout << median_of_two_iteration({0}, {1}) << std::endl;
    std::cout << median_of_two_iteration({1, 3}, {2}) << std::endl;
    std::cout << median_of_two_iteration({1, 2}, {3, 4}) << std::endl;
    std::cout << median_of_two_iteration({1, 2}, {2, 4}) << std::endl;
    std::cout << median_of_two_iteration({4, 4}, {4, 4}) << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

ssize_t bin_search(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] find " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return -1;
}

ssize_t bin_search_1st_great_equal(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] 1st great equal " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return h + 1 >= nums.size() ? -1 : h + 1;
}

ssize_t bin_search_1st_great(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] 1st great " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return h + 1 >= nums.size() ? -1 : h + 1;
}

void test_bin_search() {
    std::cout << "binary search" << std::endl;
    std::cout << bin_search({}, 1) << std::endl;
    std::cout << bin_search({1}, 0) << std::endl;
    std::cout << bin_search({1}, 2) << std::endl;
    std::cout << bin_search({1}, 1) << std::endl;
    std::cout << bin_search({1, 2}, 0) << std::endl;
    std::cout << bin_search({1, 2}, 3) << std::endl;
    std::cout << bin_search({1, 2}, 1) << std::endl;
    std::cout << bin_search({1, 2}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 3, 5}, 3) << std::endl;

    std::cout << "\nbinary search 1st greater equal" << std::endl;
    std::cout << bin_search_1st_great_equal({}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 3, 5}, 3) << std::endl;

    std::cout << "\nbinary search 1st greater " << std::endl;
    std::cout << bin_search_1st_great({}, 1) << std::endl;
    std::cout << bin_search_1st_great({1}, 0) << std::endl;
    std::cout << bin_search_1st_great({1}, 2) << std::endl;
    std::cout << bin_search_1st_great({1}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 0) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 3, 5}, 3) << std::endl;
}

ssize_t bin_search_rotate(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] find rotate " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < nums[h]) {
            if (nums[mid] < target && nums[h] >= target) {
                // right sorted and target in range
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        } else {
            if (nums[mid] > target && nums[l] <= target) {
                // left sorted and target in range
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    return -1;
}

void test_bin_search_rotate() {
    std::cout << "binary search rotate" << std::endl;
    std::cout << bin_search_rotate({}, 1) << std::endl;
    std::cout << bin_search_rotate({1}, 0) << std::endl;
    std::cout << bin_search_rotate({1}, 2) << std::endl;
    std::cout << bin_search_rotate({1}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 0) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_rotate({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 3, 5}, 3) << std::endl;
    std::cout << bin_search_rotate({}, 1) << std::endl;
    std::cout << bin_search_rotate({1}, 0) << std::endl;
    std::cout << bin_search_rotate({1}, 2) << std::endl;
    std::cout << bin_search_rotate({1}, 1) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 0) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 3) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 1) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 0) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 4) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 0) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 4) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 5) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 5, 1, 2, 3}, 3) << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void kmp_nexts(const std::string& pattern, std::vector<ssize_t>& nexts) {
    if (pattern.empty()) {
        return;
    }
    nexts.resize(pattern.size(), -1);
    ssize_t k = -1;
    int i = 0;
    while (i < pattern.size() - 1) {
        if (k == -1 || pattern[i] == pattern[k]) {
            ++k;
            ++i;
            if (pattern[i] == pattern[k]) {
                nexts[i] = nexts[k];
            } else {
                nexts[i] = k;
            }
        } else {
            k = nexts[k];
        }
    }
}

ssize_t substr_kmp(const std::string& str, const std::string& pattern) {
    std::cout << "\"" << str << "\" kmp substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }

    std::vector<ssize_t> nexts;
    kmp_nexts(pattern, nexts);

    ssize_t i = 0;
    ssize_t j = 0;
    while (i < (ssize_t)str.size() && j < (ssize_t)pattern.size()) {
        if (j == -1 || str[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            j = nexts[j];
        }
    }
    if (j >= pattern.size()) {
        return i - j;
    }
    return -1;
}

void bm_bads(const std::string& pattern, char (& bads)[256]) {
    memset(bads, -1, sizeof(bads));

    for (size_t i = 0; i < pattern.size(); ++i) {
        bads[pattern[i]] = pattern.size() - 1 - i;
    }
}

void bm_goods_suffix(const std::string& pattern, std::vector<size_t>& suffix) {
    suffix.resize(pattern.size(), 0);

    for (size_t i = 0; i < pattern.size(); ++i) {
        if (i == pattern.size() - 1) {
            suffix[i] = pattern.size();
            continue;
        }
        ssize_t j = i;
        while (j >= 0 && pattern[j] == pattern[pattern.size() - 1 - i + j]) {
            --j;
        }
        suffix[i] = i - j;
    }
}

void bm_goods(const std::string& pattern, std::vector<size_t>& goods) {

    std::vector<size_t> suffix;
    bm_goods_suffix(pattern, suffix);

    goods.resize(pattern.size(), pattern.size());

    // full match suffix
    size_t j = 0;
    for (ssize_t i = pattern.size() - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (; j < pattern.size() - 1 - i; j++) {
                if (goods[j] == pattern.size()) { // means no assign value after initialize
                    goods[j] = pattern.size() - 1 - i;
                }
            }
        }
    }

    // partial match suffix
    for (ssize_t i = 0; i <= pattern.size() - 2; i++) {
        goods[pattern.size() - 1 - suffix[i]] = pattern.size() - 1 - i;
    }
}

ssize_t substr_bm(const std::string& str, const std::string& pattern) {
    // FIXME
    std::cout << "\"" << str << "\" bm substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }
    char bads[256];
    std::vector<size_t> goods;
    bm_bads(pattern, bads);
    bm_goods(pattern, goods);

    size_t j = 0;
    while (j <= str.size() - pattern.size()) {
        ssize_t i;
        for (i = pattern.size() - 1; i >= 0 && pattern[i] == str[i + j]; i--) {}
        if (i < 0) {
            j += goods[0];
            return j;
        } else {
            j += std::max(bads[str[i + j]] - pattern.size() + 1, goods[i]);
        }
    }
    return -1;
}

ssize_t substr_sunday(const std::string& str, const std::string& pattern) {
    std::cout << "\"" << str << "\" sunday substr \"" << pattern << "\": ";
    if (str.empty() || pattern.empty() || pattern.size() > str.size()) {
        return -1;
    }

    size_t steps[256] = {pattern.size() + 1};
    for (size_t i = 0; i < pattern.size(); ++i) {
        steps[pattern[i]] = pattern.size() - i;
    }

    size_t i = 0;
    while (i <= str.size() - pattern.size()) {
        size_t j = 0;
        while (str[i + j] == pattern[j]) {
            ++j;
            if (j >= pattern.size()) {
                return i;
            }
        }
        i += steps[str[i + pattern.size()]];
    }

    return -1;
}

void test_substr() {
    std::vector<std::function<ssize_t(const std::string&, const std::string&)>> substr_funcs;
    substr_funcs.emplace_back(substr_kmp);
//    substr_funcs.emplace_back(substr_bm);
    substr_funcs.emplace_back(substr_sunday);

    for (auto& substr : substr_funcs) {
//        std::cout << substr("", "") << std::endl;
//        std::cout << substr("", "1") << std::endl;
//        std::cout << substr("1", "") << std::endl;
//        std::cout << substr("1", "1") << std::endl;
//        std::cout << substr("1", "2") << std::endl;
//        std::cout << substr("12", "") << std::endl;
//        std::cout << substr("12", "1") << std::endl;
//        std::cout << substr("12", "2") << std::endl;
//        std::cout << substr("12", "12") << std::endl;
//        std::cout << substr("12", "123") << std::endl;
//        std::cout << substr("123", "") << std::endl;
//        std::cout << substr("123", "1") << std::endl;
//        std::cout << substr("123", "2") << std::endl;
//        std::cout << substr("123", "12") << std::endl;
//        std::cout << substr("123", "123") << std::endl;
//        std::cout << substr("11233", "123") << std::endl;
        std::cout << substr("abbcabababbc", "bcababab") << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void rb_tree() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void b_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

void avl_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

#include "sums_of_collection.hpp"

int main() {
    test_util();

//    test_print_rhombus();
//    test_reverse_list();
//    test_reverse_stack();
//    test_binary_tree_travel();
//    test_convert_tree_to_linkedlist();
//    test_bst_add_del();
//    test_premutation();
//    test_qsort();
//    test_longest_palindrome();
//    test_len_of_longest_substr();
//    test_heap();
//    test_skiplist();
//    test_lcs();
//    test_edit_distance();
//    test_median_of_two();
//    test_bin_search();
//    test_bin_search_rotate();
//    test_substr();

//    test_two_sum();

    return 0;
}