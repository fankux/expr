#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex30 {

/**
 ///////////// 301.

 */

/**
 ///////////// 302.

 */


/**
 ///////////// 303.

 */


/**
 ///////////// 304.

 */


/**
 ///////////// 305.

 */


/**
 ///////////// 306.

 */


/**
 ///////////// 307.

 */


/**
 ///////////// 308.

 */


/**
 ///////////// 309. Best Time to Buy and Sell Stock with Cooldown
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like
 (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time
 (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:
Input: [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]

THOUGHTS:
 buy[0~i]: last operate is buy before or at i
 rest[0~i]: last operate is cooldown before or at i
 sell[0~i]: last operate is sell before or at i

 sell[i] = max(sell[i-1],   buy[i-1] + price)
            today not sell  someday buy, today sell

 rest[i] = max(rest[i-1],    sell[i-1],     buy[i-1] ?)
            today not rest   sell at i-1    buy before i-1 ?

 buy[i] =  max(buy[i-1],    rest[i-1] - price,       )
            today not buy   sell at day before yestoday,

     case rest[i] = sell[i-1], then:
 buy[i] =  max(buy[i-1],  sell[i-2] - price)
 sell[i] = max(sell[i-1], buy[i-1] + price)
 */
int maxProfit(std::vector<int>& prices) {
//    size_t len = prices.size();
//    std::vector<int> buy(len + 1, 0);
//    std::vector<int> sell(len + 1, 0);
    int buy = INT_MIN;
    int pre_buy = 0;
    int sell = 0;
    int pre_sell = 0;
    for (int price : prices) {
//        if (i == 1) {
//            buy[0] = INT_MIN;
//            buy[i] = 0 - prices[0];
//            continue;
//        }
//        buy[i] = std::max(buy[i - 1], sell[i - 2] - prices[i - 1]);
//        sell[i] = std::max(sell[i - 1], buy[i - 1] + prices[i - 1]);

        pre_buy = buy;
        buy = std::max(pre_buy, pre_sell - price);
        pre_sell = sell;
        sell = std::max(pre_sell, pre_buy + price);
    }
    return sell;
}

FTEST(test_maxProfit) {
    auto t = [&](const std::vector<int>& prices) {
        std::vector<int> nns = prices;
        auto re = maxProfit(nns);
        LOG(INFO) << prices << " max profit whit cooldown: " << re;
        return re;
    };

    FEXP(t({}), 0);
    FEXP(t({0}), 0);
    FEXP(t({1}), 0);
    FEXP(t({0, 0}), 0);
    FEXP(t({0, 1}), 1);
    FEXP(t({0, 1, 1}), 1);
    FEXP(t({0, 1, 2}), 2);
    FEXP(t({1, 2, 3, 0, 2}), 3);
}

/**
 ///////////// 310.

 */



}