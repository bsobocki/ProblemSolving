#include <iostream>
#include <utils/utils.hpp>
#include <map>
#include <vector>

using namespace std;

// O(n²) - time complexity
// O(1)  - space complexity
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

struct Test {
    string str;
    vector<string> validResults;
    
    string getInfo() const {
        return str;
    }
};

void runSolution() {
    const vector<Test> tests = {
        {"kbaaabr", {"baaab"}},
        {"babad", {"bab", "aba"}},
        {"cbffbd", {"bffb"}},
        {"babca", {"bab"}},
        {"aacabdkacaa", {"aca"}},
        {"bb", {"bb"}},
        {"aaaa", {"aaaa"}},
        {"", {""}},
        {"habcdeedcbagj", {"abcdeedcba"}},
        {"a", {"a"}},
        {"ac", {"a", "c"}},
        {"racecar", {"racecar"}},
        {"abcdef", {"a", "b", "c", "d", "e", "f"}},
        {"noon", {"noon"}},
        {"civic", {"civic"}},
        {"abacabad", {"abacaba"}},
        {"forgeeksskeegfor", {"geeksskeeg"}},
        {"abcddcba", {"abcddcba"}}
    };

    std::cout << getResultInfoHeader() << std::endl;
    for (auto& test : tests) {
        string result = longestPalindrome(test.str);
        cout << getTestResultInfo(test.getInfo(), test.validResults, result) << endl;
    }
}


