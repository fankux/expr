//
// Created by fankux on 2020/1/7.
//

#pragma once

#include "util.hpp"

template<typename T>
class Heap {
public:
    Heap() = default;

    explicit Heap(const std::vector<T>& inits) {
        for (auto& init : inits) {
            push(init);
        }
    }

    void clear() {
        _c.clear();
    }

    bool empty() const {
        return _c.empty();
    }

    size_t size() const {
        return _c.size();
    }

    void push(const T& v) {
        size_t idx = _c.size();
        _c.emplace_back(v);

        while (idx > 0) {
            size_t p_idx = (idx - 1) / 2;
            if (v < _c[p_idx]) {
                break;
            }
            std::swap(_c[idx], _c[p_idx]);
            idx = p_idx;
        }
    }

    void push(const std::vector<T>& list) {
        for (auto& l : list) {
            push(l);
        }
    }

    const T& top() const {
        return _c.front();
    }

    T& top() {
        return _c.front();
    }

    void pop() {
        if (_c.empty()) {
            return;
        }
        _c.front() = _c.back();
        _c.pop_back();

        size_t len = _c.size();
        size_t idx = 0;
        size_t c_idx = 1;
        while (c_idx < len) {
            if (c_idx + 1 < len && _c[c_idx] < _c[c_idx + 1]) {
                // find max value of left and right child
                ++c_idx;
            }
            if (_c[c_idx] < _c[idx]) {
                break;
            }
            std::swap(_c[idx], _c[c_idx]);
            idx = c_idx;
            c_idx = 2 * idx + 1;
        }
    }

    void pop(T& v) {
        if (!empty()) {
            v = _c.top();
            pop();
        }
    }

    std::string print() {
        Heap heap = *this;
        std::string res;
        while (!heap.empty()) {
            res += std::to_string(heap.top()) + " ";
            heap.pop();
        }
        return res;
    }

private:
    std::deque<T> _c;
};

FTEST(test_heap) {
    std::vector<int> nums{2, 5, 1, 7, 8, 4, 3, 6};
    Heap<int> heap(nums);
    LOG(INFO) << heap.print();

    heap.push(9);
    LOG(INFO) << heap.print();

    heap.pop();
    heap.pop();
    LOG(INFO) << heap.print();;
}