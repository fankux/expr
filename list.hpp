
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

LCListNode* list_convert_leetcode(LinkNode* p, std::vector<LCListNode*>& nodes) {
    if (p == nullptr) {
        return nullptr;
    }

    LCListNode* head = nullptr;
    LCListNode* prev = nullptr;
    while (p) {
        LCListNode* lc = new LCListNode(p->v);
        nodes.emplace_back(lc);
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

std::string print_list(LinkNode* n) {
    if (n == nullptr) {
        return "NULL";
    }
    std::stringstream ss;
    while (n) {
        ss << n->v << ", ";
        n = n->next;
    }
    return ss.str();
}

std::string print_list(LCListNode* n) {
    if (n == nullptr) {
        return "NULL";
    }
    std::stringstream ss;
    while (n) {
        ss << n->val << ", ";
        n = n->next;
    }
    return ss.str();
}

FTEST(test_list) {
    LinkNode* l = create_list({1, 2, 3, 4, 5});
    print_list(l);

    LCListNode* lc = list_convert_leetcode(l);
    print_list(lc);
}

LinkNode* reverse_list(LinkNode* n) {
    LinkNode* pre = nullptr;
    while (n) {
        LinkNode* next = n->next;
        n->next = pre;
        pre = n;
        n = next;
    }
    return pre;
}

FTEST(test_reverse_list) {
    auto t = [](const std::vector<int>& nums) {
        LinkNode* l1 = create_list(nums);
        LOG(INFO) << "reverse: " << nums;
        print_list(reverse_list(l1));
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({1, 2, 3, 4, 5});
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

///////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class FListNode {
public:
    template<class X> friend
    class FList;

    FListNode() = default;

    virtual ~FListNode() {
        _prev = nullptr;
        _next = nullptr;
    }

    explicit FListNode(const T& data) : _data(data) {}

    T& data() {
        return _data;
    }

    FListNode* next() {
        return _prev;
    };

    FListNode* prev() {
        return _prev;
    };

    friend LogStream& operator<<(LogStream& ls, const FListNode& lock) {
        ls << lock._data;
        return ls;
    }

private:
    FListNode* _prev = nullptr;
    FListNode* _next = nullptr;
    T _data;
};

template<class T>
class FList {
public:
    explicit FList() = default;

    virtual ~FList() {
        clear();
    }

    inline void clear() {
        FListNode<T>* p = _head;
        FListNode<T>* q = p;
        for (size_t i = _len; i > 0; --i) {
            p = p->_next;
            free(q);
            q = p;
        }
        _len = 0;
    }

    inline size_t size() {
        return _len;
    }

    inline bool empty() {
        return _len == 0;
    }

    inline bool add_tail(const T& data) {
        FListNode<T>* node = new(std::nothrow) FListNode<T>(data);
        if (node == nullptr) {
            return false;
        }
        return add_tail(node);
    }

    inline bool add_tail(FListNode<T>* node) {
        if (empty()) {
            node->_prev = nullptr;
            node->_next = nullptr;
            _tail = node;
            _head = _tail;
        } else {
            node->_next = nullptr;
            node->_prev = _tail;
            _tail->_next = node;
            _tail = _tail->_next;
        }
        ++_len;
        return true;
    }

    inline bool add_head(const T& data) {
        FListNode<T>* node = new(std::nothrow) FListNode<T>(data);
        if (node == nullptr) {
            return false;
        }
        return add_head(node);
    }

    inline bool add_head(FListNode<T>* node) {
        if (empty()) {
            node->_prev = nullptr;
            node->_next = nullptr;
            _head = node;
            _tail = _head;
        } else {
            node->_prev = nullptr;
            node->_next = _head;
            _head->_prev = node;
            _head = _head->_prev;
        }
        ++_len;
    }

    inline bool insert(FListNode<T>* pos, FListNode<T>* node) {
        if (node == nullptr) {
            return false;
        }
        if (pos == nullptr) {
            return add_head(node);
        }
        if (pos->_next == nullptr) {
            return add_tail(node);
        }
        node->_prev = pos;
        node->_next = pos->_next;
        pos->_next->_prev = pos;
        pos->_next = pos;
        return true;
    }

    inline FListNode<T>* pop_head() {
        if (empty()) {
            return nullptr;
        }
        FListNode<T>* p = nullptr;
        if (_len == 1) { /* last one node */
            p = _head;
            _head = nullptr;
            _tail = nullptr;
        } else {
            p = _head;
            _head = _head->_next;
            _head->_prev = nullptr;

        }
        --_len;
        return p;
    }

    inline void detach(FListNode<T>* p) {
        if (_len == 1) {
            _head = nullptr;
            _tail = nullptr;
        } else {
            if (p->_prev == nullptr) {
                _head = p->_next;
                p->_next->_prev = nullptr;
            } else if (p->_next == nullptr) {
                _tail = p->_prev;
                p->_prev->_next = nullptr;
            } else {
                p->_next->_prev = p->_prev;
                p->_prev->_next = p->_next;
            }
        }
        --_len;
    }

    inline FListNode<T>* head() {
        return _head;
    }

    inline FListNode<T>* tail() {
        return _tail;
    }

private:
    size_t _len = 0;
    FListNode<T>* _head = nullptr;
    FListNode<T>* _tail = nullptr;
};