#pragma once

#include "util.hpp"

size_t lower_bound(const std::vector<int>& nums, int target) {
    size_t l = 0;
    size_t h = nums.size();
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}

size_t upper_bound(const std::vector<int>& nums, int target) {
    int l = 0;
    int h = nums.size();
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}

ssize_t bin_search(const std::vector<int>& nums, int target) {
    ssize_t re = lower_bound(nums, target);
    return re == nums.size() || nums[re] != target ? -1 : re;
}

ssize_t bin_search_1st_great_equal(const std::vector<int>& nums, int target) {
    ssize_t re = lower_bound(nums, target);
    return re == nums.size() ? -1 : re;
}

ssize_t bin_search_1st_great(const std::vector<int>& nums, int target) {
    ssize_t re = upper_bound(nums, target);
    return re == nums.size() ? -1 : re;
}

FTEST(test_bin_search) {
    auto binary_search_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search(nums, target);
        LOG(INFO) << nums << " find " << target << ": " << re;
        return re;
    };
    binary_search_t({}, 1);
    binary_search_t({1}, 0);
    binary_search_t({1}, 2);
    binary_search_t({1}, 1);
    binary_search_t({1, 2}, 0);
    binary_search_t({1, 2}, 3);
    binary_search_t({1, 2}, 1);
    binary_search_t({1, 2}, 2);
    binary_search_t({1, 2, 3}, 0);
    binary_search_t({1, 2, 3}, 1);
    binary_search_t({1, 2, 3}, 2);
    binary_search_t({1, 2, 3}, 3);
    binary_search_t({1, 2, 3}, 4);
    binary_search_t({1, 2, 3, 4}, 1);
    binary_search_t({1, 2, 3, 4}, 2);
    binary_search_t({1, 2, 3, 4}, 3);
    binary_search_t({1, 2, 3, 4}, 4);
    binary_search_t({1, 2, 3, 4, 5}, 1);
    binary_search_t({1, 2, 3, 4, 5}, 2);
    binary_search_t({1, 2, 3, 4, 5}, 3);
    binary_search_t({1, 2, 3, 4, 5}, 4);
    binary_search_t({1, 2, 3, 4, 5}, 5);
    binary_search_t({1, 2, 2, 4, 5}, 2);
    binary_search_t({1, 2, 3, 3, 5}, 3);

    auto bound_t = [](const std::vector<int>& nums, int target) {
        auto re = lower_bound(nums, target);
        LOG(INFO) << nums << " lower x>=" << target << "(closed): " << re;
        re = upper_bound(nums, target);
        LOG(INFO) << nums << " upper x<=" << target << "(unclosed): " << re;
        return re;
    };
    bound_t({1}, 1);
    bound_t({1, 1}, 1);
    bound_t({1, 1, 1}, 1);
    bound_t({1, 1, 1, 1}, 1);
    bound_t({1, 1, 1, 1, 1}, 1);
    bound_t({1}, 0);
    bound_t({1}, 2);
    bound_t({1, 1, 1, 1, 1}, 0);
    bound_t({1, 1, 1, 1, 1}, 2);
    bound_t({1, 2, 2, 2, 3}, 2);
    bound_t({1, 2, 3, 5}, 4);

    auto first_ge_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search_1st_great_equal(nums, target);
        LOG(INFO) << nums << " 1st x>=" << target << ": " << re;
        return re;
    };
    first_ge_t({}, 1);
    first_ge_t({1}, 0);
    first_ge_t({1}, 2);
    first_ge_t({1}, 1);
    first_ge_t({1, 2}, 0);
    first_ge_t({1, 2}, 3);
    first_ge_t({1, 2}, 1);
    first_ge_t({1, 2}, 2);
    first_ge_t({1, 2, 3}, 0);
    first_ge_t({1, 2, 3}, 1);
    first_ge_t({1, 2, 3}, 2);
    first_ge_t({1, 2, 3}, 3);
    first_ge_t({1, 2, 3}, 4);
    first_ge_t({1, 2, 3, 4}, 1);
    first_ge_t({1, 2, 3, 4}, 2);
    first_ge_t({1, 2, 3, 4}, 3);
    first_ge_t({1, 2, 3, 4}, 4);
    first_ge_t({1, 2, 3, 4, 5}, 1);
    first_ge_t({1, 2, 3, 4, 5}, 2);
    first_ge_t({1, 2, 3, 4, 5}, 3);
    first_ge_t({1, 2, 3, 4, 5}, 4);
    first_ge_t({1, 2, 3, 4, 5}, 5);
    first_ge_t({1, 2, 2, 4, 5}, 2);
    first_ge_t({1, 2, 3, 3, 5}, 3);

    auto first_g_t = [](const std::vector<int>& nums, int target) {
        auto re = bin_search_1st_great(nums, target);
        LOG(INFO) << nums << " 1st x>" << target << ": " << re;
        return re;
    };
    first_g_t({}, 1);
    first_g_t({1}, 0);
    first_g_t({1}, 2);
    first_g_t({1}, 1);
    first_g_t({1, 2}, 0);
    first_g_t({1, 2}, 3);
    first_g_t({1, 2}, 1);
    first_g_t({1, 2}, 2);
    first_g_t({1, 2, 3}, 0);
    first_g_t({1, 2, 3}, 1);
    first_g_t({1, 2, 3}, 2);
    first_g_t({1, 2, 3}, 3);
    first_g_t({1, 2, 3}, 4);
    first_g_t({1, 2, 3, 4}, 1);
    first_g_t({1, 2, 3, 4}, 2);
    first_g_t({1, 2, 3, 4}, 3);
    first_g_t({1, 2, 3, 4}, 4);
    first_g_t({1, 2, 3, 4, 5}, 1);
    first_g_t({1, 2, 3, 4, 5}, 2);
    first_g_t({1, 2, 3, 4, 5}, 3);
    first_g_t({1, 2, 3, 4, 5}, 4);
    first_g_t({1, 2, 3, 4, 5}, 5);
    first_g_t({1, 2, 2, 4, 5}, 2);
    first_g_t({1, 2, 3, 3, 5}, 3);
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

