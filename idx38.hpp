#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex38 {

/**
 ///////////// 381.

 */

/**
 ///////////// 382.

 */


/**
 ///////////// 383.

 */


/**
 ///////////// 384. Shuffle an Array
Shuffle a set of numbers without duplicates.

Example:
// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);
// Shuffle the array [1,2,3] and return its result.
 Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();
// Resets the array back to its original configuration [1,2,3].
solution.reset();
// Returns the random shuffling of array [1,2,3].
solution.shuffle();

 **
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
class ShuffleArray {
public:
    ShuffleArray(std::vector<int>& nums) {
        _nums = nums;
    }

    /** Resets the array to its original configuration and return it. */
    std::vector<int> reset() {
        return _nums;
    }

    /** Returns a random shuffling of the array. */
    std::vector<int> shuffle() {
        std::vector<int> res;
        auto index_slot_method = [&] {
            std::vector<int> indics;
            for (size_t i = 0; i < _nums.size(); ++i) {
                indics.emplace_back(i);
            }

            res.reserve(_nums.size());
            for (size_t i = 0; i < _nums.size(); ++i) {
                int pos = rand() % indics.size();
                int v = indics[pos];
                indics[pos] = indics.back();
                indics.pop_back();
                res[i] = _nums[v];
            }
        };
        auto knuth_method = [&] {
            res = _nums;
            for (size_t i = 0; i < res.size(); ++i) {
                int t = i + rand() % (res.size() - i);
                std::swap(res[i], res[t]);
            }
        };
        knuth_method();
        return res;
    }

private:
    std::vector<int> _nums;
};

FTEST(test_ShuffleArray) {
    std::vector<int> nums{1, 2, 3, 4, 5};
    ShuffleArray shuffler(nums);
    LOG(INFO) << nums << " shuffle: " << shuffler.shuffle();
    LOG(INFO) << nums << " shuffle: " << shuffler.shuffle();
    LOG(INFO) << nums << " shuffle: " << shuffler.shuffle();
    LOG(INFO) << nums << " shuffle: " << shuffler.shuffle();
    LOG(INFO) << nums << " reset: " << shuffler.reset();
}

/**
 ///////////// 385.

 */


/**
 ///////////// 386.

 */


/**
 ///////////// 387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index.
 If it doesn't exist, return -1.

Examples:
s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
 */
int firstUniqChar(std::string s) {
    int mm[26] = {0};
    for (char c : s) {
        ++mm[c - 'a'];
    }
    for (size_t i = 0; i < s.size(); ++i) {
        if (mm[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}

FTEST(test_firstUniqChar) {
    auto t = [&](const std::string& s) {
        auto re = firstUniqChar(s);
        LOG(INFO) << s << " first unique char: " << re;
        return re;
    };

    FEXP(t(""), -1);
    FEXP(t("a"), 0);
    FEXP(t("aa"), -1);
    FEXP(t("aab"), 2);
    FEXP(t("leetcode"), 0);
    FEXP(t("loveleetcode"), 2);
}

/**
 ///////////// 388.

 */


/**
 ///////////// 389.

 */


/**
 ///////////// 390.

 */



}