#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex41 {

/**
 ///////////// 411.

 */

/**
 ///////////// 412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.
But for multiples of three it should output “Fizz” instead of the number
 and for the multiples of five output “Buzz”.
 For numbers which are multiples of both three and five output “FizzBuzz”.

Example:
n = 15,
Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
 */
std::vector<std::string> fizzBuzz(int n) {
    std::vector<std::string> res;
    int three = 3;
    int five = 5;
    for (int i = 1; i <= n; ++i) {
        if (i == three && i == five) {
            res.emplace_back("FizzBuzz");
            three += 3;
            five += 5;
        } else if (i == three) {
            res.emplace_back("Fizz");
            three += 3;
        } else if (i == five) {
            res.emplace_back("Buzz");
            five += 5;
        } else {
            res.emplace_back(std::to_string(i));
        }
    }
    return res;
}

FTEST(test_fizzBuzz) {
    auto t = [&](int n) {
        auto re = fizzBuzz(n);
        LOG(INFO) << n << " Fizz Buzz: " << re;
        return re;
    };

    t(1);
    t(2);
    t(3);
    t(4);
    t(5);
    t(6);
    t(7);
    t(8);
    t(9);
    t(10);
    t(20);
}

/**
 ///////////// 413.

 */


/**
 ///////////// 414.

 */


/**
 ///////////// 415.

 */


/**
 ///////////// 416.

 */


/**
 ///////////// 417.

 */


/**
 ///////////// 418.

 */


/**
 ///////////// 419.

 */


/**
 ///////////// 420.

 */



}