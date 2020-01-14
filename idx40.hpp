#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex40 {

/**
 ///////////// 401.

 */

/**
 ///////////// 402.

 */


/**
 ///////////// 403.

 */


/**
 ///////////// 404.

 */


/**
 ///////////// 405.

 */


/**
 ///////////// 406. Queue Reconstruction by Height
Suppose you have a random list of people standing in a queue.
 Each person is described by a pair of integers (h, k),
 where h is the height of the person and k is the number of people in front of this person
 who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
 */
std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
    std::sort(people.begin(), people.end(), [](std::vector<int>& a, std::vector<int>& b) {
        return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
    });

    size_t len = people.size();
    for (size_t i = 1; i < len; ++i) {
        int n = people[i][0];
        int count = people[i][1];
        int j = i;
        for (; j > count; --j) {
            people[j][0] = people[j - 1][0];
            people[j][1] = people[j - 1][1];
        }
        people[j][0] = n;
        people[j][1] = count;
    }
    return people;
}

/**
 ///////////// 407.

 */


/**
 ///////////// 408.

 */


/**
 ///////////// 409.

 */


/**
 ///////////// 410.

 */



}