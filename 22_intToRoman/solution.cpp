#include <iostream>
#include <utils/utils.hpp>

using namespace std;

string intToRoman(int num) {
    std::vector<char> romans = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

    // place shows where we have as digital place
    // it maps to our array 'romans' as 0, 2, 4, 6
    auto getRoman = [&](int digit, int place) {
        if (place < 0 || place > 6) return string("");

        // digit 'unit' in current digital place
        // 'unit' symbolize power of 10
        char unit = romans[place];

        // if we have thousands return 'M' up to 3 times
        if (place == 6)
            return string(digit, 'M');
        
        // digit 'five' in current digital place
        char five = romans[place+1];
        // digit 'unit' from the next digital place (so 'ten' in current)
        char ten = romans[place+2];

        // append 'unit' up to 3 times
        if (digit < 4)
            return string(digit, unit);

        // use subtractive forms:
        else if (digit == 4)
            return string({unit, five});

        else if (digit == 9)
            return string({unit, ten});
        
        // add 'five' and append 'unit' up to 3 times
        return string({five}) + string(digit-5, unit);
    };

    // start from the less important digits
    int place = 0;
    std::string result;

    // standard digit handling
    while (num > 0) {
        // add current roman part at the beggining
        result = getRoman(num % 10, place) + result;
        place += 2;
        num /= 10;
    }

    return result;
}

struct Test {
    int num;
    string expectedResult;

    std::string getInfo() const {
        return std::to_string(num);
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: Complex number with all decimal places
        { 3749, "MMMDCCXLIX" },

        // Example 2: Standard additive forms (50 + 5 + 3)
        { 58, "LVIII" },

        // Example 3: Multiple subtractive forms (CM, XC, IV)
        { 1994, "MCMXCIV" },

        // Edge Case: Minimum constraint
        { 1, "I" },

        // Edge Case: Maximum constraint
        { 3999, "MMMCMXCIX" },

        // Subtractive Case: 4
        { 4, "IV" },

        // Subtractive Case: 9
        { 9, "IX" },

        // Logic Check: 49 is 40(XL) + 9(IX), NOT IL
        { 49, "XLIX" },

        // Logic Check: 99 is 90(XC) + 9(IX), NOT IC
        { 99, "XCIX" },

        // Subtractive Case: 400
        { 400, "CD" },

        // Subtractive Case: 900
        { 900, "CM" },

        // Repetition check: 3 is III (max allowed repetition)
        { 3, "III" },

        // Round number check
        { 1000, "M" }
    };

    runTests(tests, [](const Test& test){
        string result = intToRoman(test.num);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}