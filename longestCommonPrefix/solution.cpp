#include <iostream>
#include <vector>
#include <to_string.hpp>

using namespace std;

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


void runSolution() {
    std::vector<std::string> test1 = {"reflower","flow","flight"};
    auto res = longestCommonPrefix(test1);
    std::cout << "longest common prefix for : " << to_string(test1) << " is " << res << std::endl;
    /*todo*/
}