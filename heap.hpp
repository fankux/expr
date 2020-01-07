//
// Created by fankux on 2020/1/7.
//

#pragma once

#include "util.hpp"

FTEST(test_heap) {
    int nums[] = {2, 5, 1, 7, 8, 4, 3, 6};
    int len = sizeof(nums) / sizeof(nums[0]);
    create_min_heap(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_add(nums, len, 9);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_delete(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}