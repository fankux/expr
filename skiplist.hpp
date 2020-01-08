//
// Created by fankux on 2020/1/8.
//

#pragma once

#include "util.hpp"

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

FTEST(test_skiplist) {
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
