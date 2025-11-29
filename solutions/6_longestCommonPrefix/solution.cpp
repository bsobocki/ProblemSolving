#include <iostream>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

// O(S) - time complexity
// O(1) - space complexity
// where S = sum of all characters in all strings
string longestCommonPrefix(const vector<string>& strs) {
    if (strs.empty()) return "";
    // for (auto& str : strs)
    //     if (str.empty()) return "";
    
    int shortest = 0;
    for (int i = 0; i < strs.size(); i++)
        if (strs[i].size() < strs[shortest].size())
            shortest = i;

    int shortestLen = strs[shortest].size();
    bool run = true;

    // for each letter in the shortest string
    for (int i = 0; i < shortestLen; i++) {
        // check if others also have it at the same place (prefix)
        for (auto& str : strs) {
            if (str[i] != strs[shortest][i]) {
                // if we have a mismatch then just return prefix from 0 to i-1
                return strs[shortest].substr(0,i);
            }
        }
    }
    
    // if we went through the whole vector
    // then just return the shortest string
    return strs[shortest];
}

struct Test {
    vector<string> strs;
    string expectedResult;
};

void runSolution() {
    vector<Test> tests = {
        {{"flower","flow","flight"}, "fl"},
        {{"dog","racecar","car"}, ""},
        {{"interspecies","interstellar","interstate"}, "inters"},
        {{"prefix","prefixes","preform"}, "pref"},
        {{"", "b"}, ""},
        {{"a"}, "a"},
        {{"ab", "a"}, "a"},
        {{"abc", "abc", "abc"}, "abc"},
        {{"aa", "ab"}, "a"},
        {{"reflower","flow","flight"}, ""},
        {{"cir","car"}, "c"}
    };

    runTests(tests, [](const Test& test) {
        string result = longestCommonPrefix(test.strs);
        cout << getTestResultInfo(to_string(test.strs), test.expectedResult, result) << endl;
        return test.expectedResult == result;
    });
}
