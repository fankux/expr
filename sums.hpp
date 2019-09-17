#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t average(const std::vector<int>& nums, uint32_t& remain) {
    uint32_t average = 0;
    uint64_t fsum = 0;
    for (int num : nums) {
        size_t n = nums.size();
        average += num / n;
        fsum += num % n;
        if (fsum >= n) {
            ++average;
            fsum -= n;
        }
    }
    remain = fsum;
    return average;
}

static void test_average_item(const std::vector<int>& nums) {
    uint32_t remain = 0;
    LOG(INFO) << nums << " average: " << average(nums, remain) << " remain " << remain;
}

FTEST(test_average) {
    test_average_item({0, 0, 0});
    test_average_item({0, 0, 1});
    test_average_item({0, 0, 2});
    test_average_item({0, 0, 3});
    test_average_item({0, 1, 0});
    test_average_item({0, 1, 1});
    test_average_item({0, 1, 2});
    test_average_item({0, 1, 3});
    test_average_item({0, 2, 0});
    test_average_item({0, 2, 1});
    test_average_item({0, 2, 2});
    test_average_item({0, 2, 3});
    test_average_item({0, 3, 0});
    test_average_item({0, 3, 1});
    test_average_item({0, 3, 2});
    test_average_item({0, 3, 3});

    test_average_item({1, 0, 0});
    test_average_item({1, 0, 1});
    test_average_item({1, 0, 2});
    test_average_item({1, 0, 3});
    test_average_item({1, 1, 0});
    test_average_item({1, 1, 1});
    test_average_item({1, 1, 2});
    test_average_item({1, 1, 3});
    test_average_item({1, 2, 0});
    test_average_item({1, 2, 1});
    test_average_item({1, 2, 2});
    test_average_item({1, 2, 3});
    test_average_item({1, 3, 0});
    test_average_item({1, 3, 1});
    test_average_item({1, 3, 2});
    test_average_item({1, 3, 3});

    test_average_item({2, 0, 0});
    test_average_item({2, 0, 1});
    test_average_item({2, 0, 2});
    test_average_item({2, 0, 3});
    test_average_item({2, 1, 0});
    test_average_item({2, 1, 1});
    test_average_item({2, 1, 2});
    test_average_item({2, 1, 3});
    test_average_item({2, 2, 0});
    test_average_item({2, 2, 1});
    test_average_item({2, 2, 2});
    test_average_item({2, 2, 3});
    test_average_item({2, 3, 0});
    test_average_item({2, 3, 1});
    test_average_item({2, 3, 2});
    test_average_item({2, 3, 3});

    test_average_item({3, 0, 0});
    test_average_item({3, 0, 1});
    test_average_item({3, 0, 2});
    test_average_item({3, 0, 3});
    test_average_item({3, 1, 0});
    test_average_item({3, 1, 1});
    test_average_item({3, 1, 2});
    test_average_item({3, 1, 3});
    test_average_item({3, 2, 0});
    test_average_item({3, 2, 1});
    test_average_item({3, 2, 2});
    test_average_item({3, 2, 3});
    test_average_item({3, 3, 0});
    test_average_item({3, 3, 1});
    test_average_item({3, 3, 2});
    test_average_item({3, 3, 3});

    test_average_item({INT_MAX, INT_MAX, INT_MAX - 1});
    test_average_item({INT_MAX, INT_MAX, INT_MAX});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<size_t>> two_sum_all_idx(const std::vector<int>& nums, int target) {
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
        auto entry = cc.find(target - nums[i]);
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

static void test_two_sum_item(const std::vector<int>& nums, int target) {
    LOG(INFO) << nums << " find: " << target << " result: " << two_sum_all_idx(nums, target);
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

std::vector<std::vector<int>> three_sum(std::vector<int>& nums, int target) {
    if (nums.size() < 2) {
        return {};
    }

    std::sort(nums.begin(), nums.end());
    if (target == 0 && (nums.front() > 0 || nums.back() < 0)) {
        return {};
    }

    std::vector<std::vector<int>> res;
    for (size_t k = 0; k < nums.size() - 2; ++k) {
        if (target == 0 && nums[k] > target) {
            break;
        }
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        int target_in = target - nums[k];
        size_t i = k + 1;
        size_t j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target_in) {
                res.emplace_back(std::vector<int>{nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i + 1]) {
                    ++i;
                }
                while (i < j && nums[j] == nums[j - 1]) {
                    --j;
                }
                ++i;
                --j;
            } else if (nums[i] + nums[j] < target_in) {
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

std::vector<std::vector<int>> three_sum_closest(std::vector<int>& nums, int target) {
    if (nums.size() < 3) {
        return {};
    }

    std::sort(nums.begin(), nums.end());

    uint32_t min_abs = UINT_MAX;
    std::vector<std::vector<int>> res;
    for (size_t k = 0; k < nums.size() - 2; ++k) {
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        int target_in = target - nums[k];
        size_t i = k + 1;
        size_t j = nums.size() - 1;
        while (i < j) {
            bool dedup_flag = false;
            int sum_in = nums[i] + nums[j];
            uint32_t abs = ::abs(target_in - sum_in);
            if (abs <= min_abs) {
                if (abs < min_abs) {
                    res.clear();
                }
                min_abs = abs;
                res.emplace_back(std::vector<int>{nums[k], nums[i], nums[j]});
                dedup_flag = true;
            }

            if (sum_in < target_in) {
                while (dedup_flag && i < j && nums[i] == nums[i + 1]) {
                    ++i;
                }
                ++i;
            } else {
                while (dedup_flag && i < j && nums[j] == nums[j - 1]) {
                    --j;
                }
                --j;
            }
        }
    }

    return res;
}

static void test_three_sum_closest_item(const std::vector<int>& nums, int target) {
    std::vector<int> nums_in = nums;
    LOG(INFO) << nums_in << " find: " << target << " closest result: "
            << three_sum_closest(nums_in, target);
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
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, -1);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, 1);
    test_three_sum_closest_item({-3, 1, 2, -1, 0, 1, 0, 0}, 2);

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

std::vector<std::vector<int>> three_sum_max_smaller(std::vector<int>& nums, int target) {
    if (nums.size() < 3) {
        return {};
    }

    std::sort(nums.begin(), nums.end());

    uint32_t abs_min = UINT_MAX;
    std::vector<std::vector<int>> res;
    for (size_t k = 0; k < nums.size() - 2; ++k) {
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        int target_in = target - nums[k];
        size_t i = k + 1;
        size_t j = nums.size() - 1;
        while (i < j) {
            bool dedup_flag = false;
            int sum_in = nums[i] + nums[j];
            uint32_t abs = ::abs(target_in - sum_in);
            if (sum_in < target_in && abs <= abs_min) {
                if (abs < abs_min) {
                    res.clear();
                }
                abs_min = abs;
                res.emplace_back(std::vector<int>{nums[k], nums[i], nums[j]});

                dedup_flag = true;
            }

            if (sum_in < target_in) {
                while (dedup_flag && i < j && nums[i] == nums[i + 1]) {
                    ++i;
                }
                ++i;
            } else {
                while (dedup_flag && i < j && nums[j] == nums[j - 1]) {
                    --j;
                }
                --j;
            }
        }
    }

    return res;
}

static void test_three_sum_max_smaller_item(const std::vector<int>& nums, int target) {
    std::vector<int> nums_in = nums;
    LOG(INFO) << nums_in << " find: " << target << " smaller result: "
            << three_sum_max_smaller(nums_in, target);
}

FTEST(test_three_sum_max_smaller) {
    test_three_sum_max_smaller_item({1, 0, 2}, 0);
    test_three_sum_max_smaller_item({-1, -3, -5}, 0);
    test_three_sum_max_smaller_item({-1, 0, 1}, 0);
    test_three_sum_max_smaller_item({-1, -1, 0, 1, 0, 1}, 0);
    test_three_sum_max_smaller_item({-1, 0, -1, 0, 1, 1}, 0);
    test_three_sum_max_smaller_item({-1, -1, 0, 0, 1, 1}, 0);
    test_three_sum_max_smaller_item({-1, 0, 1, -1, 0, 1}, 0);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1}, 0);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, 0);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, -1);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, 1);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, 2);

    test_three_sum_max_smaller_item({1, 0, 2}, 3);
    test_three_sum_max_smaller_item({-1, -3, -5}, -9);
    test_three_sum_max_smaller_item({-1, 0, 1}, 0);
    test_three_sum_max_smaller_item({-1, -1, 0, 1, 0, 1}, 3);
    test_three_sum_max_smaller_item({-1, 0, -1, 0, 1, 1}, -2);
    test_three_sum_max_smaller_item({-1, -1, 0, 0, 1, 1}, 1);
    test_three_sum_max_smaller_item({-1, 0, 1, -1, 0, 1}, -1);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1}, 3);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1}, 4);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    test_three_sum_max_smaller_item({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
}

std::vector<std::vector<int>> four_sum(std::vector<int>& nums, int target) {
    if (nums.size() < 4) {
        return {};
    }

    std::sort(nums.begin(), nums.end());

    std::vector<std::vector<int>> res;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }

            int target_in = target - nums[i];
            size_t l = j + 1;
            size_t h = nums.size() - 1;
            while (l < h) {
                int sum = nums[j] + nums[l] + nums[h];
                if (sum == target_in) {
                    res.emplace_back(std::vector<int>{nums[i], nums[j], nums[l], nums[h]});
                    while (l < h && nums[l] == nums[l + 1]) {
                        ++l;
                    }
                    while (l < h && nums[h] == nums[h - 1]) {
                        --h;
                    }
                    ++l;
                    --h;
                } else if (sum < target) {
                    ++l;
                } else {
                    --h;
                }
            }
        }
    }

    return res;
}

