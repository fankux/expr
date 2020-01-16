#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex73 {

/**
 ///////////// 731.

 */

/**
 ///////////// 732.

 */


/**
 ///////////// 733.

 */


/**
 ///////////// 734.

 */


/**
 ///////////// 735.

 */


/**
 ///////////// 736.

 */


/**
 ///////////// 737. 
 */


/**
 ///////////// 738.

 */


/**
 ///////////// 739. Daily Temperatures
Given a list of daily temperatures T, return a list such that, for each day in the input,
 tells you how many days you would have to wait until a warmer temperature.
 If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73],
 your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000].
 Each temperature will be an integer in the range [30, 100].
 */
std::vector<int> dailyTemperatures(std::vector<int>& T) {
    size_t len = T.size();
    std::vector<int> res(len, 0);
    std::stack<std::pair<int, int>> st;
    for (int i = len - 1; i >= 0; --i) {
        while (!st.empty() && T[i] >= st.top().first) {
            st.pop();
        }
        res[i] = st.empty() ? 0 : st.top().second - i;
        st.emplace(T[i], i);
    }
    return res;
}

FTEST(test_dailyTemperatures) {
    auto t = [](const std::vector<int>& nums) {
        std::vector<int> nns = nums;
        auto re = dailyTemperatures(nns);
        LOG(INFO) << nums << " daily temperatures: " << re;
        return re;
    };

    t({});
    t({1});
    t({1, 0});
    t({1, 1});
    t({1, 2});
    t({1, 1, 1});
    t({1, 1, 2});
    t({1, 2, 1});
    t({2, 1, 1});
    t({1, 2, 2});
    t({2, 1, 2});
    t({2, 2, 1});
    t({2, 2, 2});
    t({1, 2, 3});
    t({73, 74, 75, 71, 69, 72, 76, 73});
}

/**
 ///////////// 740.

 */



}