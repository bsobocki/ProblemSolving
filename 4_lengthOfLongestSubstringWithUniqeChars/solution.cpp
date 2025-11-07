#include <iostream>
#include <unordered_map>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int start = 0;
    int maxSize = 0;
    std::unordered_map<char, int> seen;

    for (int i = 0; i < s.size(); i++) {
        auto chr = s[i];
        // check if the letter have been seen
        // and if the last occurrence
        // is the part of the substring we are checking
        if (seen.count(chr) and seen[chr] >= start) {
            if (maxSize < i - start) 
                maxSize = i - start;
            // move start to exclude seen letter
            start = seen[chr] + 1;
        }
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

    std::cout << getResultInfoHeader() << endl;
    for (auto& test : tests) {
        int result = lengthOfLongestSubstring(test.s);
        cout << getTestResultInfo(test.s, test.expectedResult, result) << endl;
    }
}
