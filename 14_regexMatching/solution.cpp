#include <iostream>
#include <utils/utils.hpp>

using namespace std;

// easiest recurstion attempt
// Time complexity: O((n+m)*2^(n+m)), because we have two branches (recalculating everything) and makes substrings each time (for p and s)
// Space Complexity O((n+m)^2), because call stack depth is O(n+m) in worst case (each call takes one char from s and/or p, so in total we have n+m depth)
bool isMatchSlowerRecursion(string s, string p) {
    if (s.empty()) {
        // from description: "It is guaranteed for each appearance of the character '*', there will be a previous valid character to match."
        // so check if we have only star expressions <char>* in regex by checking is size is even and number of stars is size/2
        if (!p.empty() && p.size() % 2 == 0)
            return std::count(p.begin(), p.end(), '*') == p.size()/2;
        // if is empty then it matches but if not, then size is odd, so we have something more than only star expressions - doesn't match
        return p.empty();
    }

    // if p is empty and s is not then s doesn't match p
    if (p.empty()) return false;

    bool firstCharMatches = s[0] == p[0] || p[0] == '.';

    // so p[0] is a letter or '.' because it cannot be * (based on the description)
    if (p.size() == 1)
         return s.size() == 1 && firstCharMatches;

    if (p[1] == '*') {
        // if we have * and we matches char before we have 2 options:
        if (firstCharMatches)
            return isMatchSlowerRecursion(s.substr(1), p) ||  // we can take this match and move on to check if more chars matches this expression <char>*
                   isMatchSlowerRecursion(s, p.substr(2));    // or treat * as 0 occurences and move on with the same s and substring of p without <char>*
        
        // if we don't match the character before *, then we just skip this <char>* treating * as 0 occurences
        return isMatchSlowerRecursion(s, p.substr(2));
    }
    
    // if we don't have <char>* case then we just match current char and move to the next one in both strings
    return firstCharMatches && isMatchSlowerRecursion(s.substr(1), p.substr(1));
}

// Time Complexity: O(n*m) - we have at most (n+1)*(m+1) unique states (all combinations of i and j)
// each state is computed once due to memoization, and each computation does O(1) work (except base case which can be O(m))
// without memoization this would be exponential O(2^(n+m/2)) due to branching at '*' patterns
// Space Complexity: O(n*m) for memoization table + O(n+m) for recursion stack
bool isMatchMemo(const string& s, int i, const string& p, int j, std::vector<std::vector<int>>& mem) {
    if(mem[i][j] != -1) return mem[i][j];

    int sSize = s.size() - i;
    int pSize = p.size() - j;

    // if s is empty or we moved to the end of s - in both cases we are checking an empty string
    if (sSize <= 0) {
        // from description: "It is guaranteed for each appearance of the character '*', there will be a previous valid character to match."
        // so check if we have only star expressions <char>* in regex by checking is size is even and number of stars is size/2
        if (pSize > 0 && pSize % 2 == 0) {
            mem[i][j] = std::count(p.begin()+j, p.end(), '*') == pSize/2;
            return mem[i][j];
        }
        // if is empty then it matches but if not, then size is odd, so we have something more than only star expressions - doesn't match
        mem[i][j] = pSize <= 0;
        return mem[i][j];
    }
    // if p is empty and s is not, then s doesn't match p
    else if (pSize <= 0) {
        mem[i][j] = false;
        return mem[i][j];
    }

    bool firstCharMatches = s[i] == p[j] || p[j] == '.';

    // so p[0] is a letter or '.' because it cannot be * (based on the description)
    if (pSize == 1) {
        mem[i][j] = sSize == 1 && firstCharMatches;
        return mem[i][j];
    }

    if (p[j+1] == '*') {
        // if we have * and we matches char before we have 2 options:
        if (firstCharMatches) {
            mem[i][j] = isMatchMemo(s, i+1, p, j, mem) ||  // we can take this match and move on to check if more chars matches this expression <char>*
                        isMatchMemo(s, i, p, j+2, mem);    // or treat * as 0 occurences and move on with the same s and substring of p without <char>*
            return mem[i][j];
        }
                   
        // if we don't match the character before *, then we just skip this <char>* treating * as 0 occurences
        mem[i][j] = isMatchMemo(s, i, p, j+2, mem);
        return mem[i][j];
    }
    
    // if we don't have <char>* case then we just match current char and move to the next one in both strings
    mem[i][j] = firstCharMatches && isMatchMemo(s, i+1, p, j+1, mem);
    return mem[i][j];
}

