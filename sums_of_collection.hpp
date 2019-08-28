#include <vector>
#include <map>
#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<size_t>> two_sum(const std::vector<int>& nums, int sum) {
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
    LOG(INFO) << nums << " find: " << sum << " result: " << two_sum(nums, sum);
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

std::vector<std::vector<size_t>> three_sum(std::vector<int>& nums, int sum) {
    if (nums.size() < 2) {
        return {};
    }

    std::sort(nums.begin(), nums.end());

    std::vector<std::vector<size_t>> res;


    return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
