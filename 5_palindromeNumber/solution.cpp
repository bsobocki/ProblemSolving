#include <iostream>
#include <vector>
#include <utils/utils.hpp>
#include <functional>

using namespace std;

// O(log_10 n) - time & space complexity
bool isPalindromeVec(int x) {
    if (x < 0) return false;

    std::vector<int> digits;
    while(x > 0) {
        digits.push_back(x%10);
        x /= 10;
    }

    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != digits[digits.size()-1-i])
            return false;
    }
    return true;
}

// reverse the whole X
// O(log_10 n) - time complexity
// O(1)        - space complexity
bool isPalindromeRev(int x) {
    if (x < 0) return false;
    int tempX = x;
    long int revX = 0;

    while(tempX > 0) {
        // move current digits
        revX *= 10;
        // add the new one
        revX += tempX % 10;
        tempX /= 10;
    }

    return revX == x;
}

// reverse only the half of the X number
// this is not my idea, but it is a little bit faster :D
// so i wanted to add it
// O(log_10 n) - time complexity
// O(1)        - space complexity
bool isPalindromeRevHalf(int x) {
    // the algorithm won't work for 10*k
    if (x < 0 or (x and x % 10 == 0)) return false;

    int revX = 0;
    while (revX < x) {
        revX = revX * 10 + x % 10;
        x /= 10;
    }

    return x == revX or x == revX/10;
}

struct Test {
    int x;
    bool expectedResult;
    
    string getInfo() const {
        return to_string(x);
    }
};

void runSolution() {
    const vector<Test> tests = {
        {121, true},
        {-121, false},
        {10, false},
        {0, true},
        {12321, true},
        {123321, true},
        {1234, false},
        {1, true},
        {99, true},
        {1000021, false},
    };

    auto testSolution = [&](const std::string& title, std::function<bool(int)> isPalindrome) {
        cout << "\n=== " << title << " SOLUTION ===" << endl;
        cout << getResultInfoHeader() << endl;
        for (auto& test : tests) {
            bool result = isPalindrome(test.x);
            cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << endl;
        }
    };

    testSolution("VECTOR", isPalindromeVec);
    testSolution("REVERSE FULL", isPalindromeRev);
    testSolution("REVERSE HALF", isPalindromeRevHalf);
}
