#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex34 {

/**
 ///////////// 341. Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].

 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
class NestedInteger {
public:
    NestedInteger(int v) {
        _is_int = true;
        _v = v;
    }

    NestedInteger(const std::vector<int>& nums) {
        _is_int = false;
        for (auto num : nums) {
            _list.emplace_back(num);
        }
    }

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const {
        return _is_int;
    }

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const {
        return _v;
    }

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    std::vector<NestedInteger>& getList() {
        return _list;
    }

private:
    bool _is_int = false;
    int _v = 0;
    std::vector<NestedInteger> _list;
};

#define NESTEDITERATOR_STACK 1

class NestedIterator {
public:
#ifdef NESTEDITERATOR_STACK

    NestedIterator(std::vector<NestedInteger>& nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            _ss.emplace(&(nestedList[i]));
        }
    }

    int next() {
        int ret = _ss.top()->getInteger();
        _ss.pop();
        return ret;
    }

    bool hasNext() {
        while (!_ss.empty()) {
            NestedInteger* item = _ss.top();
            if (item->isInteger()) {
                return true;
            }
            _ss.pop();
            for (int i = item->getList().size() - 1; i >= 0; --i) {
                _ss.emplace(&(item->getList()[i]));
            }
        }
        return false;
    }

#else

    NestedIterator(std::vector<NestedInteger>& nestedList) {
        _list = nestedList;
    }

    int next() {
        NestedInteger& item = _list[_idx];
        if (item.isInteger()) {
            ++_idx;
            return item.getInteger();
        }
        return _sub_iter->next();
    }

    bool hasNext() {
        for (; _idx < _list.size() && !_list[_idx].isInteger(); ++_idx) {
            if (_sub_iter == nullptr) {
                _sub_iter = new NestedIterator(_list[_idx].getList());
            }
            if (_sub_iter->hasNext()) {
                return true;
            }
            delete _sub_iter;
            _sub_iter = nullptr;
        }
        return _idx < _list.size();
    }

#endif

private:
#ifdef NESTEDITERATOR_STACK
    std::stack<NestedInteger*> _ss;
#else
    int _idx = 0;
    std::vector<NestedInteger> _list;
    NestedIterator* _sub_iter = nullptr;
#endif
};

FTEST(test_FlattenNestedList) {
    auto t = [](NestedInteger& nested) {
        std::stringstream ss;
        NestedIterator iter(nested.getList());
        while (iter.hasNext()) {
            if (iter.hasNext()) {
                ss << iter.next() << " ";
            }
        }
        LOG(INFO) << ss.str();
    };

    // []
    NestedInteger nested({});
    t(nested);

    // [[]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    t(nested);

    // [[[]]]
    nested.getList().back().getList().emplace_back(std::vector<int>());
    t(nested);

    // [[],[]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    t(nested);

    //[[],[3]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>{3});
    t(nested);

    //[[],[],[3]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>{3});
    t(nested);

    //[[],[3],[]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>{3});
    nested.getList().emplace_back(std::vector<int>());
    t(nested);

    //[[1],[]]
    nested = NestedInteger(std::vector<int>());
    nested.getList().emplace_back(std::vector<int>{1});
    nested.getList().emplace_back(std::vector<int>());
    t(nested);

    //[[1],[],[]]
    nested.getList().emplace_back(std::vector<int>());
    t(nested);

    // [1,[4,[6]]]
    nested = NestedInteger({1, 2});
    nested.getList()[1] = NestedInteger({4, 6});
    nested.getList()[1].getList()[1] = NestedInteger(6);
    t(nested);

    //[[1,1],2,[1,1]]
    nested = NestedInteger({1, 2, 1});
    nested.getList()[0] = NestedInteger({1, 1});
    nested.getList()[2] = NestedInteger({1, 1});
    t(nested);

    // [1,2,3]
    nested = NestedInteger({1, 2, 3});
    t(nested);
}

/**
 ///////////// 342.

 */


/**
 ///////////// 343.

 */


/**
 ///////////// 344. Reverse String
Write a function that reverses a string. The input string is given as an array of characters char[].
Do not allocate extra space for another array,
 you must do this by modifying the input array in-place with O(1) extra memory.

You may assume all the characters consist of printable ascii characters.

Example 1:
Input: ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:
Input: ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
 */
void reverseString(std::vector<char>& s) {
    int l = 0;
    int r = s.size() - 1;
    while (l < r) {
        std::swap(s[l++], s[r--]);
    }
}

/**
 ///////////// 345.

 */


/**
 ///////////// 346.

 */


/**
 ///////////// 347. Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 */
std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mm;
    for (int num : nums) {
        mm[num]++;
    }
    std::priority_queue<std::pair<int, int>> qq;
    for (auto& entry : mm) {
        qq.emplace(entry.second, entry.first);
    }
    std::vector<int> res;
    for (int i = 0; i < k && !qq.empty(); ++i) {
        res.emplace_back(qq.top().second);
        qq.pop();
    }
    return res;
}

FTEST(test_topKFrequent) {
    auto t = [](const std::vector<int>& nums, int k) {
        std::vector<int> nns = nums;
        auto re = topKFrequent(nns, k);
        LOG(INFO) << nums << " top " << k << " frequent: " << re;
        return re;
    };

    t({}, 0);
    t({}, 1);
    t({1}, 0);
    t({1}, 1);
    t({1, 2}, 2);
    t({1, 1, 2}, 1);
    t({1, 1, 2}, 2);
    t({1, 1, 1, 2, 2, 3}, 2);
}

/**
 ///////////// 348.

 */


/**
 ///////////// 349.

 */


/**
 ///////////// 350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.

Follow up:
 - What if the given array is already sorted? How would you optimize your algorithm?
 - What if nums1's size is small compared to nums2's size? Which algorithm is better?
 - What if elements of nums2 are stored on disk,
    and the memory is limited such that you cannot load all elements into the memory at once?
 */
std::vector<int> intersectTwoArray(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::unordered_map<int, int> mm;
    for (int num : nums1) {
        ++mm[num];
    }
    std::vector<int> res;
    for (int num : nums2) {
        if (--mm[num] >= 0) {
            res.emplace_back(num);
        }
    }
    return res;
}


}