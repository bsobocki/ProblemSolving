#include <iostream>
#include <to_string.hpp>
#include <map>
#include <vector>

using namespace std;

std::string longestPalindrome(string str) {
    auto size = str.size();
    if (size < 2) return str;
    int maxLen = 0;
    int maxBeg = 0;
    int mid = size/2;

    auto getPalindromeSize = [&str](int beg, int end) {
        while(beg >= 0 && end < str.size() && str[beg] == str[end]) {
            beg--;
            end++;
        }
        return end-beg-1;
    };

    for (int i = 0; i <= size/2; i++) {
        auto ind = mid+i;
        auto maxLocalPalindromeLen = std::max(getPalindromeSize(ind, ind),
                                              getPalindromeSize(ind, ind+1));

        if (maxLocalPalindromeLen > maxLen) {
            maxLen = maxLocalPalindromeLen;
            maxBeg = ind - (maxLen-1)/2;
        }

        ind = mid-i;
        maxLocalPalindromeLen = std::max(getPalindromeSize(ind, ind),
                                         getPalindromeSize(ind, ind+1));
        
        if (maxLocalPalindromeLen > maxLen) {
            maxLen = maxLocalPalindromeLen;
            maxBeg = ind - (maxLen-1)/2;
        }
    }

    return str.substr(maxBeg, maxLen);
}

std::map<std::string, std::vector<std::string>> tests = {
    {"kbaaabr", {"baaab"}},
    {"babad", {"bab", "aba"}},
    {"cbffbd", {"bffb"}},
    {"babca", {"bab"}},
    {"aacabdkacaa", {"aca"}},
    {"bb", {"bb"}},
    {"aaaa", {"aaaa"}},
    {"", {""}},
    {"habcdeedcbagj", {"abcdeedcba"}}
};

void runSolution() {
    for (auto& test : tests) {
        std::cout << "[str: \"" << test.first << "\"] : [answer:\"" << longestPalindrome(test.first) << "\"] : [valid results: " << to_string(test.second) << "]" << std::endl;
    }
}

