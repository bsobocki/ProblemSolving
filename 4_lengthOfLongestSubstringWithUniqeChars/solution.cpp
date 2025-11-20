#include <iostream>
#include <unordered_map>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

// O(n) - time complexity
// O(n) - space complexity
// we are going through the string starting from 0
// we are putting unseen characters into the map [key: char, value: char index]
// if we get to the seen character then we exclude it from our substring
// to do that we just move start - representing the beggining of the substring
// to the position of this letter that we saw before
// example:
// s u b s t r i n g - start at 0, but found 's' on i=3
// ^
// we move start to seen[chr] + 1, so now start = 1
// u b s t r i n g - our longest unique substring
int lengthOfLongestSubstring(string s) {
    int start = 0;
    int maxSize = 0;
    std::unordered_map<char, int> seen;

    for (int i = 0; i < s.size(); i++) {
        auto chr = s[i];
        // check if the letter have been seen
        // and if the last occurrence is the part of the substring we are checking
        // because we don't want to check character we saw before current substring
        if (seen.count(chr) and seen[chr] >= start) {
            if (maxSize < i - start) 
                maxSize = i - start;
            // move start to exclude seen letter
            start = seen[chr] + 1;
        }
        // add/update character status
        seen[chr] = i;
    }

    // after we reached the end of the string we need to check
    // whether the last checked substring is the longest one
    if (maxSize < s.size() - start)
        maxSize = s.size() - start;

    return maxSize;
}

struct Test {
    string s;
    int expectedResult;
};

void runSolution() {
    const vector<Test> tests = {
        {"abcabcbb", 3},  // "abc"
        {"bbbbb", 1},     // "b"
        {"pwwkew", 3},    // "wke"
        {"", 0},          // ""
        {" ", 1},         // " "
        {"au", 2},        // "au"
        {"dvdf", 3},      // "vdf"
        {"abba", 2},      // "ab" or "ba"
        {"tmmzuxt", 5},   // "mzuxt"
    };

    runTests(tests, [](const Test& test) {
        int result = lengthOfLongestSubstring(test.s);
        cout << getTestResultInfo(test.s, test.expectedResult, result) << endl;
        return test.expectedResult == result;
    });
}