static void test_four_sum_item(const std::vector<int>& nums, int target) {
    std::vector<int> nums_in = nums;
    LOG(INFO) << nums_in << " find: " << target << " sum result: " << four_sum(nums_in, target);
}

FTEST(test_four_sum) {
    test_four_sum_item({1, 0, 2, -3}, 0);
    test_four_sum_item({-1, -3, -5, 0}, 0);
    test_four_sum_item({-1, 0, 1, 0}, 0);
    test_four_sum_item({-1, -1, 0, 1, 0, 1}, 0);
    test_four_sum_item({-1, 0, -1, 0, 1, 1}, 0);
    test_four_sum_item({-1, -1, 0, 0, 1, 1}, 0);
    test_four_sum_item({-1, 0, 1, -1, 0, 1}, 0);
    test_four_sum_item({-3, 1, 2, -1, 0, 1}, 0);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, 0);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, -1);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, 1);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, 2);

    test_four_sum_item({1, 0, 2}, 3);
    test_four_sum_item({-1, -3, -5}, -9);
    test_four_sum_item({-1, 0, 1}, 0);
    test_four_sum_item({-1, -1, 0, 1, 0, 1}, 3);
    test_four_sum_item({-1, 0, -1, 0, 1, 1}, -2);
    test_four_sum_item({-1, -1, 0, 0, 1, 1}, 1);
    test_four_sum_item({-1, 0, 1, -1, 0, 1}, -1);
    test_four_sum_item({-3, 1, 2, -1, 0, 1}, 3);
    test_four_sum_item({-3, 1, 2, -1, 0, 1}, 4);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, -3);
    test_four_sum_item({-3, 1, 2, -1, 0, 1, 0, 0}, -4);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

