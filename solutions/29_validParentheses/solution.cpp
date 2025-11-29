#include <iostream>
#include <utils/utils.hpp>
#include <stack>

using namespace std;

bool isValid(const string& s) {
    // Target sum for a valid pair (e.g., '(' + ')' = 1 + 6 = 7)
    const int checkSum = 7; 
    const int firstClosingBracketId = 4;

    // Map brackets to IDs such that open + close = checkSum.
    // ( = 1, { = 2, [ = 3
    // ] = 4, } = 5, ) = 6
    auto charId = [] (const char ch) -> int {
        switch(ch) {
            case '(': return 1;
            case '{': return 2;
            case '[': return 3;
            case ']': return 4;
            case '}': return 5;
            case ')': return 6;
        }
        return -1;
    };

    auto isOpenChar = [&](const char ch) {
        return charId(ch) < firstClosingBracketId;
    };

    auto isValidClosure = [&](const char open, const char close) {
        return charId(open) + charId(close) == checkSum;
    };

    std::stack<char> st;
    for (auto ch : s) {
        if (isOpenChar(ch)) {
            st.push(ch);
        }
        else if (!st.empty() && isValidClosure(st.top(), ch)) {
            st.pop();
        }
        else {
            return false;
        }
    }

    // The stack must be empty. If it's not, we have unmatched open brackets.
    return st.empty();
}

struct Test {
    const std::string s;
    bool expectedResult;

    std::string getInfo() const {
        return s;
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // --- Standard LeetCode Examples ---
        { "()", true },
        { "()[]{}", true },
        { "(]", false },
        { "([])", true },
        
        // --- Nested Structures ---
        { "{[]}", true },
        { "({[]})", true },
        { "(([]){})", true },

        // --- Ordering Errors (Interleaved) ---
        // This fails because ')' tries to close '['
        { "([)]", false },
        { "[(])", false },

        // --- Leftover Open Brackets (Stack not empty at end) ---
        { "(", false },
        { "(()", false },
        { "[{", false },

        // --- Starting with Closing Brackets (Stack underflow) ---
        { "]", false },
        { ")(", false },
        { "){", false },
        
        // --- Long Valid String ---
        { "((((({{{[[[]]]}}})))))", true },
        
        // --- Mismatched Counts ---
        { "((", false },
        { "))", false }
    };

    runTests(tests, [](const Test& test){
        bool result = isValid(test.s);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}