#include <iostream>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

// O(S) - time complexity
// O(1) - space complexity
// where S = sum of all characters in all strings
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    for (auto& str : strs)
        if (str.empty()) return "";
    
    int shortest = 0;
    for (int i = 0; i < strs.size(); i++)
        if (strs[i].size() < strs[shortest].size())
            shortest = i;

    int ind = -1;
    int shortestLen = strs[shortest].size();
    bool run = true;

    while (run and ++ind < shortestLen) {
        for (auto& str : strs) {
            if (str[ind] != strs[shortest][ind]) {
                run = false;
                break;
            }
        }
    }
    
    return strs[shortest].substr(0,ind);
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

    std::cout << getResultInfoHeader() << std::endl;
    for (auto& test : tests) {
        auto strs = test.strs;
        string result = longestCommonPrefix(strs);
        cout << getTestResultInfo(to_string(test.strs), test.expectedResult, result) << endl;
    }
}
