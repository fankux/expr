#pragma once

#include <vector>
#include <map>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<size_t>> two_sum_all_idx(const std::vector<int>& nums, int sum) {
    if (nums.size() < 2) {
        return {};
    }
    std::unordered_map<int, std::vector<size_t>> cc;
    for (size_t i = 0; i < nums.size(); ++i) {
        cc[nums[i]].emplace_back(i);
    }

    std::vector<bool> visit(nums.size(), false);

    std::vector<std::vector<size_t>> res;
    for (size_t i = 0; i < nums.size(); ++i) {
        auto entry = cc.find(sum - nums[i]);
        if (entry != cc.end()) {
            for (auto idx : entry->second) {
                if (idx == i || (visit[i] && visit[idx])) {
                    continue;
                }
                visit[idx] = true;
                if (i < idx) {
                    res.emplace_back(std::vector<size_t>{i, idx});
                } else {
                    res.emplace_back(std::vector<size_t>{idx, i});
                }
            }
            visit[i] = true;
        }
    }

    return res;
}

static void test_two_sum_item(const std::vector<int>& nums, int sum) {
    LOG(INFO) << nums << " find: " << sum << " result: " << two_sum_all_idx(nums, sum);
}

FTEST(test_two_sum) {
    test_two_sum_item({1, 2, 4}, 3);
    test_two_sum_item({-1, 2, 4}, 3);
    test_two_sum_item({1, 1, 2, 4}, 3);
    test_two_sum_item({1, 1, 2, 4}, 3);
    test_two_sum_item({1, 1, 2, 2, 4}, 3);
    test_two_sum_item({-1, 1, 1, 2, 2, 4}, 3);
    test_two_sum_item({1, 2, 4}, 0);
    test_two_sum_item({1, 2, 4}, 1);
    test_two_sum_item({1, 2, 4}, 2);
    test_two_sum_item({1, 2, 4}, 4);
    test_two_sum_item({1, 2, 4}, 5);
    test_two_sum_item({1, 2, 4}, 6);
}

std::vector<std::vector<int>> three_sum(std::vector<int>& nums, int sum) {
    if (nums.size() < 2) {
        return {};
    }

    std::sort(nums.begin(), nums.end());
    if (sum == 0 && (nums.front() > 0 || nums.back() < 0)) {
        return {};
    }

    std::vector<std::vector<int>> res;
    for (size_t k = 0; k < nums.size() - 2; ++k) {
        if (sum == 0 && nums[k] > sum) {
            break;
        }
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        int target = sum - nums[k];
        size_t i = k + 1;
        size_t j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.emplace_back(std::vector<int>{nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i + 1]) {
                    ++i;
                }
                while (i < j && nums[j] == nums[j - 1]) {
                    ++j;
                }
                ++i;
                --j;
            } else if (nums[i] + nums[j] < target) {
                ++i;
            } else {
                --j;
            }
        }
    }

    return res;
}

static void test_three_sum_item(const std::vector<int>& nums, int sum) {
    std::vector<int> nums_in = nums;
    LOG(INFO) << nums_in << " find: " << sum << " result: " << three_sum(nums_in, sum);
}

FTEST(test_three_sum) {
    test_three_sum_item({1, 0, 2}, 0);
    test_three_sum_item({-1, -3, -5}, 0);
    test_three_sum_item({-1, 0, 1}, 0);
    test_three_sum_item({-1, -1, 0, 1, 0, 1}, 0);
    test_three_sum_item({-1, 0, -1, 0, 1, 1}, 0);
    test_three_sum_item({-1, -1, 0, 0, 1, 1}, 0);
    test_three_sum_item({-1, 0, 1, -1, 0, 1}, 0);
    test_three_sum_item({-3, 1, 2, -1, 0, 1}, 0);
    test_three_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, 0);

    test_three_sum_item({1, 0, 2}, 3);
    test_three_sum_item({-1, -3, -5}, -9);
    test_three_sum_item({-1, 0, 1}, 0);
    test_three_sum_item({-1, -1, 0, 1, 0, 1}, 2);
    test_three_sum_item({-1, 0, -1, 0, 1, 1}, -2);
    test_three_sum_item({-1, -1, 0, 0, 1, 1}, 1);
    test_three_sum_item({-1, 0, 1, -1, 0, 1}, -1);
    test_three_sum_item({-3, 1, 2, -1, 0, 1}, 3);
    test_three_sum_item({-3, 1, 2, -1, 0, 1}, 4);
    test_three_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    test_three_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
}

std::vector<std::vector<int>> three_sum_closest(std::vector<int>& nums, int sum) {
    if (nums.size() < 2) {
        return {};
    }

    std::sort(nums.begin(), nums.end());

    uint32_t min_abs = UINT_MAX;
    std::vector<std::vector<int>> res;
    for (size_t k = 0; k < nums.size() - 2; ++k) {
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        int target = sum - nums[k];
        size_t i = k + 1;
        size_t j = nums.size() - 1;
        while (i < j) {
            int sum_in = nums[i] + nums[j];
            uint32_t abs = ::abs(target - sum_in);
            if (abs <= min_abs) {
                if (abs < min_abs) {
                    res.clear();
                }
                min_abs = abs;
                res.emplace_back(std::vector<int>{nums[k], nums[i], nums[j]});
            }

            if (abs == 0) {
                while (i < j && nums[i] == nums[i + 1]) {
                    ++i;
                }
                while (i < j && nums[j] == nums[j - 1]) {
                    ++j;
                }
                ++i;
                --j;
            } else if (sum_in < target) {
                ++i;
            } else {
                --j;
            }
        }
    }

    return res;
}

static void test_three_sum_closest_item(const std::vector<int>& nums, int sum) {
    std::vector<int> nums_in = nums;
    LOG(INFO) << nums_in << " find: " << sum << " closest result: "
            << three_sum_closest(nums_in, sum);
}

FTEST(test_three_sum_closest) {
    test_three_sum_closest_item({1, 0, 2}, 0);
    test_three_sum_closest_item({-1, -3, -5}, 0);
    test_three_sum_closest_item({-1, 0, 1}, 0);
    test_three_sum_closest_item({-1, -1, 0, 1, 0, 1}, 0);
    test_three_sum_closest_item({-1, 0, -1, 0, 1, 1}, 0);
    test_three_sum_closest_item({-1, -1, 0, 0, 1, 1}, 0);
    test_three_sum_closest_item({-1, 0, 1, -1, 0, 1}, 0);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1}, 0);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, 0);

    test_three_sum_closest_item({1, 0, 2}, 3);
    test_three_sum_closest_item({-1, -3, -5}, -9);
    test_three_sum_closest_item({-1, 0, 1}, 0);
    test_three_sum_closest_item({-1, -1, 0, 1, 0, 1}, 3);
    test_three_sum_closest_item({-1, 0, -1, 0, 1, 1}, -2);
    test_three_sum_closest_item({-1, -1, 0, 0, 1, 1}, 1);
    test_three_sum_closest_item({-1, 0, 1, -1, 0, 1}, -1);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1}, 3);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1}, 4);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
