#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex32 {

/**
 ///////////// 321.

 */

/**
 ///////////// 322. Coin Change
You are given coins of different denominations and a total amount of money amount.
 Write a function to compute the fewest number of coins that you need to make up that amount.
 If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1

Note:
You may assume that you have an infinite number of each kind of coin.
 */
int coinChange(std::vector<int>& coins, int amount) {
    auto recursive_method = [&] {
        std::unordered_map<int, int> mm;
        std::function<int(int)> r_func;
        r_func = [&](int n) {
            if (n <= 0) {
                return n == 0 ? 0 : -1;
            }
            auto entry = mm.find(n);
            if (entry != mm.end()) {
                return entry->second;
            }
            int found = false;
            int res = INT_MAX;
            for (int coin : coins) {
                int re = r_func(n - coin);
                if (re != -1) {
                    found = true;
                    res = std::min(res, re + 1);
                }
            }
            mm.emplace(n, found ? res : -1);
            return found ? res : -1;
        };
        return r_func(amount);
    };
    auto dp_method = [&] {
        std::vector<int> state(amount + 1, amount + 1);
        state[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (coin <= i) {
                    state[i] = std::min(state[i], 1 + state[i - coin]);
                }
            }
        }
        return state.empty() ? 0 : (state.back() == amount + 1 ? -1 : state.back());
    };
    auto sorted_find = [&] {
        if (amount == 0) {
            return 0;
        }
        int res = INT_MAX;
        std::sort(coins.begin(), coins.end());
        std::function<void(int, int, int)> r_func;
        r_func = [&](int start, int target, int cur) {
            if (start < 0) {
                return;
            }
            int quotient = target / coins[start];
            if (target % coins[start] == 0) {
                res = std::min(res, cur + quotient);
                return;
            }
            for (int i = quotient; i >= 0; --i) {
                if (cur + i >= res - 1) {   // TODO.. do not understand
                    break;
                }
                r_func(start - 1, target - i * coins[start], cur + i);
            }
        };
        r_func(coins.size() - 1, amount, 0);
        return res == INT_MAX ? -1 : res;
    };
    return sorted_find();
}

FTEST(test_coinChange) {
    auto t = [](const std::vector<int>& nums, int n) {
        std::vector<int> nns = nums;
        auto re = coinChange(nns, n);
        LOG(INFO) << nums << " coin change " << n << ": " << re;
        return re;
    };

    FEXP(t({}, 0), 0);
    FEXP(t({}, 1), -1);
    FEXP(t({2}, 3), -1);
    FEXP(t({1}, 1), 1);
    FEXP(t({1}, 2), 2);
    FEXP(t({1}, 3), 3);
    FEXP(t({2}, 2), 1);
    FEXP(t({1, 2}, 2), 1);
    FEXP(t({1, 2}, 3), 2);
    FEXP(t({1, 2, 5}, 11), 3);
    FEXP(t({1, 2, 5}, 100), 20);
}

/**
 ///////////// 323.

 */


/**
 ///////////// 324. Wiggle Sort II
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:
Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].

Example 2:
Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].

Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

 THOUGHTS:
    Sort first, split to two half at the middle, get a number from back to begin
        (only this way can ensure the foward number is greater than previous) of each half.
 */
void wiggleSort(std::vector<int>& nums) {
    std::vector<int> nn = nums;
    std::sort(nn.begin(), nn.end());
    int i = nn.size() - 1;
    int j = (nn.size() - 1) / 2;
    for (size_t k = 0; k < nn.size(); ++k) {
        nums[k] = (k & 1) ? nn[i--] : nn[j--];
    }
}

FTEST(test_wiggleSort) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        wiggleSort(nns);
        LOG(INFO) << nums << " wiggle sort: " << nns;
    };

    t({});
    t({1});
    t({1, 2});
    t({2, 1});
    t({2, 1});
    t({2, 1, 3});
    t({2, 1, 3, 4});
    t({2, 1, 5, 3, 4});
}

/**
 ///////////// 325.

 */