// much faster solution !!
bool isMatchMemorizedRecursion(string s, string p) {
    // we will create a table for our cases s[0..i] matches p[0..j] - with empty strings checks
    // for the same checks we did in recursion solution
    // not initialized: -1, false: 0, true: 1
    std::vector<std::vector<int>> mem(s.size()+1, std::vector<int>(p.size()+1, -1));
    return isMatchMemo(s, 0, p, 0, mem);
}

// helper function for debugging Dynamic Programming Algorithm
void writeDP(string s, string p, const vector<vector<bool>>& vec) {
    cout << endl << std::string(4*(p.size()+2)+1, '-') << std::endl;
    cout << "| # |   | ";
    for (auto c : p) cout << c << " | ";
    cout << endl << std::string(4*(p.size()+2)+1, '-') << std::endl;

    auto row = vec.begin();
    cout << "|   | ";
    for (auto val : *row++) cout << (val ? "✓" : "✗") << " | ";
    cout << endl;

    auto ch = s.begin();
    for (; row != vec.end(); row++) {
        cout << "| " << *ch++ << " | ";
        for (auto val : *row) cout << (val ? "✓" : "✗") << " | ";
        cout << endl;
    }
    cout << std::string(4*(p.size()+2)+1, '-') << std::endl;
}

// we have the first attempt done as isMatchSlowerRecursion(string, string)
// but it is very very slow, so based on that we will try to build Dynamic Programming Solution
bool isMatch(string s, string p) {
    // we will create a table for our cases s[0..i] matches p[0..j] - with empty strings
    // the same checks we did in recursion solution, but here empty strings are at 0 indexes
    // index tells about string length (i tells about current s length and j about p)
    // we will start with false as each value
    std::vector<std::vector<bool>> dp(s.size()+1, std::vector<bool>(p.size()+1, false));

    // empty s matches empty p
    dp[0][0] = true;

    // at first we want to check empty s matches parts of p
    // it can do it only for p composed only from expressions <char>* (like e.g. a*.*b*)
    // index j = 0 represents a column for empty p, so we start from 2 (second character, so first that can be '*')
    for (int j = 2; j <= p.size(); j+=2) {
        if (p[j-1] == '*') {
            // if we have expression <char>* then it can be matched
            // only when empty s matches previous part of p (before "<char>*")
            dp[0][j] = dp[0][j-2];
        }
    }

    // cases where p is empty but s is not remains as false
    // because we can't match empty pattern with non-empty string


    // the column j = 1 remains false except dp[1][1] if s[0] == p[0] or p[0] == '.'
    if (!s.empty() && !p.empty()) {
        dp[1][1] = s[0] == p[0] || p[0] == '.';
    }

    // for each check we will add one more character from s or one more from p
    // so we will consider cases "what after adding this character? will it still match?"
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 2; j <= p.size(); j++) {
            // checking s[0..i-1] and p[0..j-1]
            auto currS = s[i-1];
            auto currP = p[j-1];
            auto prevP = p[j-2];

            if (currP == '*') {
                if (currS == prevP || prevP == '.') {
                    dp[i][j] =  dp[i][j-2] ||   // we can still treat it as 0 matches (the same as p[0..j-3] - without <char>*)
                                dp[i-1][j];     // we can treat is as one more match (the same as s[0..i-2] for p[0..j-1])
                }
                else {
                    // treat <char>* as 0 occurences so the result is the same as for p without <char>*
                    dp[i][j] =  dp[i][j-2];
                } 
            }
            // if we have a letter or '.'
            else {
                // if we match this one then the result is the same as without currS and currP
                if (currS == currP || currP == '.') {
                    dp[i][j] = dp[i-1][j-1];
                }
                // if we don't then the result of current check remains false
            }
        }
    }

    return dp[s.size()][p.size()];
}

