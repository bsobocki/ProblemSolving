#include <iostream>
#include <utils/utils.hpp>
#include <map>
#include <vector>

using namespace std;

bool isPalindrome(string str, int i=0, int j=-1) {
    if (j==-1) j += str.size();
    for(; i < j; i++, j--) {
        if (str[i] != str[j]) return false;
    }
    return true;
}

// most intuitive (and slowest) recursive
std::string longestPalindromeRecursive(string str) {
    if (str.size() < 2) return str;

    if (isPalindrome(str)) return str;

    string left = longestPalindromeRecursive(str.substr(0,str.size()-1));
    string right = longestPalindromeRecursive(str.substr(1,str.size()-1));

    if (left.size() > right.size()) return left;

    return right;
}

// slightly better because of memorizing calculated states
std::string longestPalindromeRec(string& str, int i, int j, vector<vector<string>>& mem) {
    if (mem[i][j] != "") return mem[i][j];
    
    if (i >= j){
        mem[i][j] = str.substr(i, j-i+1);
    }
    else {
        if (isPalindrome(str,i,j)) {
            mem[i][j] = str.substr(i,j-i+1);
        }
        else {
            string right = longestPalindromeRec(str, i+1, j, mem);
            string left = longestPalindromeRec(str, i, j-1, mem);
            
            if (left.size() > right.size()) {
                mem[i][j] = left;
            }
            else {
                mem[i][j] = right;
            }
        }
    }

    return mem[i][j];
}

// memorized recursion - optimization
// but memorizing string - O(n^3)
string longestPalindromeRecursiveBetter(string str) {
    if (str.empty()) return str;

    std::vector<std::vector<string>> mem(str.size(), std::vector<string>(str.size(), ""));
    return longestPalindromeRec(str,0,str.size()-1, mem);
}

// helper function for debugging Dynamic Programming Algorithm
void writeDP(const vector<vector<bool>>& vec) {
    cout << endl << std::string(4*(vec[0].size()+2)+1, '-') << std::endl;
    cout << "| # | ";
    for (int i = 0; i < vec[0].size(); i++) cout << i%10 << " | ";
    cout << endl << std::string(4*(vec[0].size()+2)+1, '-') << std::endl;

    int idx = 0;
    auto row = vec.begin();
    for (; row != vec.end(); row++) {
        cout << "| " << (idx++)%10 << " | ";
        for (auto val : *row) cout << (val ? "✓" : "✗") << " | ";
        cout << endl;
    }
    cout << endl << std::string(4*(vec[0].size()+2)+1, '-') << std::endl;
}

// Dynamic Programming solution
// time complexity - O(n^2)
// space complexity O(n^2)
std::string longestPalindromeDP(string str) {
    if (str.size() < 2) return str;

    // creating and copying strings are too long - we will use bool to just see if str[i..j] is a palindrome
    std::vector<std::vector<bool>> dp(str.size(), std::vector<bool>(str.size(), false));

    // all one-character and empty substrings are palindromes
    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = true;
        }
    }

    for (int i = str.size()-1; i >= 0; i--) {
        // we need to start from i+1 because we filled dp[i][i]
        // and empty substrings where j < i
        for (int j = i+1; j < str.size(); j++) {
            // str[i..j] is a palindrome when its edge chars are the same and it has a palindrome between them
            dp[i][j] = str[i] == str[j] && dp[i+1][j-1];
        }
    }

    // we want to search from longest strings to shortest
    // so we will search diagonally starting from (i=0 j=size-1)
    // the next diagonal search will be (i=0 j=size-2) (i=1 j=size-1)
    // next (i=0 j=size-3) (i=1 j=size-2) (i=2 j=size-1)
    for (int jStart = str.size()-1; jStart >= 0; jStart--) {
        for (int i = 0; i < str.size() - jStart; i++) {
            int j = jStart + i;
            if (dp[i][j]) {
                return str.substr(i, j-i+1);
            }
        }
    }
    return "";
}

// "Expand Around Center" approach
// O(n²) - time complexity
// O(1)  - space complexity
std::string longestPalindrome(string str) {
    auto size = str.size();
    if (size < 2) return str;
    int maxLen = 0;
    int maxBeg = 0;

    auto getPalindromeSize = [&str](int beg, int end) {
        // expand until the characters at both ends are equal
        while(beg >= 0 && end < str.size() && str[beg] == str[end]) {
            beg--;
            end++;
        }
        // returns length end-beg-1 instead of end-beg+1 because do one iteration too much - after check
        // so we will decrease beg and increase end so our length increases by 2, so end-beg+1-2 = end-beg-1
        return end-beg-1;
    };

    // we will try to expand palindromes as much as we can starting in the middle
    // and checking if character on the left is equal to the right one in getPalindromeSize
    for (int i = 0; i < size; i++) {
        auto maxLocalPalindromeLen = std::max(getPalindromeSize(i, i), // for odd size palindromes
                                              getPalindromeSize(i, i+1)); // for evem size palindromes

        if (maxLocalPalindromeLen > maxLen) {
            maxLen = maxLocalPalindromeLen; // save biggest palindrome length
            maxBeg = i - (maxLen-1)/2; // save the beggining of this palindrome
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

    runTests(tests, [](const Test& test) {
        string result = longestPalindrome(test.str);
        string resultDP = longestPalindromeDP(test.str);
        string resultRecursive = longestPalindromeRecursive(test.str);
        string resultRecBetter = longestPalindromeRecursiveBetter(test.str);

        cout << endl;
        cout << getTestResultInfo(test.getInfo() + " [OPT]", test.validResults, result) << endl;
        cout << getTestResultInfo(test.getInfo() + " [DP]", test.validResults, resultDP) << endl;
        cout << getTestResultInfo(test.getInfo() + " [REC]", test.validResults, resultRecursive) << endl;
        cout << getTestResultInfo(test.getInfo() + " [MEM REC]", test.validResults, resultRecBetter) << endl;
        cout << endl;

        auto passed = [&](string& res) {
            return std::find(test.validResults.begin(), test.validResults.end(), res) != test.validResults.end();
        };

        return passed(result) && passed(resultDP) & passed(resultRecursive) && passed(resultRecBetter);
    });
}


