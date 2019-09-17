
#pragma once

#include <math.h>
#include "util.hpp"

struct LCListNode {
    int val;
    LCListNode* next;

    explicit LCListNode(int x) : val(x), next(nullptr) {}

};

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

LCListNode* list_convert_leetcode(LinkNode* p) {
    if (p == nullptr) {
        return nullptr;
    }

    LCListNode* head = nullptr;
    LCListNode* prev = nullptr;
    while (p) {
        LCListNode* lc = new LCListNode(p->v);
        if (head == nullptr) {
            head = lc;
            prev = lc;

            p = p->next;
            continue;
        }

        prev->next = lc;
        prev = lc;
        p = p->next;
    }
    return head;
}

void print_list(LinkNode* n) {
    if (n == nullptr) {
        LOG(INFO) << "NULL";
        return;
    }
    std::stringstream ss;
    while (n) {
        ss << n->v << ", ";
        n = n->next;
    }
    LOG(INFO) << ss.str();
}

void print_list(LCListNode* n) {
    if (n == nullptr) {
        LOG(INFO) << "NULL";
        return;
    }
    std::stringstream ss;
    while (n) {
        ss << n->val << ", ";
        n = n->next;
    }
    LOG(INFO) << ss.str();
}

FTEST(test_list) {
    LinkNode* l = create_list({1, 2, 3, 4, 5});
    print_list(l);

    LCListNode* lc = list_convert_leetcode(l);
    print_list(lc);
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

FTEST(test_reverse_list) {
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

LinkNode* add_two_list(LinkNode* l, LinkNode* r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }

    l = reverse_list(l);
    r = reverse_list(r);

    LinkNode* lp = l;
    LinkNode* rp = r;

    int carry = 0;
    while (lp && rp) {
        int count = (lp->v + rp->v + carry) % 10;
        carry = (lp->v + rp->v + carry) / 10;
        lp->v = count;
        rp->v = count;
        lp = lp->next;
        rp = rp->next;
    }

    LinkNode* rest = lp ? lp : rp;
    LinkNode* pre = rest;
    while (rest) {
        pre = rest;
        int count = (rest->v + carry) % 10;
        carry = (rest->v + carry) / 10;
        rest->v = count;
        rest = rest->next;
    }
    if (carry != 0) {
        pre->next = new LinkNode(carry);
    }

    l = reverse_list(l);
    r = reverse_list(r);

    return lp ? l : r;
}

FTEST(test_add_two_list) {
    LinkNode* res = add_two_list(nullptr, nullptr);
    print_list(res);

    LinkNode* l = create_list({1, 2, 3, 4});
    LinkNode* r = create_list({3, 4, 5});
    res = add_two_list(l, r);
    print_list(res);

    l = create_list({1, 2, 5, 5});
    r = create_list({3, 4, 5});
    res = add_two_list(r, l);
    print_list(res);

    l = create_list({9, 9, 5, 5});
    r = create_list({7, 4, 5});
    res = add_two_list(r, l);
    print_list(res);
}
