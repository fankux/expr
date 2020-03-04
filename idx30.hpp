#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex30 {

/**
 ///////////// 301. Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input string valid.
 Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).

Example 1:
Input: "()())()"
Output: ["()()()", "(())()"]

Example 2:
Input: "(a)())()"
Output: ["(a)()()", "(a())()"]

Example 3:
Input: ")("
Output: [""]

THOUGHTS(pair reverse method):
    - First, try to search pair '(' match ')', remove ')' that number execees '(', like ()),
      this round is recursive to remove patterns like: ())).
      here we have done number of ')' more than number of '('
    - Then reverse search pair as ')' match '(', and reverse search string also.
      Do same action as step 1, we could remove all '(' that number of '(' more than number of ')'
 */
std::vector<std::string> removeInvalidParentheses(std::string s) {
    std::vector<std::string> res;
    auto dfs_check_method = [&] {
        auto check = [](const std::string& s) {
            int cnt = 0;
            for (char c : s) {
                if (c == '(') {
                    ++cnt;
                } else if (c == ')' && (--cnt) < 0) {
                    return false;
                }
            }
            return cnt == 0;
        };
        std::function<void(std::string, int, int, int)> rfunc;
        rfunc = [&](std::string s, int start, int count1, int count2) {
            if (count1 == 0 && count2 == 0 && check(s)) {
                res.emplace_back(std::move(s));
                return;
            }

            for (size_t i = start; i < s.size(); ++i) {
                if (i > start && s[i] == s[i - 1]) {
                    continue;
                }
                if (count1 > 0 && s[i] == '(') {
                    rfunc(s.substr(0, i) + s.substr(i + 1), i, count1 - 1, count2);
                } else if (count2 > 0 && s[i] == ')') {
                    rfunc(s.substr(0, i) + s.substr(i + 1), i, count1, count2 - 1);
                }
            }
        };
        int count1 = 0;
        int count2 = 0;
        for (char c : s) {
            count1 += c == '(';
            if (count1 == 0) {
                count2 += c == ')';
            } else {    // count1 > 0
                count1 -= c == ')';
            }
        }
        rfunc(s, 0, count1, count2);
    };
    auto pair_reverse_method = [&] {
        std::function<void(std::string, size_t, size_t, const std::pair<char, char>&)> rfunc;
        rfunc = [&](std::string s, size_t li, size_t lj, const std::pair<char, char>& pair) {
            int count = 0;
            for (size_t i = li; i < s.size(); ++i) {
                if (s[i] == pair.first) {
                    ++count;
                } else if (s[i] == pair.second) {
                    --count;
                }
                if (count >= 0) {
                    continue;
                }
                for (size_t j = lj; j <= i; ++j) {
                    if (s[j] == pair.second && (j == lj || s[j] != s[j - 1])) {
                        rfunc(s.substr(0, j) + s.substr(j + 1), i, j, pair);
                    }
                }
                return;
            }
            s = std::string(s.rbegin(), s.rend());
            if (pair.first == '(') {
                rfunc(s, 0, 0, {')', '('});
            } else { // now pair is )(, we have done a round
                res.emplace_back(s);
            }
        };
        rfunc(s, 0, 0, {'(', ')'});
    };
    pair_reverse_method();
    return res;
}

FTEST(test_removeInvalidParentheses) {
    auto t = [](const std::string& s) {
        auto re = removeInvalidParentheses(s);
        LOG(INFO) << s << " remove invalid parentheses: " << re;
    };

    t("");
    t("a");
    t("a(");
    t("a)");
    t("a)(");
    t("a)((");
    t("a)(((");
    t("a))(");
    t("a)))(");
    t("a()");
    t("a(()");
    t("a((()");
    t("a())");
    t("a()))");
    t("a()(");
    t("a()((");
    t("a()(((");
    t(")a()");
    t("))a()");
    t(")))a()");
    t("()())()");
    t("(a)())()");
}

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
int maxProfitCooldown(std::vector<int>& prices) {
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

FTEST(test_maxProfitCooldown) {
    auto t = [&](const std::vector<int>& prices) {
        std::vector<int> nns = prices;
        auto re = maxProfitCooldown(nns);
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