double median_of_two(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    std::function<int(size_t, size_t, size_t)> kth;
    kth = [&kth, &nums1, &nums2](size_t i, size_t j, size_t k) {
        if (i >= nums1.size()) {
            return nums2[j + k - 1];
        }
        if (j >= nums2.size()) {
            return nums1[i + k - 1];
        }
        if (k == 1) {
            return std::min(nums1[i], nums2[j]);
        }

        // if exist the K th number
        int mv1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int mv2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
        if (mv1 < mv2) {
            return kth(i + k / 2, j, k - k / 2);
        } else {
            return kth(i, j + k / 2, k - k / 2);
        }
    };

    size_t i = nums1.size();
    size_t j = nums2.size();
    size_t left = (i + j + 1) / 2;
    size_t right = (i + j + 2) / 2;
    return (kth(0, 0, left) + kth(0, 0, right)) / 2.0;
}

double median_of_two_iteration(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int i = nums1.size();
    int j = nums2.size();
    if (i > j) {
        return median_of_two_iteration(nums2, nums1);
    }
    size_t l = 0;
    size_t h = 2 * i;
    size_t c1;
    size_t c2;
    int l1 = 0;
    int l2 = 0;
    int r1 = 0;
    int r2 = 0;
    while (l <= h) {
        c1 = (l + h) / 2;
        c2 = i + j - c1;
        l1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
        r1 = (c1 == 2 * i) ? INT_MAX : nums1[c1 / 2];
        l2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
        r2 = (c2 == 2 * j) ? INT_MAX : nums2[c2 / 2];

        if (l1 > r2) {
            h = c1 - 1;
        } else if (l2 > r1) {
            l = c1 + 1;
        } else {
            break;
        }
    }
    return (std::max(l1, l2) + std::min(r1, r2)) / 2.0;
}

FTEST(test_median_of_two) {
    LOG(INFO) << "recursive: ";
    LOG(INFO) << median_of_two({0}, {0});
    LOG(INFO) << median_of_two({1}, {1});
    LOG(INFO) << median_of_two({0}, {1});
    LOG(INFO) << median_of_two({1, 3}, {2});
    LOG(INFO) << median_of_two({1, 2}, {3, 4});
    LOG(INFO) << median_of_two({1, 2}, {2, 4});
    LOG(INFO) << median_of_two({4, 4}, {4, 4});

    LOG(INFO);
    LOG(INFO) << "iteration: ";
    LOG(INFO) << median_of_two_iteration({0}, {0});
    LOG(INFO) << median_of_two_iteration({1}, {1});
    LOG(INFO) << median_of_two_iteration({0}, {1});
    LOG(INFO) << median_of_two_iteration({1, 3}, {2});
    LOG(INFO) << median_of_two_iteration({1, 2}, {3, 4});
    LOG(INFO) << median_of_two_iteration({1, 2}, {2, 4});
    LOG(INFO) << median_of_two_iteration({4, 4}, {4, 4});
}
