#include <iostream>
#include <utils/utils.hpp>

using namespace std;

int romanToInt(const string& s) {
    auto convert = [](const char romanDigit) noexcept {
        switch(romanDigit) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return 0;
    };

    int num = 0;
    for(int i = 0; i < s.size(); i++) {
        int left = convert(s[i]);
        int right = i < s.size()-1 ? convert(s[i+1]) : 0;

        // if we have bigger digit on the left then we don't have subtraction
        if ( left >= right)
            num += left;
        // if we have subtraction then treat both digits as one decimal digit 
        else {
            num += right - left;
            i++; // skip right for the next iteration
        }
    }

    return num;
}

struct Test {
    std::string s;
    int expectedResult;

    std::string getInfo() const {
        return s;
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        {"MCMXCIV", 1994},
        // 1. Simple Addition
        {"III", 3},
        {"VI", 6}, 
        
        // 2. Simple Subtraction
        {"IV", 4},
        {"IX", 9},
        {"XL", 40},
        
        // 3. Mixed Standard Cases
        {"LVIII", 58},          // L=50, V=5, III=3
        {"MCMXCIV", 1994},      // M=1000, CM=900, XC=90, IV=4
        
        // 4. Consecutive Subtractions (Important for your loop logic)
        //    This tests if the index skipping works correctly back-to-back
        {"CDXLIV", 444},        // CD(400) + XL(40) + IV(4)
        {"CMXC", 990},          // CM(900) + XC(90)

        // 5. Max Value (Standard LeetCode constraint is 3999)
        {"MMMCMXCIX", 3999},    // MMM(3000) + CM(900) + XC(90) + IX(9)
        
        // 6. Current Year (Fun test)
        {"MMXXV", 2025},       // MM(2000) + XX(20) + V(5)
        
        // 7. Single Character / Shortest inputs
        {"I", 1},
        {"M", 1000},
        
        // 8. Subtraction at the very beginning
        {"CM", 900}
    };

    runTests(tests, [](const Test& test){
        int result = romanToInt(test.s);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}