FTEST(test_reverse_stack) {
    std::vector<int> s{1, 2, 3, 4, 5};
    std::vector<int> s2 = s;
    reverse_stack(s2);
    LOG(INFO) << s << " reverse: " << s2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**

 THOUGHTS:
    dp[i][j] means the max result of i items and weight j.

                   / dp[i-1][j]                         not pick item[i]
    dp[i][j] = max
                   \ dp[i-1][j-weights[i]]+prices[i]    pick item[i], weight decrese weight[i]
 */
int knapsack01(const std::vector<int>& prices, const std::vector<int>& weights, int total) {
    size_t len = prices.size();
    std::vector<std::vector<int>> dp(len + 1, std::vector<int>(total + 1, 0));

    for (size_t i = 0; i <= len; ++i) {
        for (int w = 0; w <= total; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (w >= weights[i - 1]) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + prices[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return len == 0 || total == 0 ? 0 : dp.back().back();
}

FTEST(test_knapsack01) {
    auto t = [](const std::vector<int>& prices, const std::vector<int>& weights, int total) {
        auto re = knapsack01(prices, weights, total);
        LOG(INFO) << prices << ", " << weights << " max " << total << ": " << re;
        return re;
    };

    FEXP(t({}, {}, 0), 0);
    FEXP(t({2}, {2}, 0), 0);
    FEXP(t({2}, {2}, 1), 0);
    FEXP(t({2}, {2}, 2), 2);
    FEXP(t({1, 4, 5, 7}, {1, 3, 4, 5}, 7), 9);
}

// TODO... all(limit) knapsack
