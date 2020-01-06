#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex37 {

/**
 ///////////// 371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = -2, b = 3
Output: 1
 */
int getSum(int a, int b) {
    int res = 0;
    bool carry = false;
    for (int i = 0; i < 32; ++i) {
        int mask = 1 << i;
        int count = 0;
        count += (a & mask) != 0 ? 1 : 0;
        count += (b & mask) != 0 ? 1 : 0;
        count += carry ? 1 : 0;
        carry = count > 1;
        res |= count % 2 == 1 ? mask : 0;
    }
    return res;
}

FTEST(test_getSum) {
    auto t = [&](int a, int b) {
        auto re = getSum(a, b);
        LOG(INFO) << a << " + " << b << " = " << re;
        return re;
    };

    FEXP(t(0, 0), 0);
    FEXP(t(0, 1), 1);
    FEXP(t(1, 0), 1);
    FEXP(t(1, 1), 2);
    FEXP(t(1, 2), 3);
    FEXP(t(0, INT_MIN), INT_MIN);
    FEXP(t(0, INT_MAX), INT_MAX);
    FEXP(t(INT_MIN, INT_MAX), -1);
    FEXP(t(-2, 3), 1);
}

/**
 ///////////// 372.

 */


/**
 ///////////// 373.

 */


/**
 ///////////// 374.

 */


/**
 ///////////// 375.

 */


/**
 ///////////// 376.

 */


/**
 ///////////// 377.

 */


/**
 ///////////// 378. Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending order,
 find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.

Note:
You may assume k is always valid, 1 ≤ k ≤ n^2.
 */
int kthSmallestMatrix(std::vector<std::vector<int>>& matrix, int k) {
    size_t n = matrix.size();
    std::priority_queue<int> qq;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            qq.emplace(matrix[i][j]);
            if (qq.size() > k) {
                qq.pop();
            }
        }
    }
    return qq.top();
}

FTEST(test_kthSmallestMatrix) {
    auto t = [&](const std::vector<std::vector<int>>& matrix, int k) {
        std::vector<std::vector<int>> nns = matrix;
        auto re = kthSmallestMatrix(nns, k);
        LOG(INFO) << matrix << " " << k << "th " << " = " << re;
        return re;
    };

    FEXP(t({{1}}, 1), 1);
    FEXP(t({{1, 2}, {2, 3}}, 1), 1);
    FEXP(t({{1, 2}, {2, 3}}, 2), 2);
    FEXP(t({{1, 2}, {2, 3}}, 3), 2);
    FEXP(t({{1, 2}, {2, 3}}, 4), 3);
    FEXP(t({{1, 2}, {3, 4}}, 1), 1);
    FEXP(t({{1, 2}, {3, 4}}, 2), 2);
    FEXP(t({{1, 2}, {3, 4}}, 3), 3);
    FEXP(t({{1, 2}, {3, 4}}, 4), 4);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 1), 1);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 2), 5);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 3), 9);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 4), 10);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 5), 11);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 6), 12);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 7), 13);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 8), 13);
    FEXP(t({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 9), 15);

}

/**
 ///////////// 379.

 */


/**
 ///////////// 380. Insert Delete GetRandom O(1)
Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements.
 Each element must have the same probability of being returned.

Example:
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();
// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);
// Returns false as 2 does not exist in the set.
randomSet.remove(2);
// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);
// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();
// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);
// 2 was already in the set, so return false.
randomSet.insert(2);
// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

 **
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (_mm.count(val) == 0) {
            _nums.emplace_back(val);
            _mm.emplace(val, _nums.size() - 1);
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto entry = _mm.find(val);
        if (entry != _mm.end()) {
            _nums[entry->second] = _nums.back();
            _mm[_nums.back()] = entry->second;
            _nums.pop_back();
            _mm.erase(entry);
            return true;
        }
        return false;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return _nums[rand() % _nums.size()];
    }

private:
    std::vector<int> _nums;
    std::unordered_map<int, int> _mm;
};

}