struct Test {
    std::string s;
    std::string p;
    bool expectedResult;

    std::string getInfo() const {
        return "{ '" + s + "' <=> '" + p + "' }";
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Basic exact matching
        {"aa", "a", false},
        {"aa", "aa", true},
        {"abc", "abc", true},
        {"abc", "ab", false},
        
        // Simple * matching (zero occurrences)
        {"aa", "a*", true},
        {"ab", "a*b", true},
        {"b", "a*b", true},
        {"", "a*", true},
        {"", "a*b*", true},
        
        // Simple * matching (multiple occurrences)
        {"aaa", "a*", true},
        {"aaaa", "a*", true},
        {"aab", "a*b", true},
        
        // Dot (.) matching
        {"ab", ".", false},
        {"a", ".", true},
        {"ab", "..", true},
        {"ab", "...", false},
        {"abc", "a.c", true},
        {"abc", "a.b", false},
        
        // Dot with star (.*) matching
        {"ab", ".*", true},
        {"abc", ".*", true},
        {"", ".*", true},
        {"aab", "c*a*b", true},
        {"ab", ".*c", false},
        {"abcd", "a.*d", true},
        {"abcd", "a.*c.*d", true},
        
        // Complex patterns
        {"mississippi", "mis*is*p*.", false},
        {"mississippi", "mis*is*ip*.", true},
        {"aaa", "a*a", true},
        {"aaa", "ab*a*c*a", true},
        {"aab", "c*a*b", true},
        {"ab", ".*c", false},
        {"aaa", "aaaa", false},
        
        // Multiple stars
        {"aa", "a*a*", true},
        {"aaa", "a*a*a*", true},
        {"ab", "a*b*", true},
        {"", "c*c*", true},
        
        // Edge cases with patterns
        {"a", "ab*", true},
        {"a", "ab*a", false},
        {"aa", "a*a", true},
        {"bbbba", ".*a*a", true},
        {"a", ".*..a*", false},
        
        // Single character tests
        {"", ".", false},
        {"a", "a", true},
        {"b", "a", false},
        
        // Complex real-world patterns
        {"abcdefg", "a.*g", true},
        {"abcdefg", "a.*f", false},
        {"aabcbcbcac", ".*a*aa*.*b*.c*.", true},
        {"abcd", "d*", false},
        {"abcd", ".*d", true},
        {"a", "a*a", true},
        
        // Tricky cases
        {"ab", ".*.", true},
        {"aaa", "a.a", true},
        {"aaa", "ab*a*c*a", true},
        {"abcdede", "ab.*de", true},
        {"a", ".*..", false},
        {"aa", "a.*", true},
        {"aa", ".*a", true},
        
        // Empty and minimal patterns
        {"", "", true},
        {"a", "", false},
        {"", "a", false},
        
        // Consecutive stars
        {"aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s", true},
        {"abcabc", ".*c", true},
    };

    std::string s = "aa";
    std::string p = "a*";
    std::cout << "'" << s << "' ? '" << p << "' : " << isMatch(s,p) << endl;

    runTests(tests, [](const Test& test){
        const bool isMatchSlow = isMatchSlowerRecursion(test.s, test.p);
        const bool isMatchMemoRec = isMatchMemorizedRecursion(test.s, test.p);
        const bool isMatchDP = isMatch(test.s, test.p);
        cout << getTestResultInfo(test.getInfo(), test.expectedResult, isMatchDP) << std::endl;
        return isMatchMemoRec == test.expectedResult && isMatchSlow == test.expectedResult && isMatchDP == test.expectedResult;
    });
}