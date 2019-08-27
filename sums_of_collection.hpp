#include <vector>
#include <map>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<size_t> two_sum(const std::vector<int>& nums, int sum) {
    if (nums.size() < 2) {
        return {};
    }
    std::map<int, size_t> cc;
    for (size_t i = 0; i < nums.size(); ++i) {
        cc.emplace(nums[i], i);
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        auto entry = cc.find(sum - nums[i]);
        if (entry != cc.end()) {
            return {entry->second, i};
        }
    }

    return {};
}

void test_two_sum() {
    std::vector<size_t> nums;
    std::cout << std::is_compound<std::vector<int>&>::value << std::endl;
    std::cout << std::is_compound<int>::value << std::endl;

    LOG() << two_sum({1, 2, 4}, 3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