/**
 ///////////// 326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Example 1:
Input: 27
Output: true

Example 2:
Input: 0
Output: false

Example 3:
Input: 9
Output: true

Example 4:
Input: 45
Output: false

 Follow up:
Could you do it without using any loop / recursion?
 */
bool isPowerOfThree(int n) {
    return (n > 0 && 1162261467 % n == 0);
}

/**
 ///////////// 327.

 */


/**
 ///////////// 328. Odd Even Linked List
Given a singly linked list, group all odd nodes together followed by the even nodes.
 Please note here we are talking about the node number and not the value in the nodes.
You should try to do it in place.
 The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL

Example 2:
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...
 */
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    ListNode* p = head;
    ListNode* pre = head->next;
    while (pre && pre->next) {
        ListNode* q = pre->next;
        pre->next = q->next;
        q->next = p->next;
        p->next = q;

        p = p->next;
        pre = pre->next;
    }
    return head;
}

FTEST(test_oddEvenList) {
    auto t = [](const std::vector<int>& nums) {
        ListNode* list = list_convert_leetcode(create_list(nums));
        list = oddEvenList(list);
        LOG(INFO) << nums << " odd event list: " << print_list(list);
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({1, 2, 3, 4, 5});
    t({2, 1, 3, 5, 6, 4, 7});
}

/**
 ///////////// 329. Longest Increasing Path in a Matrix
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down.
 You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:
Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:
Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
 */
int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        return 0;
    }
    size_t row = matrix.size();
    size_t col = matrix.front().size();
    // max path length starting at point(x,y)
    std::vector<std::vector<int>> state(row, std::vector<int>(col, 0));
    std::vector<std::pair<int, int>> ds = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    std::function<int(int, int)> r_func;
    r_func = [&](int x, int y) {
        if (state[x][y] != 0) {
            return state[x][y];
        }
        int mx = 1;
        for (auto& d : ds) {
            int nx = x + d.first;
            int ny = y + d.second;
            if (nx < 0 || ny < 0 || nx >= row || ny >= col || matrix[nx][ny] <= matrix[x][y]) {
                continue;
            }
            mx = std::max(mx, 1 + r_func(nx, ny));
        }
        state[x][y] = mx;
        return mx;
    };
    int res = 0;
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            res = std::max(res, r_func(i, j));
        }
    }
    return res;
}

FTEST(test_longestIncreasingPath) {
    auto t = [](const std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> nns = matrix;
        auto re = longestIncreasingPath(nns);
        LOG(INFO) << matrix << " matrix incresing: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({{}}), 0);
    FEXP(t({{1}}), 1);
    FEXP(t({{1, 2}}), 2);
    FEXP(t({{1}, {2}}), 2);
    FEXP(t({{1, 2, 1}}), 2);
    FEXP(t({{1, 2, 3}}), 3);
    FEXP(t({{1}, {2}, {1}}), 2);
    FEXP(t({{1}, {2}, {3}}), 3);
    FEXP(t({{9, 9, 4}, {6, 6, 8}, {2, 1, 1}}), 4);
    FEXP(t({{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}), 4);
    FEXP(t({{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
            {20, 21, 22, 23, 24, 25, 26, 27, 28, 29}, {39, 38, 37, 36, 35, 34, 33, 32, 31, 30},
            {40, 41, 42, 43, 44, 45, 46, 47, 48, 49}, {59, 58, 57, 56, 55, 54, 53, 52, 51, 50},
            {60, 61, 62, 63, 64, 65, 66, 67, 68, 69}, {79, 78, 77, 76, 75, 74, 73, 72, 71, 70},
            {80, 81, 82, 83, 84, 85, 86, 87, 88, 89}, {99, 98, 97, 96, 95, 94, 93, 92, 91, 90},
            {100, 101, 102, 103, 104, 105, 106, 107, 108, 109},
            {119, 118, 117, 116, 115, 114, 113, 112, 111, 110},
            {120, 121, 122, 123, 124, 125, 126, 127, 128, 129},
            {139, 138, 137, 136, 135, 134, 133, 132, 131, 130},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}), 140);
}

/**
 ///////////// 330.

 */



}