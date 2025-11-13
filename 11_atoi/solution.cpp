#include <iostream>
#include <random>
#include <algorithm>
#include <climits>

#include <utils/utils.hpp>

using namespace std;

std::string_view trimLeft(std::string_view s) {
    auto firstNotWhiteChar = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    });
    return s.substr(firstNotWhiteChar - s.begin());
}

int myAtoi(string s) {
    std::string_view input = trimLeft(s);

    if (input.empty()) return 0;

    int8_t sign = 1;
    size_t idx = 0;

    if (input[idx] == '-') {
        sign = -1;
        idx++;
    } 
    else if (input[idx] == '+') 
        idx++;

    long long num = 0;
    while(idx < input.size() && std::isdigit(input[idx])) {
        num = num*10 + (int)(input[idx] - '0');
        idx++;

        // overflow check - num is long long so it won't overflow long long
        // by multiplying number from range (INT_MIN, INT_MAX) by 10
        if (sign == -1) {
            if (-num <= INT_MIN) return INT_MIN;
        }
        else if (num >= INT_MAX) return INT_MAX;
    }

    return static_cast<int>(sign*num);
}

struct Test {
    std::string s;
    int expectedResult;

    std::string getInfo() {
        return "s: " + s;
    }
};



void runSolution() {

    std::vector<Test> tests = {
        // Basic examples from problem
        {"42", 42},
        {"   -42", -42},
        {"4193 with words", 4193},
        {"words and 987", 0},
        {"1337c0d3", 1337},
        {"0-1", 0},
        
        // Empty and whitespace only
        {"", 0},
        {"   ", 0},
        {"          ", 0},
        
        // Sign handling
        {"+1", 1},
        {"-1", -1},
        {"+", 0},
        {"-", 0},
        {"+-12", 0},
        {"-+12", 0},
        {"++1", 0},
        {"--1", 0},
        {"   +  123", 0},
        {"   -  123", 0},
        
        // Leading zeros
        {"000123", 123},
        {"-000123", -123},
        {"+000456", 456},
        {"0000000000", 0},
        {"-0000000000", 0},
        
        // Overflow cases (INT_MAX = 2147483647, INT_MIN = -2147483648)
        {"2147483647", 2147483647},           // INT_MAX
        {"2147483648", 2147483647},           // INT_MAX + 1 -> rounds to INT_MAX
        {"2147483649", 2147483647},           // rounds to INT_MAX
        {"9999999999", 2147483647},           // large overflow
        {"99999999999999999999", 2147483647}, // very large overflow
        {"-2147483648", -2147483648},         // INT_MIN
        {"-2147483649", -2147483648},         // INT_MIN - 1 -> rounds to INT_MIN
        {"-9999999999", -2147483648},         // large underflow
        {"-99999999999999999999", -2147483648}, // very large underflow
        {"2147483646", 2147483646},           // INT_MAX - 1
        {"-2147483647", -2147483647},         // INT_MIN + 1
        
        // Near boundary cases
        {"2147483640", 2147483640},
        {"2147483650", 2147483647},
        {"-2147483640", -2147483640},
        {"-2147483650", -2147483648},
        {"21474836460", 2147483647},          // overflow by digit append
        {"-21474836480", -2147483648},
        
        // Non-digit characters
        {".1", 0},
        {".", 0},
        {"...123", 0},
        {"12.34", 12},
        {"abc", 0},
        {"  abc  123", 0},
        
        // Whitespace with signs
        {"  +123", 123},
        {"  -123", -123},
        {"  + 123", 0},
        {"  - 123", 0},
        
        // Mixed valid and invalid
        {"123abc456", 123},
        {"  -0012a42", -12},
        {"123 456", 123},
        {"  -  1", 0},
        
        // Special patterns
        {"   +0 123", 0},
        {"00000-42a1234", 0},
        {"  +  ", 0},
        {"+-", 0},
        {"+0", 0},
        {"-0", 0},
        {"   -0", 0},
        
        // Long valid numbers
        {"123456789", 123456789},
        {"-123456789", -123456789},
        {"1234567890", 1234567890},
        {"-1234567890", -1234567890},
        
        // Edge cases with characters after numbers
        {"123+456", 123},
        {"123-456", 123},
        {"123 ", 123},
        {"123          ", 123},
        
        // Multiple signs in string (but sign only valid at start)
        {"1-2+3", 1},
        {"0+0", 0},
        
        // Overflow during parsing
        {"10000000000000000000000000000000000000000000000000", 2147483647},
        {"-10000000000000000000000000000000000000000000000000", -2147483648},
        
        // Just at boundaries
        {"2147483647000", 2147483647},
        {"-2147483648000", -2147483648},
        
        // Leading whitespace variations
        {"   123", 123},  // tab is not space (depends on implementation)
        {"     +123", 123},
        {"     -123", -123},
        
        // Zero cases
        {"0", 0},
        {"+0", 0},
        {"-0", 0},
        {"   0", 0},
        {"000", 0},
        {"0000000", 0},
        
        // Single digit
        {"1", 1},
        {"9", 9},
        {"-5", -5},
        {"+7", 7}
    };

    std::cout << getResultInfoHeader() << std::endl;
    size_t passedCout = 0;
    for (auto test: tests) {
        int integer = myAtoi(test.s);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, integer) << std::endl;

        if (integer == test.expectedResult) passedCout++;
    }

    if (passedCout == tests.size()) {
        std::cout << greenStr("✓ ALL TESTS PASSED!") << endl;
    }
}