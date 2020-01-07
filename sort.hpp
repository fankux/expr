//
// Created by fankux on 2020/1/7.
//

#pragma once

void qsort(std::vector<int>& nums, int start, int end) {
    if (nums.empty() || start >= end) {
        return;
    }

    auto partition = [](std::vector<int>& nums, int left, int right) {
        int pivot = nums[left];
        while (left < right) {
            while (left < right && pivot < nums[right]) {
                --right;
            }
            nums[left] = nums[right];
            while (left < right && nums[left] <= pivot) {
                ++left;
            }
            nums[right] = nums[left];
        }
        nums[left] = pivot;
        return left;
    };

    int m = partition(nums, start, end);
    qsort(nums, start, m - 1);
    qsort(nums, m + 1, end);
}

void merge_sort(std::vector<int>& nums) {
    std::vector<int> tmp(nums.size());
    std::function<void(int, int)> r_func;
    r_func = [&](int start, int end) {
        if (start >= end - 1) {
            return;
        }
        size_t mid = start + (end - start) / 2;
        r_func(start, mid);
        r_func(mid, end);

        size_t n = start;
        size_t i = start;
        size_t j = mid;
        while (i < mid && j < end) {
            tmp[n++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
        }
        while (i < mid) {
            tmp[n++] = nums[i++];
        }
        while (j < end) {
            tmp[n++] = nums[j++];
        }
        for (; start < end; ++start) {
            nums[start] = tmp[start];
        }
    };
    r_func(0, nums.size());
}

void sort(std::vector<int>& nums) {
//    qsort(nums, 0, nums.size() - 1);
    merge_sort(nums);
}

FTEST(test_sort) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        sort(nns);
        LOG(INFO) << nums << " sort: " << nns;
    };

    t({});
    t({1});
    t({1, 2});
    t({1, 2, 3});
    t({1, 2, 3, 4});
    t({1, 1});
    t({1, 1, 2});
    t({1, 2, 2});
    t({2, 1, 2});
    t({2, 1});
    t({2, 2, 1});
    t({2, 1, 1});
    t({1, 2, 1});
    t({3, 2, 1});
    t({4, 2, 1});
    t({-1, -1, 0});
    t({0, -1, -1});
    t({1, 0, -1});
    t({-1, 0, 1});
    t({6, 2, 8, 1, 5, 7});
    t({-6, -2, -8, -1, -5, -7});
}