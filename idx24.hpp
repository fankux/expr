#pragma once

#include "list.hpp"
#include "subs.hpp"
#include "strs.hpp"
#include "graph.hpp"

namespace LCIndex24 {

/**
 ///////////// 241.

 */

/**
 ///////////// 242. Valid Anagram
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
 */
bool isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) {
        return false;
    }
    int cc[26] = {0};
    for (auto c : s) {
        ++cc[c - 'a'];
    }
    for (auto c : t) {
        if (--cc[c - 'a'] < 0) {
            return false;
        }
    }
    return true;
}


/**
 ///////////// 243.

 */


/**
 ///////////// 244.

 */


/**
 ///////////// 245.

 */


/**
 ///////////// 246.

 */


/**
 ///////////// 247.

 */


/**
 ///////////// 248.

 */


/**
 ///////////// 249.

 */


/**
 ///////////// 250.

 */



}