#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex29 {

/**
 ///////////// 291.

 */

/**
 ///////////// 292.

 */


/**
 ///////////// 293.

 */


/**
 ///////////// 294.

 */


/**
 ///////////// 295. Find Median from Data Stream
Median is the middle value in an ordered integer list.
 If the size of the list is even, there is no middle value.
 So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3
[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:
 - void addNum(int num) - Add a integer number from the data stream to the data structure.
 - double findMedian() - Return the median of all elements so far.

Example:
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

Follow up:
If all integer numbers from the stream are between 0 and 100, how would you optimize it?
If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?

 **
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() = default;

    void addNum(int num) {
        if (_left.empty()) {
            _left.emplace(num);
            return;
        }
        if (num <= _left.top()) {
            _left.emplace(num);
        } else {
            _right.emplace(num);
        }
        if (_left.size() > _right.size() + 1) {
            _right.emplace(_left.top());
            _left.pop();
        } else if (_left.size() < _right.size()) {
            _left.emplace(_right.top());
            _right.pop();
        }
    }

    double findMedian() {
        if (_left.size() == _right.size()) {
            return _left.empty() ? 0 : (_left.top() + _right.top()) / 2.0;
        }
        return _left.top();
    }

    void clear() {
        std::priority_queue<int>().swap(_left);
        std::priority_queue<int, std::vector<int>, std::greater<int>>().swap(_right);
    }

private:
    std::priority_queue<int> _left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> _right;
};

FTEST(test_MedianFinder) {
    MedianFinder median;
    median.addNum(1);
    FEXP(median.findMedian(), 1);
    median.addNum(2);
    FEXP(median.findMedian(), 1.5);
    median.addNum(3);
    FEXP(median.findMedian(), 2);
}

/**
 ///////////// 296.

 */


/**
 ///////////// 297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so
 that it can be stored in a file or memory buffer, or transmitted across a network connection link
 to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree.
 There is no restriction on how your serialization/deserialization algorithm should work.
 You just need to ensure that a binary tree can be serialized to a string
 and this string can be deserialized to the original tree structure.

Example:
You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree.
 You do not necessarily need to follow this format,
 so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states.
 Your serialize and deserialize algorithms should be stateless.

 * Your Codec object will be instantiated and called as such:
 * Codec codec;
 * codec.deserialize(codec.serialize(root));
 */
class TreeCodec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string code;
        std::deque<TreeNode*> qq{root};
        bool flag = true;
        while (flag && !qq.empty()) {
            flag = false;
            char section[4] = {0};
            for (size_t i = qq.size(); i > 0; --i) {
                TreeNode* n = qq.front();
                qq.pop_front();

                char validf[1];
                validf[0] = n != nullptr ? 1 : 0;
                code.append(validf, 1);
                if (n != nullptr) {
                    memcpy(section, &(n->val), 4);
                    code.append(section, 4);
                    qq.emplace_back(n->left);
                    qq.emplace_back(n->right);
                    flag = flag || n->left != nullptr || n->right != nullptr;
                }
            }
        }
        return code;
    }

    std::string deserialize_tostring(const std::string& code) {
        std::string res;
        size_t len = code.size();
        int pos = 0;
        while (pos < len) {
            if (pos + 1 > len) {
                return "error valid flag";
            }
            char validf;
            memcpy(&validf, code.c_str() + (pos++), 1);
            if (validf) {
                if (pos + 4 > len) {
                    return "error value";
                }
                int v = 0;
                memcpy(&v, code.c_str() + pos, 4);
                pos += 4;
                res += std::to_string(v) + " ";
            } else {
                res += "null ";
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        if (data.empty() || data.front() == 0) {
            return nullptr;
        }
        int pos = 1;
        TreeNode* root = new TreeNode(0);
        memcpy(&root->val, data.c_str() + pos, 4);
        pos += 4;

        TreeNode* p = nullptr;
        std::deque<TreeNode*> qq{root};
        while (pos < data.size()) {
            p = qq.front();
            qq.pop_front();

            char validf;
            memcpy(&validf, data.c_str() + (pos++), 1);
            if (validf != 0) {
                p->left = new TreeNode(0);
                memcpy(&p->left->val, data.c_str() + pos, 4);
                pos += 4;
                qq.emplace_back(p->left);
            }

            memcpy(&validf, data.c_str() + (pos++), 1);
            if (validf != 0) {
                p->right = new TreeNode(0);
                memcpy(&p->right->val, data.c_str() + pos, 4);
                pos += 4;
                qq.emplace_back(p->right);
            }
        }
        return root;
    }
};

FTEST(test_TreeCodec) {
    TreeCodec codec;
    auto t = [&codec](const std::vector<TreeNodeStub>& nums) {
        TreeNode* tree = create_tree(nums);
        std::string code = codec.serialize(tree);
        LOG(INFO) << "tree:\n" << print_tree(tree)
                  << "\n code: \n" << codec.deserialize_tostring(code);
        TreeNode* tree_recover = codec.deserialize(code);
        LOG(INFO) << "recover: \n" << print_tree(tree_recover);
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, nullptr, 2});
    t({1, 2, nullptr});
    t({1, nullptr, nullptr});
    t({1, nullptr, 2, nullptr, nullptr, 3});
    t({1, nullptr, 2, nullptr, nullptr, nullptr, 3});
    t({1, 2, 3, nullptr, nullptr, 4, 5});
    t({3, 2, 4, 1});
    t({3, 2, 4, 1, 5});
    t({1, 2, nullptr});
    t({1, 2, nullptr, 3});
    t({1, 2, nullptr, 3, nullptr, nullptr, nullptr, 4});
    t({1, 2, nullptr, 3, nullptr, nullptr, nullptr, 4,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 5});
}

/**
 ///////////// 298.

 */


/**
 ///////////// 299.

 */


/**
 ///////////// 300. Longest Increasing Subsequence
Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:
Input: [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Note:
There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?
 */
int lengthOfLIS(std::vector<int>& nums) {
    size_t len = nums.size();
    auto dp_method = [&] {
        std::vector<int> dp(len, 1);
        int res = 0;
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            res = std::max(res, dp[i]);
        }
        return res;
    };
    auto bin_search_method = [&] {
        std::vector<int> vv;
        for (size_t i = 0; i < len; ++i) {
            size_t l = 0;
            size_t r = vv.size();
            while (l < r) {
                size_t mid = l + (r - l) / 2;
                if (vv[mid] < nums[i]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            if (l == vv.size()) {
                vv.emplace_back(nums[i]);
            } else {
                vv[l] = nums[i];
            }
        }
        return vv.size();
    };
    return bin_search_method();
}

FTEST(test_lengthOfLIS) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = lengthOfLIS(nns);
        LOG(INFO) << nums << " max length of LIS: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({1}), 1);
    FEXP(t({2, 1}), 1);
    FEXP(t({2, 1, 1}), 1);
    FEXP(t({2, 1, 2}), 2);
    FEXP(t({2, 1, 5, 3}), 2);
    FEXP(t({2, 1, 10, 4, 5}), 3);
    FEXP(t({10, 9, 2, 5, 3, 7, 101, 18}), 4);
    FEXP(t({4, 10, 4, 3, 8, 9}), 3);
    FEXP(t({1, 3, 6, 7, 9, 4, 10, 5, 6}), 6);
}

}